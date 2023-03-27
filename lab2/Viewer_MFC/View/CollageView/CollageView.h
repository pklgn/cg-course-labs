#pragma once
#include "../../Common/Observer/IObserver.h"
#include <vector>
#include <memory>
#include "../ImageFrameView/ImageFrameView.h"
#include "../../Model/Collage/Collage.h"

class CollageView : public IObserver<CollageData>
{
public:
	CollageView(Collage& collage);
	~CollageView();

	size_t GetCount();
	void AddImageFrameViewAtIndex(std::unique_ptr<ImageFrameView>&& imageFrameView, size_t index);
	void RemoveImageFrameViewAtIndex(size_t index);
	void Display(Gdiplus::Graphics& g);
	void Update(const CollageData& data) override;

private:
	std::vector<std::unique_ptr<ImageFrameView>> m_imageFrameViews;
	Collage& m_collage;
};
