#pragma once
#include <list>
#include "IObservable.h"

class Observable : public IObservable
{
public:
	void AddObserver(IObserver& observer) override;
	void RemoveObserver(IObserver& observer) override;
	void NotifyObservers() override;

private:
	std::list<IObserver*> m_observers
};