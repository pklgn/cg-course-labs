#include "../../pch.h"
#include "CollageView.h"


CollageView::CollageView(Collage& collage)
	: m_collage(collage)
{
	collage.AddObserver(*this);
}

CollageView::~CollageView()
{
	m_collage.RemoveObserver(*this);
}

void CollageView::AddImageFrameViewAtIndex(std::unique_ptr<ImageFrameView>&& imageFrameView, size_t index)
{
	m_imageFrameViews.insert(m_imageFrameViews.begin() + index, std::move(imageFrameView));
}

void CollageView::RemoveImageFrameViewAtIndex(size_t index)
{
	m_imageFrameViews.erase(m_imageFrameViews.begin() + index);
}

size_t CollageView::GetSize()
{
	return m_imageFrameViews.size();
}

void CollageView::Display(Gdiplus::Graphics& g)
{
	for (auto&& imageFrameView : m_imageFrameViews)
	{
		imageFrameView.get()->Display(g);
	}
}

void CollageView::Update(const CollageData& data)
{
	if (data.imageFrame == std::nullopt)
	{
		RemoveImageFrameViewAtIndex(data.collageIndex.value());

		return;
	}
	auto&& test = **data.imageFrame;
	auto imageFrameView = std::make_unique<ImageFrameView>(test);
	AddImageFrameViewAtIndex(std::move(imageFrameView), data.collageIndex.value());
}
