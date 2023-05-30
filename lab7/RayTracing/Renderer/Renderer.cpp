﻿#include <boost/interprocess/ipc/message_queue.hpp>
#include "Renderer.h"
#include "../RenderContext/RenderContext.h"
#include "../Scene/Scene.h"

using std::mutex;

Renderer::~Renderer(void)
{
	// Останавливаем работу фонового потока, если он еще не закончился
	Stop();
}

// Выполняется ли в данный момент построение изображения в буфере кадра?
bool Renderer::IsRendering() const
{
	return m_rendering;
}

// Установлен ли флаг, сообщающий о необходимости завершения работы
bool Renderer::IsStopping() const
{
	// Считываем потокобезопасным образом значение переменной m_stopping
	return m_stopping;
}

bool Renderer::SetRendering(bool rendering)
{
	bool expected = !rendering;
	return m_rendering.compare_exchange_strong(expected, rendering);
}

bool Renderer::SetStopping(bool stopping)
{
	bool expected = !stopping;
	return m_stopping.compare_exchange_strong(expected, stopping);
}

bool Renderer::GetProgress(unsigned& renderedChunks, unsigned& totalChunks) const
{
	// Захватываем мьютекс на время работы данного метода
	std::lock_guard lock(m_mutex);

	// Получаем потокобезопасным образом значения переменных
	// m_renderedChunks и m_totalChunks
	renderedChunks = m_renderedChunks;
	totalChunks = m_totalChunks;

	// Сообщаем, все ли блоки изображения были обработаны
	return (totalChunks > 0) && (renderedChunks == totalChunks);
}

/*
Выполняет основную работу по построению изображения в буфере кадра
*/
void Renderer::RenderFrame(CScene const& scene, CRenderContext const& context, FrameBuffer& frameBuffer)
{
	// Запоминаем ширину и высоту буфера кадра, чтобы каждый раз не вызывать
	// методы класса CFrameBuffer
	const int width = frameBuffer.GetWidth();
	const int height = frameBuffer.GetHeight();

	/*
	Задаем общее количество блоков изображения
	Под блоком изображения здесь понимается 1 строка буфера кадра
	*/
	m_totalChunks = height;

	// Пробегаем все строки буфера кадра
	// При включенной поддержке OpenMP итерации цикла по строкам изображения
	// будут выполняться в параллельных потоках
#ifdef _OPENMP
#pragma omp parallel for schedule(dynamic)
#endif
	for (int y = 0; y < height; ++y)
	{
		std::uint32_t* rowPixels = nullptr;

		// Синхронизируем доступ к frameBuffer из вспомогательных потоков
#ifdef _OPENMP
#pragma omp critical
#endif
		{
			// Получаем адрес начала y-й строки в буфере кадра
			rowPixels = frameBuffer.GetPixels(y);
		}

		// Цикл по строкам выполняется только, если поступил запрос от пользователя
		// об остановке построения изображения
		// Инструкцию break для выхода из цикла здесь использовать нельзя (ограничение OpenMP)
		if (!IsStopping())
		{
			// Пробегаем все пиксели в строке
			for (int x = 0; x < width; ++x)
			{
				// Вычисляем цвет текущего пикселя и записываем его в буфер кадра
				rowPixels[size_t(x)] = context.CalculatePixelColor(scene, x, y);
			}

			++m_renderedChunks;
		}
	}

	// Сбрасываем флаг остановки
	SetStopping(false);
	// Сообщаем об окончании построения изображения
	SetRendering(false);
}

// Запускает визуализацию сцены в буфере кадра в фоновом потоке
// Возвращает false, если еще не была завершена работа ранее запущенного потока
bool Renderer::Render(CScene const& scene, CRenderContext const& context, FrameBuffer& frameBuffer)
{
	// Пытаемся перейти в режим рендеринга
	if (!SetRendering(true))
	{
		// В данный момент еще идет построение изображения в параллельном потоке
		return false;
	}

	// Блокируем доступ к общим (для фонового и основного потока) данным класса
	// вплоть до завершения работа метода Render
	std::lock_guard lock(m_mutex);

	// Очищаем буфер кадра
	frameBuffer.Clear();

	// Сбрасываем количество обработанных и общее количество блоков изображения
	// сигнализируя о том, что еще ничего не сделано
	m_totalChunks = 0;
	m_renderedChunks = 0;

	// Сбрасываем запрос на остановку построения изображения
	if (SetStopping(false))
	{
		// Если еще до запуска рабочего потока пришел запрос на остановку,
		// выходим, сбрасывая флаг "идет построение изображения"
		SetRendering(false);
		return false;
	}

	// Запускаем метод RenderFrame в параллельном потоке, передавая ему
	// необходимый набор параметров
	m_thread = std::jthread(
		&Renderer::RenderFrame, // Адрес метода RenderFrame
		this, // Указатель this
		std::ref(scene), // Ссылка на scene
		std::ref(context), // Ссылка на context
		std::ref(frameBuffer)); // Ссылка на frameBuffer

	// Выходим, сообщая о том, что процесс построения изображения запущен
	return true;
}

void Renderer::Stop()
{
	// Если происходит построение изображения
	if (IsRendering())
	{
		// Сообщаем потоку, выполняющему построение изображения, о необходимости
		// завершить работу
		SetStopping(true);

		// Дожидаемся окончания работы рабочего потока, если он не закончил работу
		if (m_thread.joinable())
		{
			m_thread.join();
		}

		// Сбрасываем флаг остановки, если поток завершил свою работу до вызова SetStopping(true)
		SetStopping(false);
	}
}