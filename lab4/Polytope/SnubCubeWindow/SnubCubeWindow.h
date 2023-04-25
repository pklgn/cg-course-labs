#pragma once
#include <BaseWindow.hpp>

class SnubCubeWindow : public BaseWindow
{
public:
	using BaseWindow::BaseWindow;
	SnubCubeWindow(int w, int h, const char* title);

private:
	void UpdateUVMatrices(int width, int height);
	void Draw(int width, int height) override;
};
