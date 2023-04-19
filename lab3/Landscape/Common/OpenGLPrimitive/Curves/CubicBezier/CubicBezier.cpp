#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "CubicBezier.h"

CubicBezier::CubicBezier(Size size, Vector3d position, const Curve4d& controlPoints, unsigned int verticesNumber)
	: BasePrimitive(size, position)
	, m_controlPoints(controlPoints)
	, m_verticesNumber(verticesNumber)
{
	std::vector<GLfloat> bezierPoints;

	for (int i = 0; i <= m_verticesNumber; i++)
	{
		GLfloat t = GLfloat(i) / GLfloat(m_verticesNumber);
		GLfloat x = static_cast<float>(pow(1 - t, 3) * controlPoints.p1.x + 3 * t * pow(1 - t, 2) * controlPoints.p2.x + 3 * pow(t, 2) * (1 - t) * controlPoints.p3.x + pow(t, 3) * controlPoints.p4.x);
		GLfloat y = static_cast<float>(pow(1 - t, 3) * controlPoints.p1.y + 3 * t * pow(1 - t, 2) * controlPoints.p2.y + 3 * pow(t, 2) * (1 - t) * controlPoints.p3.y + pow(t, 3) * controlPoints.p4.y);
		GLfloat z = static_cast<float>(pow(1 - t, 3) * controlPoints.p1.z + 3 * t * pow(1 - t, 2) * controlPoints.p2.z + 3 * pow(t, 2) * (1 - t) * controlPoints.p3.z + pow(t, 3) * controlPoints.p4.z);
		bezierPoints.push_back(x);
		bezierPoints.push_back(y);
		bezierPoints.push_back(z);
	}

	SetVerticesData(bezierPoints);
	UpdateData();
}

void CubicBezier::Draw(GLuint program) const
{
	// ��������� VAO
	glBindVertexArray(m_vao);

	int location = glGetUniformLocation(program, "u_color");
	// TODO: ���������� ���� �� �������
	glUniform4f(location, 1.f, 0.3f, 0.8f, 1.0f);
	
	ApplyModelTransform(program);

	// ��������� ������ �����
	glDrawArrays(GL_POLYGON, 0, m_verticesNumber + 1);

	// ����������� VAO
	glBindVertexArray(0);
}
