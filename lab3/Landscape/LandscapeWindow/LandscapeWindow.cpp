#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "LandscapeWindow.h"
#include "../Common/OpenGLPrimitive/Circle.h"
#include "../Common/OpenGLPrimitive/Rectangle.h"
#include "../Common/Types/DimensionTypes.h"
#include "../Common/Types/GeometryTypes.h"
#include "../Common/OpenGLPrimitive/Rectangle.h"
#include "../Common/OpenGLLog/OpenGLLog.h"

// Функция для вычисления точек на кривой Безье
std::vector<GLfloat> CalculateCubicBezierPoints(const Curve4d& controlPoints)
{
	const int NUM_POINTS = 100;
	std::vector<GLfloat> bezierPoints;

	for (int i = 0; i <= NUM_POINTS; i++)
	{
		GLfloat t = GLfloat(i) / GLfloat(NUM_POINTS);
		GLfloat x = static_cast<float>(pow(1 - t, 3) * controlPoints.p1.x + 3 * t * pow(1 - t, 2) * controlPoints.p2.x + 3 * pow(t, 2) * (1 - t) * controlPoints.p3.x + pow(t, 3) * controlPoints.p4.x);
		GLfloat y = static_cast<float>(pow(1 - t, 3) * controlPoints.p1.y + 3 * t * pow(1 - t, 2) * controlPoints.p2.y + 3 * pow(t, 2) * (1 - t) * controlPoints.p3.y + pow(t, 3) * controlPoints.p4.y);
		GLfloat z = static_cast<float>(pow(1 - t, 3) * controlPoints.p1.z + 3 * t * pow(1 - t, 2) * controlPoints.p2.z + 3 * pow(t, 2) * (1 - t) * controlPoints.p3.z + pow(t, 3) * controlPoints.p4.z);
		bezierPoints.push_back(x);
		bezierPoints.push_back(y);
		bezierPoints.push_back(z);
	}

	return bezierPoints;
}

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
	std::vector<GLfloat> bezierPoints = CalculateCubicBezierPoints(curve);

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
	glDrawArrays(GL_POLYGON, 0, 100 + 1);

	// Деактивация VAO
	glBindVertexArray(0);
}

std::vector<GLfloat> CalculateQuadraticBezierPoints(const Curve3d& controlPoints)
{
	const int NUM_POINTS = 100;
	std::vector<GLfloat> bezierPoints;

	for (int i = 0; i <= NUM_POINTS; i++)
	{
		GLfloat t = GLfloat(i) / GLfloat(NUM_POINTS);
		float x = (1 - t) * (1 - t) * controlPoints.p1.x + 2 * (1 - t) * t * controlPoints.p2.x + t * t * controlPoints.p3.x;
		float y = (1 - t) * (1 - t) * controlPoints.p1.y + 2 * (1 - t) * t * controlPoints.p2.y + t * t * controlPoints.p3.y;
		float z = (1 - t) * (1 - t) * controlPoints.p1.z + 2 * (1 - t) * t * controlPoints.p2.z + t * t * controlPoints.p3.z;
		bezierPoints.push_back(x);
		bezierPoints.push_back(y);
		bezierPoints.push_back(z);
	}

	return bezierPoints;
}

void DrawQuadraticCurveUsing(const Curve3d& curve, GLfloat fillType)
{
	// Создание VAO
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	// Создание VBO
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	// Вычисление точек на кривой Безье
	std::vector<GLfloat> bezierPoints = CalculateQuadraticBezierPoints(curve);

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
	glDrawArrays(GL_POLYGON, 0, 100 + 1);

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
	curve.p1.x = 0.f;
	curve.p1.y = 0.3f;
	curve.p1.z = butterflyDepth;
	curve.p2.x = 0.125f;
	curve.p2.y = 0.3f;
	curve.p2.z = butterflyDepth;
	curve.p3.x = 0.0725f;
	curve.p3.y = -0.15f;
	curve.p3.z = butterflyDepth;
	curve.p4.x = 0.f;
	curve.p4.y = -0.1f;
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

/// <summary>
/// Draws the butterfly antena.
/// </summary>
void DrawButterflyAntena()
{
	float butterflyDepth = 0;
	Curve3d curve;
	curve.p1.x = 0.01;
	curve.p1.y = 0.3;
	curve.p1.z = butterflyDepth;
	curve.p2.x = 0.02;
	curve.p2.y = 0.5;
	curve.p2.z = butterflyDepth;
	curve.p3.x = 0.2;
	curve.p3.y = 0.7;
	curve.p3.z = butterflyDepth;
	//curve.p4.x = 0;
	//curve.p4.y = -0.1;
	//curve.p4.z = butterflyDepth;
	DrawQuadraticCurveUsing(curve, GL_POLYGON);
}

void DrawBufferflyWingPart()
{
	float butterflyDepth = 0;
	Curve4d curve;
	// Top Wing
	curve.p1.x = 0;
	curve.p1.y = 0.2;
	curve.p1.z = butterflyDepth;
	curve.p2.x = 0.8;
	curve.p2.y = 0.9;
	curve.p2.z = butterflyDepth;
	curve.p3.x = 1.5;
	curve.p3.y = 0.0;
	curve.p3.z = butterflyDepth;
	curve.p4.x = 0;
	curve.p4.y = -0.4;
	curve.p4.z = butterflyDepth;
	DrawCubicCurveUsing(curve, GL_POLYGON);
	// Bottom Wing
	curve.p1.x = 0;
	curve.p1.y = 0;
	curve.p1.z = butterflyDepth;
	curve.p2.x = 1.0;
	curve.p2.y = -0.4;
	curve.p2.z = butterflyDepth;
	curve.p3.x = 0.2;
	curve.p3.y = -1.4;
	curve.p3.z = butterflyDepth;
	curve.p4.x = 0;
	curve.p4.y = -0.4;
	curve.p4.z = butterflyDepth;
	DrawCubicCurveUsing(curve, GL_POLYGON);
}

void DrawCircleUsing(Circle circle, GLfloat fillType)
{
	// Создание VAO
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	// Создание VBO
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	std::vector<GLfloat> circlePoints;
	
	for (int i = 0; i < 180; i++)
	{
		circle.posX = circle.radius * cos((float)i);
		circle.posY = circle.radius * sin((float)i);
		//glVertex3f(circle.posX + circle.transX, circle.posY + circle.transY, circle.transZ);
		circlePoints.push_back(circle.posX + circle.transX);
		circlePoints.push_back(circle.posY + circle.transY);
		circlePoints.push_back(circle.transZ);
	}


	// Заполнение буфера VBO данными
	glBufferData(GL_ARRAY_BUFFER, circlePoints.size() * sizeof(GLfloat), circlePoints.data(), GL_STATIC_DRAW);

	// Установка атрибута координат вершин
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// Отвязка VAO и VBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Активация VAO
	glBindVertexArray(vaoID);

	glDrawArrays(GL_POLYGON, 0, 180 + 2);

	// Деактивация VAO
	glBindVertexArray(0);
}

void DrawButterflyWingCircle(float radius, float tranX, float transY)
{
	Circle c;
	c.radius = radius;
	c.transX = tranX;
	c.transY = transY;
	c.transZ = 0;
	DrawCircleUsing(c, GL_POLYGON);
}

void DrawButterflyWing()
{
	glPushMatrix();
	glColor3f(0, 0, 0.2);
	DrawBufferflyWingPart();
	glColor3f(1, 1, 0.5);
	glScalef(0.9, 0.93, 0.9);
	DrawBufferflyWingPart();
	glColor3f(0, 1, 0.5);
	DrawButterflyWingCircle(0.13, 0.48, 0.28);
	DrawButterflyWingCircle(0.14, 0.25, -0.4);
	glPopMatrix();
}

void LandscapeWindow::Draw(int width, int height)
{
	glm::mat4 view = glm::mat4(1.0f);
	GLint viewLoc = glGetUniformLocation(m_shaderProgram, "u_view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 projection = glm::ortho(0.0f, float(width), 0.0f, float(height), - 1.0f, 100.0f);
	GLint projectionLoc = glGetUniformLocation(m_shaderProgram, "u_projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glViewport(0, 0, width, height);

	Rectangle rectangle({ 20, 30 }, { 200, 300, 0 });
	rectangle.Draw(m_shaderProgram);
	OpenGLLog::CheckOpenGLError();

	 DrawButterflyBody();
	 DrawButterflyAntena();
	 DrawButterflyWing();
}
