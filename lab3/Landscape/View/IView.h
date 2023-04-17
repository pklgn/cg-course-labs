#pragma once

class IView
{
public:
	virtual ~IView() = default;

	virtual void Show() const = 0;
};