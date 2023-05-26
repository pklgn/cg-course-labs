#include "Application.h"

Application::Application()
	: m_frameBuffer(800, 600)
	, m_pMainSurface(NULL)
	, m_timerId(NULL)
	, m_mainSurfaceUpdated(0)
{
	// ������������� SDL (������ � �����)
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	SDL_WM_SetCaption("Raytracing example", NULL);

	// ������� ������� ���� ���������� � ��������� ���������
	// �� �����������, ��������� � ���
	m_pMainSurface = SDL_SetVideoMode(800, 600, 32,
		SDL_SWSURFACE | SDL_DOUBLEBUF);
}

Application::~Application()
{
	// ��������� ������ ���� ��������� SDL
	SDL_Quit();
}

void Application::MainLoop()
{
	// ������������� ����������
	Initialize(); // (1)

	// ��������� ����������� ���������� ����
	UpdateMainSurface(); // (2)

	// ���� ��������� ���������, �������������� ���� �� �����
	// ������� ������ �� ���������� ������
	SDL_Event evt; // (3)
	while (SDL_WaitEvent(&evt) && evt.type != SDL_QUIT)
	{
		switch (evt.type)
		{
		case SDL_VIDEOEXPOSE:
			// ��������� ���������� �������� ����,
			// ���� ��� ��������� � �����������
			UpdateMainSurface(); // (3.�)
			break;
		}
	}

	// ��������������� ����������
	Uninitialize(); // (4)
}

void Application::Initialize()
{
	// ��������� ���������� ����������� � ������ ���������� ������
	m_renderer.Render(m_frameBuffer); // (1.�)
	m_timerId = SDL_AddTimer(50, &TimerCallback, this);
}

void Application::Uninitialize()
{
	// ������������� ������ ���������� ������ � ���������� �����������
	SDL_RemoveTimer(m_timerId); // (4.�)
	m_renderer.Stop();
}

void Application::UpdateMainSurface()
{
	// TODO: �����������
	CopyFrameBufferToSDLSurface(); // (1)
	SDL_Flip(m_pMainSurface); // (2)

	atomic_write32(&m_mainSurfaceUpdated, 1); // (3)
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
			boost::uint32_t const* srcLine = m_frameBuffer.GetPixels(y);
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
	bool redrawIsNeeded = atomic_read32(&m_mainSurfaceUpdated) == 1; // (3)

	if (redrawIsNeeded) // (3.a)
	{
		atomic_write32(&m_mainSurfaceUpdated, 0); // (3.b)

		SDL_Event evt; // (3.c)
		evt.type = SDL_VIDEOEXPOSE;
		SDL_PushEvent(&evt);
	}
}
