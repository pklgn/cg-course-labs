#pragma once
#include <BaseWindow.hpp>

class LandscapeWindow : public BaseWindow
{
public:
	using BaseWindow::BaseWindow;

private:
	void UpdateUVMatrices(int width, int height);
	void Draw(int width, int height) override;
};
