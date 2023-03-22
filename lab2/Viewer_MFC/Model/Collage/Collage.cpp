#include "../../pch.h"
#include "Collage.h"

void Collage::AddImageFrame(std::unique_ptr<ImageFrame>&& imageFrame)
{
	m_imageFrames.push_back(std::move(imageFrame));
}

size_t Collage::GetSize() const
{
	return m_imageFrames.size();
}
