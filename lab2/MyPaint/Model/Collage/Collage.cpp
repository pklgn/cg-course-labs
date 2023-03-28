#include "../../pch.h"
#include "Collage.h"

void Collage::AddImageFrameAtIndex(std::unique_ptr<ImageFrame>&& imageFrame, size_t index)
{
	if (index == SIZE_MAX)
	{
		index = m_imageFrames.size();
	}

	if (m_imageFrames.size() < index)
	{
		throw std::out_of_range("ImageFrame index is out of range");
	}
	
	m_imageFrames.insert(m_imageFrames.begin() + index, std::move(imageFrame));
	
	m_changedData = {
		m_imageFrames.at(index).get(),
		index
	};
	NotifyObservers();
}

void Collage::RemoveImageFrameAtIndex(size_t index)
{
	// FIXED: покумекать
	if (m_imageFrames.size() < index)
	{
		throw std::out_of_range("ImageFrame index is out of range");
	}

	m_imageFrames.erase(m_imageFrames.begin() + index);

	m_changedData = {
		std::nullopt,
		index
	};
	// TODO: решить вопрос порядка удаления и правильной отписки от событий
	//NotifyObservers();
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

