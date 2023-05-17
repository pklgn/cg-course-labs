#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "Line.h"

Line::Line(float startX, float finishX, unsigned int precision, Size size, Vector3d position, Vector3d angle)
	: Primitive(size, position, angle)
{
	std::vector<VerticesDataType> verticesData;
	std::vector<IndicesDataType> indices;
	float stride = (finishX - startX) / precision;
	for (int i = 0; i <= static_cast<int>(precision); ++i)
	{
		verticesData.insert(verticesData.end(), { startX + stride * i, 0, 0 });
		indices.push_back(i);
	}

	SetVerticesData(verticesData);
	UpdateVerticesData();

	SetIndicesData(indices);
	UpdateIndicesData();
}

void Line::Draw() const
{
	m_vao->Bind();
	
	glDrawElements(GL_LINE_STRIP, (GLsizei)m_indicesData.size(), GL_UNSIGNED_INT, nullptr);

	m_vao->Unbind();
}

glm::mat4 Line::BuildModelMatrix() const
{
	auto translate = glm::translate(glm::mat4(1.0f), glm::vec3(m_position.x, m_position.y, m_position.z));
	auto scale = glm::scale(glm::mat4(1.0f), glm::vec3(m_size.width, m_size.height, m_size.depth));
	auto rotate = glm::rotate(glm::mat4(1.f), glm::radians(m_angle.x), glm::vec3(1.f, 0.f, 0.f));
	rotate = glm::rotate(rotate, glm::radians(m_angle.y), glm::vec3(0.f, 1.f, 0.f));
	rotate = glm::rotate(rotate, glm::radians(m_angle.z), glm::vec3(0.f, 0.f, 1.f));

	return translate * rotate * scale;
}
