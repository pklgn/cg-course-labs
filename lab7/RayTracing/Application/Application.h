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

	// ���������� ����������� ���� ����������
	void UpdateMainSurface();

	// ����������� ������ ����� � ������� �������� ����
	void CopyFrameBufferToSDLSurface();

	// ���������� �������, ���������� SDL
	static Uint32 SDLCALL TimerCallback(Uint32 interval, void* param);

	// ���������� ������� SDL ������� CApplication
	Uint32 OnTimer(Uint32 interval);

	// ������� ����������� ����, ��� ����������� � �����������
	void InvalidateMainSurface();

private:
	// ����� �����
	FrameBuffer m_frameBuffer;
	// ������������
	Renderer m_renderer;
	// ����������� ���� ����������
	SDL_Surface* m_pMainSurface;
	// ������������� SDL-�������
	SDL_TimerID m_timerId;
	// ��������� �� ����������� ���� ���������� (1 - ��, 0 - ���)
	boost::uint32_t m_mainSurfaceUpdated;
};
