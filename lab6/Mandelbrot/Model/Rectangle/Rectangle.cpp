#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "Rectangle.h"

Rectangle::Rectangle(Size size, Vector3d position, Vector3d angle)
	: TexturePrimitive(size, position, angle)
{
	std::vector<VerticesDataType> verticesData = {
		//position //texture
		-1, -1, 1, 0, 1,
		1, -1, 1, 1, 1,
		1, 1, 1, 1, 0,
		-1, 1, 1, 0, 0
	};

	SetVerticesData(verticesData);
	UpdateVerticesData();

	SetIndicesData({3, 0, 2, 2, 0, 1});
	UpdateIndicesData();
}

void Rectangle::Draw() const
{
	m_vao->Bind();

	glDrawElements(GL_TRIANGLES, (GLsizei)m_indicesData.size(), GL_UNSIGNED_INT, nullptr);

	m_vao->Unbind();
}

glm::mat4 Rectangle::BuildModelMatrix() const
{
	auto translate = glm::translate(glm::mat4(1.0f), glm::vec3(m_position.x, m_position.y, 0.0f));
	auto scale = glm::scale(glm::mat4(1.0f), glm::vec3(m_size.width, m_size.height, 1.0f));
	auto rotate = glm::rotate(glm::mat4(1.f), glm::radians(m_angle.x), glm::vec3(1.f, 0.f, 0.f));
	rotate = glm::rotate(rotate, glm::radians(m_angle.y), glm::vec3(0.f, 1.f, 0.f));
	rotate = glm::rotate(rotate, glm::radians(m_angle.z), glm::vec3(0.f, 0.f, 1.f));

	return translate * rotate * scale;
}
