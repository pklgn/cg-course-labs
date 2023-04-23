#pragma once
// TODO: filled with knowledge why do I have to include glew here while he was added in pch file
#include <GL/glew.h>
#include "ColorTypes.h"
#include "DimensionTypes.h"

class BasePrimitive
{
public:
	static const RGB DEFAULT_COLOR;
	BasePrimitive(Size size, Vector3d position, float angle = 0.f);
	virtual ~BasePrimitive();

	// TODO: remove vertices methods?
	void SetVerticesData(const std::vector<GLfloat>& vertices);
	std::vector<GLfloat> GetVerticesData() const;

	void SetSize(Size size);
	Size GetSize() const;

	void SetPosition(Vector3d position);
	Vector3d GetPosition() const;

	void SetAngle(float angle);
	float GetAngle() const;

	virtual void Draw(GLuint program) const = 0;

protected:
	void UpdateData();
	void ApplyModelTransform(GLuint program) const;
	std::vector<RGB> GetVerticesColor(const std::vector<RGB>& colors, unsigned int verticesNumber) const;

	// TODO: сделать отдельные обертки и сделать их вью онли
	GLuint m_vao;
	GLuint m_vbo;
	Size m_size;
	float m_angle;
	Vector3d m_position;
	std::vector<GLfloat> m_verticesData;
};
