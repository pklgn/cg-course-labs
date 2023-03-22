#pragma once
#include "IObserver.h"

class IObservable
{
public:
	virtual ~IObservable() = default;

	virtual void AddObserver(IObserver& observer) = 0;
	virtual void RemoveObserver(IObserver& observer) = 0;
	virtual void NotifyObservers() = 0;
};