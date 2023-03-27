#pragma once

template <class T>
class IObserver
{
public:
	virtual ~IObserver() = default;

	virtual void Update(const T& data) = 0;
};