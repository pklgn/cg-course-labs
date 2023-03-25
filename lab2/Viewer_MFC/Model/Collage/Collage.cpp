#include "../../pch.h"
#include "Collage.h"

void Collage::AddImageFrameAtIndex(std::unique_ptr<ImageFrame>&& imageFrame, size_t index)
{
	if (index == SIZE_MAX)
	{
		index = m_imageFrames.size();
	}
	
	m_imageFrames.insert(m_imageFrames.begin() + index, std::move(imageFrame));
	m_changedData = {
		m_imageFrames.at(index).get(),
		index
	};
}

void Collage::RemoveImageFrameAtIndex(size_t index)
{
	// TODO: покумекать
}

size_t Collage::GetSize() const
{
	return m_imageFrames.size();
}

ImageFrame* Collage::GetImageFrameAtIndex(size_t index) const
{
	return m_imageFrames.at(index).get();
}

CollageData Collage::GetChangedData() const
{
	return m_changedData;
}

