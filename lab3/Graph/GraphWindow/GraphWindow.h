#pragma once
#include "../Common/BaseWindow.h"

class GraphWindow : public BaseWindow
{
public:
	using BaseWindow::BaseWindow;

private:
	void Draw(int width, int height) override;
};