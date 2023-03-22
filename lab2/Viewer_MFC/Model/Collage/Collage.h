#pragma once
#include <memory>
#include <vector>
#include "../ImageFrame/ImageFrame.h"
#include "../../Common/Observer/IObservable.h"

class Collage : public IObservable
{
public:
	void AddImageFrame(std::unique_ptr<ImageFrame>&& imageFrame);
	size_t GetSize() const;

private:
	std::vector<std::unique_ptr<ImageFrame>> m_imageFrames;
};
