#pragma once
#include <GL/glew.h>
#include <vector>
#include "../../Common/Types/DimensionTypes.h"

class Rectangle
{
public:
	static const int VERTICES_NUMBER = 4;
	static const int DIMENSIONS_NUMBER = 3;
	Rectangle(Size size, Vector3d position);
	~Rectangle();
	
	void SetVertices(const std::vector<float>& corners);
	std::vector<float> GetVertices() const;

	void SetSize(Size size);
	Size GetSize() const;

	void Draw(unsigned int program) const;

private:
	void Prepare();
	void CheckVertices(const std::vector<float>& vertices);
	std::vector<float> m_vertices;
	GLuint m_vao;
	GLuint m_vbo;
	Size m_size;
	Vector3d m_position;
};
