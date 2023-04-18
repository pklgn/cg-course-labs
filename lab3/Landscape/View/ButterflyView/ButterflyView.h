#pragma once
#include "../IView.h"
#include "../../Common/Types/DimensionTypes.h"

class ButterflyView : public IView
{
public:
	ButterflyView(Size size, Vector3d position);
	void Show(unsigned int program) const override;

private:
	void DrawButterflyBody(unsigned int program) const;
	void DrawButterflyAntena(unsigned int program) const;
	void DrawBufferflyWingPart(unsigned int program) const;
	void DrawButterflyWing(unsigned int program) const;

	Size m_size;
	Vector3d m_position;
};
