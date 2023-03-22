#include "../../pch.h"
#include "Observable.h"

void Observable::AddObserver(IObserver& observer)
{
	m_observers.push_back(&observer);
}

void Observable::RemoveObserver(IObserver& observer)
{
	m_observers.remove(&observer);
}

void Observable::NotifyObservers()
{
	for (auto&& observer : m_observers)
	{
		observer->Update();
	}
}
