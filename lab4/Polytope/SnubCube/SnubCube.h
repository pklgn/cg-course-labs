#pragma once
#include <vector>
#include <OpenGLPrimitive/BasePrimitive.h>

class SnubCube : BasePrimitive
{
public:
	SnubCube(Size size, Vector3d position, const std::vector<RGB>& colors = {}, float angle = 0.f);

	void Draw(GLuint program) const override;

private:
	unsigned int m_verticesNumber;
};
