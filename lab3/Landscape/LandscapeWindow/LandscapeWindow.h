#pragma once
#include "../Common/BaseWindow.h"

class LandscapeWindow : public BaseWindow
{
public:
	using BaseWindow::BaseWindow;

private:
	void Draw(int width, int height) override;
};
