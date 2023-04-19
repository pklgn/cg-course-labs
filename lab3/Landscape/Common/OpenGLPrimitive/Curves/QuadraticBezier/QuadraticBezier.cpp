#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "QuadraticBezier.h"

QuadraticBezier::QuadraticBezier(Size size, Vector3d position, const Curve4d& controlPoints, float angle, unsigned int verticesNumber)
	: BasePrimitive(size, position, angle)
	, m_controlPoints(controlPoints)
	, m_verticesNumber(verticesNumber)
{
	std::vector<GLfloat> bezierPoints;

	for (int i = 0; i <= m_verticesNumber; i++)
	{
		GLfloat t = GLfloat(i) / GLfloat(m_verticesNumber);
		float x = (1 - t) * (1 - t) * controlPoints.p1.x + 2 * (1 - t) * t * controlPoints.p2.x + t * t * controlPoints.p3.x;
		float y = (1 - t) * (1 - t) * controlPoints.p1.y + 2 * (1 - t) * t * controlPoints.p2.y + t * t * controlPoints.p3.y;
		float z = (1 - t) * (1 - t) * controlPoints.p1.z + 2 * (1 - t) * t * controlPoints.p2.z + t * t * controlPoints.p3.z;
		bezierPoints.push_back(x);
		bezierPoints.push_back(y);
		bezierPoints.push_back(z);
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
	glDrawArrays(GL_POLYGON, 0, m_verticesNumber + 1);

	// Деактивация VAO
	glBindVertexArray(0);
}
