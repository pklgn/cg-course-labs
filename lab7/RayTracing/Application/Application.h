#pragma once
#include <SDL/SDL.h>
#include "../FrameBuffer/FrameBuffer.h"
#include "../GeometryObjects/Plane/Plane.h"
#include "../GeometryObjects/Sphere/Sphere.h"
#include "../RenderContext/RenderContext.h"
#include "../Renderer/Renderer.h"
#include "../Scene/Scene.h"
#include "../Shader/SimpleDiffuseShader.h"
#include "../Shader/PhongShader.h"

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
	// Сцена
	CScene m_scene;
	// Контекст
	CRenderContext m_context;

	// Поверхность окна приложения
	SDL_Surface* m_pMainSurface;
	// Идентификатор SDL-таймера
	SDL_TimerID m_timerId;
	// Обновлена ли поверхность окна приложения (1 - да, 0 - нет)
	std::atomic<uint32_t> m_mainSurfaceUpdated;

	// Геометрические объекты, присутствующие в сцене
	CPlane m_plane;
	CSphere m_sphere1;
	CSphere m_sphere2;

	// Шейдеры
	PhongShader m_phongShader;
	CSimpleDiffuseShader m_simpleDiffuseShader2;
};
