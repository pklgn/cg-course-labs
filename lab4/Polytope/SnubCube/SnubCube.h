#pragma once
#include <vector>
#include <OpenGLPrimitive/BasePrimitive.h>

class SnubCube : BasePrimitive
{
public:
	SnubCube(Size size, Vector3d position, const std::vector<RGB>& colors = {}, float angle = 0.f);

	void Draw(GLuint program) const override;

private:
	std::vector<Vector3d> CalculateNormals(const std::vector<Vector3d>& vertices, const std::vector<unsigned int>& indices, const std::unordered_map<int, int>& faceVertexCountTofaceCount) const override;
	unsigned int m_verticesNumber;
};
