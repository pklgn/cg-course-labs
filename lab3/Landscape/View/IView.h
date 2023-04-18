#pragma once

class IView
{
public:
	virtual ~IView() = default;

	virtual void Show(unsigned int program) const = 0;
};