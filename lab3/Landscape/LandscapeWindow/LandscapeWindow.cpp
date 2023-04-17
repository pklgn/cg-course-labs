#include "LandscapeWindow.h"
#include "../Common/OpenGLPrimitive/Circle.h"
#include "../Common/OpenGLPrimitive/Rectangle.h"
#include "../../../Common/Types/DimensionTypes.h"
#include "../../../Common/Types/GeometryTypes.h"

// ������� ��� ���������� ����� �� ������ �����
std::vector<GLfloat> CalculateCubicBezierPoints(const Curve4d& controlPoints)
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

// ID �������� VAO � VBO
GLuint vaoID, vboID;

void DrawCubicCurveUsing(const Curve4d& curve, GLfloat fillType)
{
	// �������� VAO
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	// �������� VBO
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	// ���������� ����� �� ������ �����
	std::vector<GLfloat> bezierPoints = CalculateCubicBezierPoints(curve);

	// ���������� ������ VBO �������
	glBufferData(GL_ARRAY_BUFFER, bezierPoints.size() * sizeof(GLfloat), bezierPoints.data(), GL_STATIC_DRAW);

	// ��������� �������� ��������� ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// ������� VAO � VBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// ��������� VAO
	glBindVertexArray(vaoID);

	// ��������� ������ �����
	glDrawArrays(GL_POLYGON, 0, 100 + 1);

	// ����������� VAO
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
	// �������� VAO
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	// �������� VBO
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	// ���������� ����� �� ������ �����
	std::vector<GLfloat> bezierPoints = CalculateQuadraticBezierPoints(curve);

	// ���������� ������ VBO �������
	glBufferData(GL_ARRAY_BUFFER, bezierPoints.size() * sizeof(GLfloat), bezierPoints.data(), GL_STATIC_DRAW);

	// ��������� �������� ��������� ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// ������� VAO � VBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// ��������� VAO
	glBindVertexArray(vaoID);

	// ��������� ������ �����
	glDrawArrays(GL_POLYGON, 0, 100 + 1);

	// ����������� VAO
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
	// �������� VAO
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	// �������� VBO
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


	// ���������� ������ VBO �������
	glBufferData(GL_ARRAY_BUFFER, circlePoints.size() * sizeof(GLfloat), circlePoints.data(), GL_STATIC_DRAW);

	// ��������� �������� ��������� ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// ������� VAO � VBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// ��������� VAO
	glBindVertexArray(vaoID);

	glDrawArrays(GL_POLYGON, 0, 180 + 2);

	// ����������� VAO
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
	DrawButterflyBody();
	DrawButterflyAntena();
	DrawButterflyWing();
}
