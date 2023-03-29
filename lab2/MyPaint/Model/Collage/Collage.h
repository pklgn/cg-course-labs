#pragma once
#include <memory>
#include <vector>
#include "../ImageFrame/ImageFrame.h"
#include "../../Common/Observer/Observable.h"
#include "CollageData/CollageData.h"

class Collage : public Observable<CollageData>
{
public:
	void AddImageFrameAtIndex(std::unique_ptr<ImageFrame>&& imageFrame, size_t index = SIZE_MAX);
	void RemoveImageFrameAtIndex(size_t index);
	void SetSize(SIZE size);

	SIZE GetSize() const;
	size_t GetImageFrameCount() const;
	ImageFrame* GetImageFrameAtIndex(size_t index) const;

protected:
	CollageData GetChangedData() const override;

private:
	SIZE m_size;
	std::vector<std::unique_ptr<ImageFrame>> m_imageFrames;
	CollageData m_changedData;
};
