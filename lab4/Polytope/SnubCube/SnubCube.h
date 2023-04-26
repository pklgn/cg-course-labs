#pragma once
#include <vector>
#include <OpenGLPrimitive/BasePrimitive.h>

class SnubCube : BasePrimitive
{
public:
	SnubCube(Size size, Vector3d position, float angle = 0.f);

	void Draw(GLuint program) const override;

private:
	void CalculateNormals(std::vector<Vector3d>& normals, const std::vector<Vector3d>& vertices) const override;
	unsigned int m_verticesNumber;
};
