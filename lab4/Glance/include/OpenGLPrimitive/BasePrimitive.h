#pragma once
// TODO: filled with knowledge why do I have to include glew here while he was added in pch file
#include <GL/glew.h>
#include <vector>
#include <unordered_map>
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
	void UpdateVerticesData();
	void UpdateIndexData(const std::vector<unsigned int>& indices);
	virtual void CalculateNormals(std::vector<Vector3d>& normals, const std::vector<Vector3d>& vertices) const = 0;
	void ApplyModelTransform(GLuint program) const;
	std::vector<RGB> GetVerticesColor(const std::vector<RGB>& colors, unsigned int verticesNumber) const;

	// TODO: ������� ��������� ������� � ������� �� ��� ����
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ibo;
	Size m_size;
	float m_angle;
	Vector3d m_position;
	std::vector<GLfloat> m_verticesData;
	std::vector<unsigned int> m_indicesData;
};
