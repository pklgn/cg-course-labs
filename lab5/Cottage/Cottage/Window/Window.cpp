#include "Window.h"

using namespace glance;

Window::Window(Size size, Vector3d position, float angle)
	: Cube(size, position, angle)
{
	m_texture = std::make_unique<Texture>("Model\\Assets\\window.jpg");
}

void Window::Draw(const glance::ShaderProgram& program) const
{
	m_texture->Bind();
	Cube::Draw(program);
}
