#include "../../../../pch.h"
#include "QuadraticBezier.h"

QuadraticBezier::QuadraticBezier(Size size, Vector3d position, const Curve4d& controlPoints, const std::vector<RGB>& colors, float angle, unsigned int verticesNumber)
	: BasePrimitive(size, position, angle)
	, m_controlPoints(controlPoints)
	, m_verticesNumber(verticesNumber)
	, m_drawMode(GL_POLYGON)
{
	std::vector<GLfloat> bezierPoints;

	std::vector<RGB> finishColors = GetVerticesColor(colors, m_verticesNumber + 1);

	for (int i = 0; i <= static_cast<int>(m_verticesNumber); i++)
	{
		GLfloat t = GLfloat(i) / GLfloat(m_verticesNumber);
		float x = (1 - t) * (1 - t) * controlPoints.p1.x + 2 * (1 - t) * t * controlPoints.p2.x + t * t * controlPoints.p3.x;
		float y = (1 - t) * (1 - t) * controlPoints.p1.y + 2 * (1 - t) * t * controlPoints.p2.y + t * t * controlPoints.p3.y;
		float z = (1 - t) * (1 - t) * controlPoints.p1.z + 2 * (1 - t) * t * controlPoints.p2.z + t * t * controlPoints.p3.z;
		bezierPoints.push_back(x);
		bezierPoints.push_back(y);
		bezierPoints.push_back(z);

		bezierPoints.push_back(finishColors[i].r);
		bezierPoints.push_back(finishColors[i].g);
		bezierPoints.push_back(finishColors[i].b);
	}

	SetVerticesData(bezierPoints);
	UpdateData();
}

void QuadraticBezier::Draw(GLuint program) const
{
	// Активация VAO
	glBindVertexArray(m_vao);

	int location = glGetUniformLocation(program, "u_color");
	// TODO: передавать цвет из вершины
	glUniform4f(location, 1.f, 0.3f, 0.8f, 1.0f);
	
	ApplyModelTransform(program);

	// Отрисовка кривой Безье
	glDrawArrays(m_drawMode, 0, m_verticesNumber + 1);

	// Деактивация VAO
	glBindVertexArray(0);
}

void QuadraticBezier::SetDrawMode(GLenum mode)
{
	m_drawMode = mode;
}
