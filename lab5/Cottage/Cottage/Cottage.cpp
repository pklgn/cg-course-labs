#include "Cottage.h"

void Cottage::Draw(const glance::ShaderProgram& program) const
{
	// TODO: собирать шейлеры в рамках коттеджа и вызывать как элемент класса конкретный шейдер
	program.SetUniform3f("u_lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	program.SetUniform3f("u_lightPos", glm::vec3(10.2f, 10.0f, 10.0f));

	m_bedroom.Draw(program);
	m_livingRoom.Draw(program);
	m_diningRoom.Draw(program);
	m_garage.Draw(program);
	m_grass.Draw(program);
	m_fence.Draw(program);
}
