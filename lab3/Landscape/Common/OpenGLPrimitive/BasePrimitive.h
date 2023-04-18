#pragma once
#include <GL/glew.h>
#include <vector>
#include "../../Common/Types/DimensionTypes.h"

class BasePrimitive
{
public:
	BasePrimitive(Size size, Vector3d position);
	virtual ~BasePrimitive();

	// TODO: remove vertices methods
	void SetVertices(const std::vector<GLfloat>& vertices);
	std::vector<GLfloat> GetVertices() const;

	void SetSize(Size size);
	Size GetSize() const;

	void SetPosition(Vector3d position);
	Vector3d GetPosition() const;

	virtual void Draw(GLuint program) const = 0;

protected:
	void UpdateData();

	GLuint m_vao;
	GLuint m_vbo;
	Size m_size;
	Vector3d m_position;
	std::vector<GLfloat> m_vertices;
};
