#pragma once
#include <GL/glew.h>
#include <memory>
#include <vector>
#include <unordered_map>
#include "Types/ColorTypes.h"
#include "Types/DimensionTypes.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"

class BasePrimitive
{
public:
	using VerticesDataType = GLfloat;
	using IndicesDataType = unsigned int;

	BasePrimitive(Size size, Vector3d position, float angle = 0.f);
	virtual ~BasePrimitive();

	// TODO: remove vertices methods?
	void SetVerticesData(const std::vector<VerticesDataType>& verticesData);
	std::vector<VerticesDataType> GetVerticesData() const;

	void SetIndicesData(const std::vector<IndicesDataType>& indicesData);
	std::vector<IndicesDataType> GetIndicesData() const;

	void SetSize(Size size);
	Size GetSize() const;

	void SetPosition(Vector3d position);
	Vector3d GetPosition() const;

	void SetAngle(float angle);
	float GetAngle() const;

	virtual void Draw(const glance::ShaderProgram& program) const = 0;

	BasePrimitive(const BasePrimitive&) = delete;
	BasePrimitive& operator=(const BasePrimitive&) = delete;

protected:
	void UpdateVerticesData();
	void UpdateIndicesData();

	void ApplyModelTransform(GLuint program) const;

	std::vector<Vector3d> CalculateNormals(const std::vector<Vector3d>& vertices) const;

	// TODO: сделать отдельные обертки и сделать их вью онли
	std::unique_ptr<glance::VertexArray> m_vao;
	std::unique_ptr<glance::VertexBuffer> m_vbo;
	std::unique_ptr<glance::IndexBuffer> m_ibo;

	Size m_size;
	float m_angle;
	Vector3d m_position;

	std::vector<VerticesDataType> m_verticesData;
	std::vector<IndicesDataType> m_indicesData;
};
