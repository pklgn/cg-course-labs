#pragma once
#include <unordered_set>
#include "IObservable.h"

template <class T>
class Observable : public IObservable<T>
{
public:
	void AddObserver(IObserver<T>& observer) override
	{
		m_observers.insert(&observer);
	}

	void RemoveObserver(IObserver<T>& observer) override
	{
		m_observers.erase(&observer);
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		for (auto&& observer : m_observers)
		{
			observer->Update(data);
		}
	}

protected:
	virtual T GetChangedData() const = 0;

private:
	std::unordered_set<IObserver<T>*> m_observers;
};