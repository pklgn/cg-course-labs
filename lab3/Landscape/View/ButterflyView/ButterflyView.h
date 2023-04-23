#pragma once
#include <vector>
#include "../BaseView.h"

class ButterflyView : public BaseView
{
public:
	ButterflyView(
		Size size, Vector3d position, const std::vector<RGB>& colors = {}, float angle = 0.f);
	void Show(unsigned int program) const override;

private:
	void DrawButterflyBody(unsigned int program) const;
	void DrawButterflyAntena(unsigned int program) const;
	void DrawBufferflyWingPart(unsigned int program) const;
	void DrawButterflyWing(unsigned int program) const;
};
