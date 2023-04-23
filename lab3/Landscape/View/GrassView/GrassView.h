#pragma once
#include <vector>
#include "../BaseView.h"

class GrassView : public BaseView
{
public:
	GrassView(
		Size size, Vector3d position, unsigned int vertices, const std::vector<RGB>& colors = {}, float angle = 0.f);

	void Show(unsigned int program) const override;

private:
	unsigned int m_vertices;
};