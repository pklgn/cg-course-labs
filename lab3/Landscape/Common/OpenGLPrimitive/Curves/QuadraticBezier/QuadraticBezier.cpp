#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "QuadraticBezier.h"

QuadraticBezier::QuadraticBezier(Size size, Vector3d position, const Curve4d& controlPoints, unsigned int verticesNumber)
	: BasePrimitive(size, position)
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

	SetVertices(bezierPoints);
	UpdateData();
}

void QuadraticBezier::Draw(GLuint program) const
{
	// Активация VAO
	glBindVertexArray(m_vao);

	int location = glGetUniformLocation(program, "u_color");
	// TODO: передавать цвет из вершины
	glUniform4f(location, 1.f, 0.3f, 0.8f, 1.0f);
	glm::mat4 model = glm::mat4(1.0f);
	auto scale = glm::scale(glm::mat4(1.0f), glm::vec3(float(m_size.width), float(m_size.height), 1.0f));
	auto trans = glm::translate(glm::mat4(1.0f), glm::vec3(float(m_position.x), float(m_position.y), float(m_position.z)));
	auto final = trans * scale;
	GLint modelLoc = glGetUniformLocation(program, "u_model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(final));

	// Отрисовка кривой Безье
	glDrawArrays(GL_POLYGON, 0, m_verticesNumber + 1);

	// Деактивация VAO
	glBindVertexArray(0);
}
