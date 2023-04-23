#pragma once
#include "../BaseView.h"
#include <vector>

class CloudView : public BaseView
{
public:
	CloudView(
		Size size, Vector3d position, const std::vector<RGB>& colors = {}, float angle = 0.f);

	void Show(unsigned int program) const override;
};