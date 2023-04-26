#include "../../../../pch.h"

#include <format>
#include <string>

#include "ColorTypes.h"
#include "GeometryTypes.h"
#include "OpenGLPrimitive/Shapes/Rectangle/Rectangle.h"


void Rectangle::Draw(GLuint program) const
{
	// Нарисуем прямоугольник
	glBindVertexArray(m_vao);

	ApplyModelTransform(program);

	glDrawArrays(GL_QUADS, 0, VERTICES_NUMBER);
	glBindVertexArray(0);
}

void Rectangle::CheckVertices(const std::vector<float>& vertices)
{
	auto expectedSize = VERTICES_NUMBER * DIMENSIONS_NUMBER;
	if (vertices.size() != expectedSize)
	{
		auto fmt = std::format("Unable to assign less or more than {} vertices with {} dimensions each",
			VERTICES_NUMBER,
			DIMENSIONS_NUMBER);
		throw std::invalid_argument(fmt);
	}
}

Rectangle::Rectangle(Size size, Vector3d position, const std::vector<RGB>& colors, float angle)
	: BasePrimitive(size, position, angle)
{
	std::vector<RGB> finishColors = GetVerticesColor(colors, VERTICES_NUMBER);
	std::vector<GLfloat> vertices = {
		//position //colors
		-1, -1, 0, finishColors[0].r, finishColors[0].g, finishColors[0].b,
		 1, -1, 0, finishColors[1].r, finishColors[1].g, finishColors[1].b,
		 1,  1, 0, finishColors[2].r, finishColors[2].g, finishColors[2].b,
		-1,  1, 0, finishColors[3].r, finishColors[3].g, finishColors[3].b,
	};

	SetVerticesData(vertices);
	UpdateVerticesData();
}
