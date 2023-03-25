#pragma once
#include <list>
#include "IObservable.h"

template <class T>
class Observable : public IObservable
{
public:
	void AddObserver(IObserver& observer) override;
	void RemoveObserver(IObserver& observer) override;
	void NotifyObservers() override;

protected:
	virtual T GetChangedData() const = 0;

private:
	std::list<IObserver*> m_observers;
};