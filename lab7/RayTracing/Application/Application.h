#include <SDL/SDL.h>
#include "../FrameBuffer/FrameBuffer.h"
#include "../Renderer/Renderer.h"
#include <boost/interprocess/ipc/message_queue.hpp>

using namespace boost::interprocess::ipcdetail;

class Application
{
public:
	Application();

	~Application();

	void MainLoop();

private:
	void Initialize();

	void Uninitialize();

	// Обновление содержимого окна приложения
	void UpdateMainSurface();

	// Копирование буфера кадра в область главного окна
	void CopyFrameBufferToSDLSurface();

	// Обработчик таймера, вызываемый SDL
	static Uint32 SDLCALL TimerCallback(Uint32 interval, void* param);

	// Обработчик таймера SDL объекта CApplication
	Uint32 OnTimer(Uint32 interval);

	// Пометка содержимого окна, как нуждающейся в перерисовке
	void InvalidateMainSurface();

private:
	// Буфер кадра
	FrameBuffer m_frameBuffer;
	// Визуализатор
	Renderer m_renderer;
	// Поверхность окна приложения
	SDL_Surface* m_pMainSurface;
	// Идентификатор SDL-таймера
	SDL_TimerID m_timerId;
	// Обновлена ли поверхность окна приложения (1 - да, 0 - нет)
	boost::uint32_t m_mainSurfaceUpdated;
};
