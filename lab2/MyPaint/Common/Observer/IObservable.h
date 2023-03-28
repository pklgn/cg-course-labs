#pragma once
#include "IObserver.h"

template <class T>
class IObservable
{
public:
	virtual ~IObservable() = default;

	virtual void AddObserver(IObserver<T>& observer) = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
	virtual void NotifyObservers() = 0;
};