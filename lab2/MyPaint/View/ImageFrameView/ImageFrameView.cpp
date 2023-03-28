#include "../../pch.h"
#include "ImageFrameView.h"


ImageFrameView::ImageFrameView(ImageFrame& imageFrame)
	: m_imageFrame(imageFrame)
{
	m_imageFrame.AddObserver(*this);
}

ImageFrameView::~ImageFrameView()
{
	m_imageFrame.RemoveObserver(*this);
	// FIXED: подумать над тем, как правильно удалять миниатюру битмапы
	// FIXED: сделал создание битмапы через .reset();
}

void ImageFrameView::Display(Gdiplus::Graphics& g)
{
	auto leftTop = m_imageFrame.GetLeftTop();
	g.DrawImage(m_pThumbnailImage.get(), static_cast<INT>(leftTop.x), static_cast<INT>(leftTop.y));
}

void ImageFrameView::Update(const ImageFrameData& data)
{
	if (data.pBitmap != std::nullopt ||
		data.size != std::nullopt)
	{
		m_pThumbnailImage.reset(m_imageFrame.GetThumbnailImage(data.size.value()));
	}
}
