#include "Application.h"
#include "../LightSource/OmniLightSource.h"
#include "../SceneObject/SceneObject.h"
// TODO: надо ли исправлять необходимость включать VectorMath.h заголовчник, потому что мы используем в рамках матрицы вида операции работы с векторами Dot и Cross?
#include "../Vector/VectorMath.h"
#include "../ViewPort/ViewPort.h"
// TODO: чисто для отладки
#include <iostream>
#include "../Material/ComplexMaterial.h"

// TODO: для отладки
size_t MOVABLE_LIGHT_SOURCE_INDEX = 0;

Application::Application()
	: m_frameBuffer(400, 300)
	, m_pMainSurface(NULL)
	, m_timerId(NULL)
	, m_mainSurfaceUpdated(0)
	, m_plane(0, 1, 0, 1) // Плоскость y=-1
	, m_sphere1(1.5) // Создаем сферу радиуса 1.5
	, m_sphere2(0.5) // Создаем сферу радиуса 0.5
{
	// Инициализация SDL (таймер и видео)
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	SDL_WM_SetCaption("Raytracing example", NULL);

	// Создаем главное окно приложения и сохраняем указатель
	// на поверхность, связанную с ним
	m_pMainSurface = SDL_SetVideoMode(400, 300, 32,
		SDL_SWSURFACE | SDL_DOUBLEBUF);

	/*
	Задаем цвет заднего фона сцены
	*/
	m_scene.SetBackdropColor(CVector4f(0, 0, 1, 1));


	// Создаем и добавляем в сцену сферу, имеющую заданный материал
	{
		/*
		Матрица трансформации сферы 1
		*/
		CMatrix4d sphereTransform;
		sphereTransform.Translate(2, 0, -5);
		m_sphere1.SetTransform(sphereTransform);

		/*
		Материал сферы 1
		*/
		ComplexMaterial material1;
		material1.SetDiffuseColor(CVector4f(0, 1, 0, 1));
		material1.SetSpecularColor(CVector4f(1, 1, 1, 1));
		material1.SetAmbientColor(CVector4f(0.2f, 0.2f, 0.2f, 1));

		// Шейдер сферы 1
		m_phongShader.SetMaterial(material1);
		m_scene.AddObject(CSceneObjectPtr(new CSceneObject(m_sphere1, m_phongShader)));
	}

	// Создаем и добавляем в сцену сферу, имеющую заданный материал
	{
		/*
		Матрица трансформации сферы 2
		*/
		CMatrix4d sphereTransform;
		sphereTransform.Translate(0, -0.5, -3);
		m_sphere2.SetTransform(sphereTransform);

		/*
		Материал сферы 2
		*/
		ComplexMaterial material2;
		material2.SetDiffuseColor(CVector4f(1, 0, 0, 1));
		material2.SetSpecularColor(CVector4f(1, 1, 1, 1));
		material2.SetAmbientColor(CVector4f(0.2f, 0.2f, 0.2f, 1));

		// Шейдер сферы 2
		m_phongShader1.SetMaterial(material2);
		m_scene.AddObject(CSceneObjectPtr(new CSceneObject(m_sphere2, m_phongShader1)));
	}

	// Создаем и добавляем в сцену точечный источник света
	{
		COmniLightPtr pLight(new COmniLightSource(CVector3d(0.f, 1.0, 10.f)));
		pLight->SetDiffuseIntensity(CVector4f(1, 1, 1, 1));
		pLight->SetSpecularIntensity(CVector4f(1, 1, 1, 1));
		pLight->SetAmbientIntensity(CVector4f(1, 1, 1, 1));
		m_scene.AddLightSource(pLight);
	}

	// Создаем и добавляем в сцену точечный источник света
	{
		COmniLightPtr pLight(new COmniLightSource(CVector3d(0.f, 30, 10.f)));
		pLight->SetDiffuseIntensity(CVector4f(1, 1, 1, 1));
		pLight->SetSpecularIntensity(CVector4f(1, 1, 1, 1));
		pLight->SetAmbientIntensity(CVector4f(1, 1, 1, 1));
		m_scene.AddLightSource(pLight);
	}

	/*
	Задаем параметры видового порта и матрицы проецирования в контексте визуализации
	*/
	m_context.SetViewPort(CViewPort(0, 0, 400, 300));
	CMatrix4d proj;
	proj.LoadPerspective(60, 400.0 / 300.0, 0.1, 10);
	m_context.SetProjectionMatrix(proj);
}

Application::~Application()
{
	// Завершаем работу всех подсистем SDL
	SDL_Quit();
}

void Application::MainLoop()
{
	// Инициализация приложения
	Initialize(); // (1)

	// Обновляем изначальное содержимое окна
	UpdateMainSurface(); // (2)

	// Цикл обработки сообщений, продолжающийся пока не будет
	// получен запрос на завершение работы
	SDL_Event evt; // (3)
	while (SDL_WaitEvent(&evt) && evt.type != SDL_QUIT)
	{
		switch (evt.type)
		{
		case SDL_VIDEOEXPOSE:
			// Обновляем содержимое главного окна,
			// если оно нуждается в перерисовке
			UpdateMainSurface(); // (3.а)
			break;

		case SDL_KEYDOWN: {
			CMatrix4d modelViewMatrix = m_context.GetModelViewMatrix();
			auto lightTranslate = m_scene.GetLight(MOVABLE_LIGHT_SOURCE_INDEX).GetTransform();
			bool cameraPosChanged = false;
			bool lightPosChanged = false;
			switch (evt.key.keysym.sym)
			{
			case SDLK_w:
				modelViewMatrix.Translate(0, 0, 1);
				cameraPosChanged = true;
				break;
			case SDLK_a:
				modelViewMatrix.Translate(1, 0, 0);
				cameraPosChanged = true;
				break;
			case SDLK_s:
				modelViewMatrix.Translate(0, 0, -1);
				cameraPosChanged = true;
				break;
			case SDLK_d:
				modelViewMatrix.Translate(-1, 0, 0);
				cameraPosChanged = true;
				break;
			case SDLK_UP:
				lightTranslate.Translate(0, 1, 0);
				lightPosChanged = true;
				break;
			case SDLK_DOWN:
				lightTranslate.Translate(0, -1, 0);
				lightPosChanged = true;
				break;
			case SDLK_LEFT:
				lightTranslate.Translate(-1, 0, 0);
				lightPosChanged = true;
				break;
			case SDLK_RIGHT:
				lightTranslate.Translate(1, 0, 0);
				lightPosChanged = true;
				break;
			default:
				break;
			}
			if (cameraPosChanged)
			{
				m_context.SetModelViewMatrix(modelViewMatrix);
				Initialize();
			}
			if (lightPosChanged)
			{
				m_scene.GetLight(MOVABLE_LIGHT_SOURCE_INDEX).SetTransform(lightTranslate);
				Initialize();
			}
		}
			break;
		case SDL_MOUSEBUTTONDOWN: {
			case SDL_MOUSEMOTION: {
				CMatrix4d modelViewMatrix = m_context.GetModelViewMatrix();
				if (evt.motion.state & SDL_BUTTON(SDL_BUTTON_LEFT))
				{
					int deltaX = 0;
					int deltaY = 0;
					SDL_GetRelativeMouseState(&deltaX, &deltaY);
					// TODO: Реализовать поворот камеры
					std::cout << deltaX << " " << deltaY << " " << std::endl;
				}
			}
			break;
		}
		};
	}

	// Деинициализация приложения
	Uninitialize(); // (4)
}

void Application::Initialize()
{
	// Запускаем построение изображения и таймер обновления экрана
	m_renderer.Render(m_scene, m_context, m_frameBuffer);
	m_timerId = SDL_AddTimer(50, &TimerCallback, this);
}

void Application::Uninitialize()
{
	// Останавливаем таймер обновления экрана и построение изображения
	SDL_RemoveTimer(m_timerId); // (4.а)
	m_renderer.Stop();
}

void Application::UpdateMainSurface()
{
	CopyFrameBufferToSDLSurface(); // (1)
	SDL_Flip(m_pMainSurface); // (2)

	m_mainSurfaceUpdated.store(1); // (3)
}

void Application::CopyFrameBufferToSDLSurface()
{
	SDL_LockSurface(m_pMainSurface); // (1.a)
	const SDL_PixelFormat* pixelFormat = m_pMainSurface->format;

	if (pixelFormat->BitsPerPixel == 32) // (1.b)
	{
		const Uint8 rShift = pixelFormat->Rshift; // (1.c)
		const Uint8 gShift = pixelFormat->Gshift;
		const Uint8 bShift = pixelFormat->Bshift;
		const Uint8 aShift = pixelFormat->Ashift;
		const Uint32 aMask = pixelFormat->Amask; // (1.d)

		const unsigned h = m_frameBuffer.GetHeight();
		const unsigned w = m_frameBuffer.GetWidth();

		// (1.e)
		Uint8* pixels = reinterpret_cast<Uint8*>(m_pMainSurface->pixels);
		for (unsigned y = 0; y < h; ++y, pixels += m_pMainSurface->pitch)
		{
			// (1.f)
			std::uint32_t const* srcLine = m_frameBuffer.GetPixels(y);
			Uint32* dstLine = reinterpret_cast<Uint32*>(pixels);

			if (bShift == 0 && gShift == 8 && rShift == 16) // (1.g)
			{
				memcpy(dstLine, srcLine, w * sizeof(Uint32));
			}
			else
			{
				for (unsigned x = 0; x < w; ++x) // (1.h)
				{
					boost::uint32_t srcColor = srcLine[x];
					Uint32 dstColor = ((srcColor & 0xff) << bShift) | (((srcColor >> 8) & 0xff) << gShift) | (((srcColor >> 16) & 0xff) << rShift) | ((((srcColor >> 24)) << aShift) & aMask);
					dstLine[x] = dstColor;
				}
			}
		}
	}

	SDL_UnlockSurface(m_pMainSurface); // (11)
}

Uint32 SDLCALL Application::TimerCallback(Uint32 interval, void* param)
{
	Application* pMyApp = reinterpret_cast<Application*>(param); // (1)
	return pMyApp->OnTimer(interval);
}

Uint32 Application::OnTimer(Uint32 interval)
{
	unsigned renderedChunks = 0;
	unsigned totalChunks = 0;
	if (m_renderer.GetProgress(renderedChunks, totalChunks)) // (2)
	{
		interval = 0; // (2.a)
	}

	InvalidateMainSurface(); // (2.b)

	return interval;
}

void Application::InvalidateMainSurface()
{
	bool redrawIsNeeded = m_mainSurfaceUpdated.load() == 1; // (3)

	if (redrawIsNeeded) // (3.a)
	{
		m_mainSurfaceUpdated.store(0); // (3.b)

		SDL_Event evt; // (3.c)
		evt.type = SDL_VIDEOEXPOSE;
		SDL_PushEvent(&evt);
	}
}
