#include "Application.h"
#include "../LightSource/OmniLightSource.h"
#include "../SceneObject/SceneObject.h"
// TODO: надо ли исправлять необходимость включать VectorMath.h заголовчник, потому что мы используем в рамках матрицы вида операции работы с векторами Dot и Cross?
#include "../Vector/VectorMath.h"
#include "../ViewPort/ViewPort.h"
// TODO: чисто для отладки
#include <iostream>
#include "../Material/ComplexMaterial.h"
#include "../TriangleMesh/TriangleMesh.h"
#include "../GeometryObjects/Dodecahedron/Dodecahedron.h"

// TODO: для отладки
size_t MOVABLE_LIGHT_SOURCE_INDEX = 0;

Application::Application()
	: m_frameBuffer(400, 300)
	, m_pMainSurface(NULL)
	, m_timerId(NULL)
	, m_mainSurfaceUpdated(0)
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

	//AddSomePlane();

	//AddSomeSpheres();

	//AddSomeConicCylinders();

	//AddSomeCubes();

	//AddSomeTetrahedron();

	//AddSomeOctahedron();

	AddSomeDodecahedron();

	AddSomeLight();

	/*
		Задаем параметры видового порта и матрицы проецирования в контексте визуализации
	*/
	m_context.SetViewPort(CViewPort(0, 0, 400, 300));
	CMatrix4d proj;
	proj.LoadPerspective(60, 400.0 / 300.0, 0.1, 10);
	m_context.SetProjectionMatrix(proj);

	// Задаем матрицу камеры
	CMatrix4d modelView;
	modelView.LoadLookAtRH(
		1, 1, 5,
		0, 0, 0,
		0, 1, 0);
	m_context.SetModelViewMatrix(modelView);
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

void Application::AddSomePlane()
{
	/*
		Матрица трансформации плоскости
	*/
	CMatrix4d planeTransform;
	planeTransform.Translate(0, -2, -3);

	/*
		Материал плоскости
	*/
	ComplexMaterial planeMaterial;
	planeMaterial.SetDiffuseColor(CVector4f(0, 1, 1, 1));
	planeMaterial.SetSpecularColor(CVector4f(1, 1, 1, 1));
	planeMaterial.SetAmbientColor(CVector4f(0.0f, 0.2f, 0.2f, 1));

	AddPlane(CreatePhongShader(planeMaterial), 0, 1, 0, 0, planeTransform);
}

void Application::AddSomeSpheres()
{
	// Матрица трансформации сферы 1
	CMatrix4d sphereTransform1;
	sphereTransform1.Translate(2, -1, -5);

	// Материал сферы 1
	ComplexMaterial material1;
	material1.SetDiffuseColor(CVector4f(0, 1, 0, 1));
	material1.SetSpecularColor(CVector4f(1, 1, 1, 1));
	material1.SetAmbientColor(CVector4f(0.0f, 0.3f, 0.0f, 1));

	AddSphere(CreatePhongShader(material1), 1, CVector3d(0, 0, 0), sphereTransform1);

	// Матрица трансформации сферы 2
	CMatrix4d sphereTransform2;
	sphereTransform2.Translate(0, -0.5, -3);

	// Материал сферы 2
	ComplexMaterial material2;
	material2.SetDiffuseColor(CVector4f(1, 0, 0, 1));
	material2.SetSpecularColor(CVector4f(1, 1, 1, 1));
	material2.SetAmbientColor(CVector4f(0.2f, 0.0f, 0.0f, 1));
	material2.SetSpecularCoefficient(512);

	AddSphere(CreatePhongShader(material2), 1, CVector3d(0, 0, 0), sphereTransform2);
}

void Application::AddSomeLight()
{
	COmniLightPtr pLightFront(new COmniLightSource(CVector3d(0.f, 5.0, 10.f)));
	pLightFront->SetDiffuseIntensity(CVector4f(1, 1, 1, 1));
	pLightFront->SetSpecularIntensity(CVector4f(1, 1, 1, 1));
	pLightFront->SetAmbientIntensity(CVector4f(1, 1, 1, 1));
	m_scene.AddLightSource(pLightFront);

	COmniLightPtr pLightUpper(new COmniLightSource(CVector3d(0.f, 30, 10.f)));
	pLightUpper->SetDiffuseIntensity(CVector4f(0.1f, 0.1f, 0.1f, 1));
	pLightUpper->SetSpecularIntensity(CVector4f(0.1f, 0.1f, 0.1f, 1));
	pLightUpper->SetAmbientIntensity(CVector4f(0.1f, 0.1f, 0.1f, 1));
	m_scene.AddLightSource(pLightUpper);
}

void Application::AddSomeConicCylinders()
{
	ComplexMaterial whiteMaterial;
	whiteMaterial.SetDiffuseColor(CVector4f(0.9f, 0.9f, 0.1f, 1));
	whiteMaterial.SetSpecularColor(CVector4f(1, 1, 1, 1));
	whiteMaterial.SetAmbientColor(CVector4f(0.2f, 0.2f, 0.2f, 1));

	CMatrix4d transform;
	transform.Translate(-1, -2, 0);
	transform.Rotate(-90, 1, 0, 0);
	
	AddConicCylinder(CreatePhongShader(whiteMaterial), 1, 0.5, 0.2, transform);
}

void Application::AddSomeCubes()
{
	// Матрица трансформации куба
	CMatrix4d cubeTransform;
	cubeTransform.Translate(-5, -0.5f, -3);
	cubeTransform.Scale(1, 1, 1);
	cubeTransform.Rotate(30, 0, 1, 0);
	cubeTransform.Rotate(-15, 1, 0, 0);

	//Материал куба
	ComplexMaterial cubeMaterial;
	cubeMaterial.SetDiffuseColor(CVector4f(1, 0, 0, 1));
	cubeMaterial.SetSpecularColor(CVector4f(1, 1, 1, 1));
	cubeMaterial.SetAmbientColor(CVector4f(0.2f, 0.2f, 0.2f, 1));
	cubeMaterial.SetSpecularCoefficient(2048);

	AddCube(CreatePhongShader(cubeMaterial), 1, CVector3d(0, 0, 0), cubeTransform);
}

void Application::AddSomeTetrahedron()
{
	// Вершины
	CVector3d v0(-1, 0, 1);
	CVector3d v1(+1, 0, 1);
	CVector3d v2(0, 0, -1);
	CVector3d v3(0, 2, 0);
	std::vector<Vertex> vertices;
	vertices.push_back(Vertex(v0));
	vertices.push_back(Vertex(v1));
	vertices.push_back(Vertex(v2));
	vertices.push_back(Vertex(v3));

	// Грани
	std::vector<Face> faces;
	faces.push_back(Face(0, 2, 1));
	faces.push_back(Face(3, 0, 1));
	faces.push_back(Face(3, 1, 2));
	faces.push_back(Face(3, 2, 0));

	// Данные полигональной сетки
	CTriangleMeshData* pMeshData = CreateTriangleMeshData(vertices, faces);

	CMatrix4d transform;
	transform.Translate(3, 0.3, -1);
	transform.Rotate(170, 0, 1, 0);
	CSimpleMaterial blue;
	blue.SetDiffuseColor(CVector4f(0.5f, 0.8f, 1, 1));

	AddTriangleMesh(CreateSimpleDiffuseShader(blue), pMeshData, transform);
}

void Application::AddSomeOctahedron()
{
	// Вершины
	CVector3d v0(0, 1, 0);
	CVector3d v1(1, 0, 0);
	CVector3d v2(0, -1, 0);
	CVector3d v3(-1, 0, 0);
	CVector3d v4(0, 0, 1);
	CVector3d v5(0, 0, -1);
	std::vector<Vertex> vertices;
	vertices.push_back(Vertex(v0));
	vertices.push_back(Vertex(v1));
	vertices.push_back(Vertex(v2));
	vertices.push_back(Vertex(v3));
	vertices.push_back(Vertex(v4));
	vertices.push_back(Vertex(v5));

	// Грани
	std::vector<Face> faces;
	faces.push_back(Face(2, 1, 4));
	faces.push_back(Face(1, 0, 4));
	faces.push_back(Face(0, 3, 4));
	faces.push_back(Face(3, 2, 4));
	faces.push_back(Face(2, 5, 1));
	faces.push_back(Face(1, 5, 0));
	faces.push_back(Face(0, 5, 3));
	faces.push_back(Face(3, 5, 2));

	// Данные полигональной сетки
	CTriangleMeshData* pMeshData = CreateTriangleMeshData(vertices, faces);

	CMatrix4d transform;
	transform.Translate(-3, 0.3, -5);
	transform.Scale(2, 2, 2);
	CSimpleMaterial violet;
	violet.SetDiffuseColor(CVector4f(0.8f, 0.0f, 0.8f, 1));

	AddTriangleMesh(CreateSimpleDiffuseShader(violet), pMeshData, transform);
}

void Application::AddSomeDodecahedron()
{
	CMatrix4d transform;
	transform.Translate(-3, 0.3, 2);

	//Материал додекадра
	ComplexMaterial material;
	material.SetDiffuseColor(CVector4f(1, 0, 0, 1));
	material.SetSpecularColor(CVector4f(1, 1, 1, 1));
	material.SetAmbientColor(CVector4f(0.2f, 0.2f, 0.2f, 1));
	material.SetSpecularCoefficient(2048);

	AddDodecahedron(CreatePhongShader(material), transform);
}

CSimpleDiffuseShader& Application::CreateSimpleDiffuseShader(CSimpleMaterial const& material)
{
	auto shader = std::make_unique<CSimpleDiffuseShader>(material);
	auto& shaderRef = *shader;
	m_shaders.emplace_back(std::move(shader));
	return shaderRef;
}

PhongShader& Application::CreatePhongShader(const ComplexMaterial& material)
{
	auto shader = std::make_unique<PhongShader>(material);
	auto& shaderRef = *shader;
	m_shaders.emplace_back(std::move(shader));
	return shaderRef;
}

CSceneObject& Application::AddSphere(IShader const& shader, double radius, CVector3d const& center, CMatrix4d const& transform)
{
	const auto& sphere = *m_geometryObjects.emplace_back(
		std::make_unique<CSphere>(radius, center, transform));

	return AddSceneObject(sphere, shader);
}

CSceneObject& Application::AddConicCylinder(IShader const& shader, double height, double baseRadius, double capRadius, CMatrix4d const& transform)
{
	const auto& conicCylinder = *m_geometryObjects.emplace_back(
		std::make_unique<ConicCylinder>(height, baseRadius, capRadius, transform));

	return AddSceneObject(conicCylinder, shader);
}

CSceneObject& Application::AddPlane(IShader const& shader, double a, double b, double c, double d, CMatrix4d const& transform)
{
	const auto& plane = *m_geometryObjects.emplace_back(
		std::make_unique<CPlane>(a, b, c, d, transform));

	return AddSceneObject(plane, shader);
}

CSceneObject& Application::AddSceneObject(IGeometryObject const& object, IShader const& shader)
{
	auto obj = std::make_shared<CSceneObject>(object, shader);
	m_scene.AddObject(obj);

	return *obj;
}

CSceneObject& Application::AddCube(IShader const& shader, double size, CVector3d const& center, CMatrix4d const& transform)
{
	const auto& cube = *m_geometryObjects.emplace_back(
		std::make_unique<Cube>(size, center, transform));

	return AddSceneObject(cube, shader);
}

CSceneObject& Application::AddTriangleMesh(IShader const& shader, CTriangleMeshData const* pMeshData, CMatrix4d const& transform)
{
	const auto& mesh = *m_geometryObjects.emplace_back(std::make_unique<CTriangleMesh>(pMeshData, transform));
	return AddSceneObject(mesh, shader);
}

CTriangleMeshData* Application::CreateTriangleMeshData(std::vector<Vertex> const& vertices, std::vector<Face> const& faces)
{
	auto* meshData = m_triangleMeshDataObjects.emplace_back(std::make_unique<CTriangleMeshData>(vertices, faces)).get();
	return meshData;
}

CSceneObject& Application::AddDodecahedron(IShader const& shader, CMatrix4d const& transform)
{
	const auto& dodecahedron = *m_geometryObjects.emplace_back(
		std::make_unique<Dodecahedron>(transform));

	return AddSceneObject(dodecahedron, shader);
}


