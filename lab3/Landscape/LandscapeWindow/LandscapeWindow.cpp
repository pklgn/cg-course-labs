#include "LandscapeWindow.h"
#include "../Common/OpenGLPrimitive/Circle.h"
#include "../Common/OpenGLPrimitive/Rectangle.h"
#include "../../../Common/Types/DimensionTypes.h"
#include "../../../Common/Types/GeometryTypes.h"

// Функция для вычисления точек на кривой Безье
std::vector<GLfloat> CalculateBezierPoints(const Curve4d& controlPoints)
{
	const int NUM_POINTS = 100;
	std::vector<GLfloat> bezierPoints;

	for (int i = 0; i <= NUM_POINTS; i++)
	{
		GLfloat t = GLfloat(i) / GLfloat(NUM_POINTS);
		GLfloat x = pow(1 - t, 3) * controlPoints.p1.x + 3 * t * pow(1 - t, 2) * controlPoints.p2.x + 3 * pow(t, 2) * (1 - t) * controlPoints.p3.x + pow(t, 3) * controlPoints.p4.x;
		GLfloat y = pow(1 - t, 3) * controlPoints.p1.y + 3 * t * pow(1 - t, 2) * controlPoints.p2.y + 3 * pow(t, 2) * (1 - t) * controlPoints.p3.y + pow(t, 3) * controlPoints.p4.y;
		GLfloat z = pow(1 - t, 3) * controlPoints.p1.z + 3 * t * pow(1 - t, 2) * controlPoints.p2.z + 3 * pow(t, 2) * (1 - t) * controlPoints.p3.z + pow(t, 3) * controlPoints.p4.z;
		bezierPoints.push_back(x);
		bezierPoints.push_back(y);
		bezierPoints.push_back(z);
	}

	return bezierPoints;
}

// Точки контроля кривой Безье
Curve4d controlPoints = {
	{ -0.5,   0.5, 0.0 },
	{ -0.25, -0.5, 0.0 },
	{  0.25,  0.5, 0.0 },
	{  0.5,  -0.5, 0.0 }
};

// ID объектов VAO и VBO
GLuint vaoID, vboID;

void DrawCubicCurveUsing(const Curve4d& curve, GLfloat fillType)
{
	// Создание VAO
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	// Создание VBO
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	// Вычисление точек на кривой Безье
	std::vector<GLfloat> bezierPoints = CalculateBezierPoints(controlPoints);

	// Заполнение буфера VBO данными
	glBufferData(GL_ARRAY_BUFFER, bezierPoints.size() * sizeof(GLfloat), bezierPoints.data(), GL_STATIC_DRAW);

	// Установка атрибута координат вершин
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// Отвязка VAO и VBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Активация VAO
	glBindVertexArray(vaoID);

	// Отрисовка кривой Безье
	glDrawArrays(GL_LINE_STRIP, 0, 100 + 1);

	// Деактивация VAO
	glBindVertexArray(0);
}

/// <summary>
/// Draws the butterfly body.
/// </summary>
void DrawButterflyBody()
{
	float butterflyDepth = 0;
	Curve4d curve;
	curve.p1.x = 0;
	curve.p1.y = 0.3;
	curve.p1.z = butterflyDepth;
	curve.p2.x = 0.125;
	curve.p2.y = 0.3;
	curve.p2.z = butterflyDepth;
	curve.p3.x = 0.0725;
	curve.p3.y = -0.15;
	curve.p3.z = butterflyDepth;
	curve.p4.x = 0;
	curve.p4.y = -0.1;
	curve.p4.z = butterflyDepth;
	DrawCubicCurveUsing(curve, GL_POLYGON);
	curve.p1.x = 0;
	curve.p1.y = 0.2;
	curve.p1.z = butterflyDepth;
	curve.p2.x = 0.1;
	curve.p2.y = -0.3;
	curve.p2.z = butterflyDepth;
	curve.p3.x = 0.025;
	curve.p3.y = -0.55;
	curve.p3.z = butterflyDepth;
	curve.p4.x = 0;
	curve.p4.y = -0.5;
	curve.p4.z = butterflyDepth;
	DrawCubicCurveUsing(curve, GL_POLYGON);
}

void LandscapeWindow::Draw(int width, int height)
{
	DrawButterflyBody();
}
