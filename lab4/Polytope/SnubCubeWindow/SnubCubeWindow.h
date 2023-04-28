#pragma once
#include <memory>
#include <BaseWindow.hpp>
#include "../SnubCube/SnubCube.h"

class SnubCubeWindow : public BaseWindow
{
public:
	using BaseWindow::BaseWindow;
	SnubCubeWindow(int w, int h, const char* title);

private:
	void UpdateVPMatrices(int width, int height);
	void Draw(int width, int height) override;

	std::unique_ptr<SnubCube> m_snubCubePtr;
};
