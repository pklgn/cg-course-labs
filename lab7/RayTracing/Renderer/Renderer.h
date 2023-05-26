#pragma once
#include <boost/thread.hpp>
#include "../FrameBuffer/FrameBuffer.h"

class Renderer
{
public:
	Renderer(void);
	~Renderer(void);

	bool IsRendering() const;

	bool GetProgress(unsigned& renderedChunks, unsigned& totalChunks) const;

	bool Render(FrameBuffer& frameBuffer);

	void Stop();

private:
	void RenderFrame(FrameBuffer& frameBuffer);

	bool SetRendering(bool rendering);

	bool SetStopping(bool stopping);

	bool IsStopping() const;

	boost::uint32_t CalculatePixelColor(int x, int y,
		unsigned frameWidth, unsigned frameHeight) const;

private:
	boost::thread m_thread;
	mutable boost::mutex m_mutex;
	volatile boost::uint32_t m_rendering;
	volatile boost::uint32_t m_stopping;
	volatile boost::uint32_t m_totalChunks;
	volatile boost::uint32_t m_renderedChunks;
};
