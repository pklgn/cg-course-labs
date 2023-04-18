#pragma once
#include <GL/glew.h>
#include <vector>
#include "../../../../Common/Types/DimensionTypes.h"
#include "../../BasePrimitive.h"

class Rectangle : public BasePrimitive
{
public:
	static const int VERTICES_NUMBER = 4;
	static const int DIMENSIONS_NUMBER = 3;
	Rectangle(Size size, Vector3d position);

	void Draw(GLuint program) const override;

private:
	void CheckVertices(const std::vector<float>& vertices);
};
