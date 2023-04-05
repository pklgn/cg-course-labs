#define _USE_MATH_DEFINES
#include <cmath>
#include "GraphWindow.h"


const GLfloat X_MIN = -1;
const GLfloat X_MAX = 1;
const GLfloat Y_MIN = -1;
const GLfloat Y_MAX = 1;

const float GRID_STEP = 0.1f;

const GLfloat MIN_X_RANGE_BOUND = -6 * M_PI;
const GLfloat MAX_X_RANGE_BOUND = 6 * M_PI;
const float X_STEP = 0.0001f;

void DrawCoordinateSystem()
{
	// Рисуем сетку
	glColor3f(0.3f, 0.3f, 0.3f);
	glBegin(GL_LINES);
	for (float i = -1.0f; i <= 1.0f; i += GRID_STEP)
	{
		glVertex2f(i, -1.0f);
		glVertex2f(i, 1.0f);

		glVertex2f(-1.0f, i);
		glVertex2f(1.0f, i);
	}
	glEnd();

	// Рисуем ось X
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(-1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);
	glEnd();

	// Рисуем ось Y
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(0.0f, -1.0f);
	glVertex2f(0.0f, 1.0f);
	glEnd();
}

GLfloat GetHarmonicOscillation(GLfloat x)
{
	return sin(3 * x) + cos(2 * x + M_PI / 12);
}

void GraphWindow::Draw(int width, int height)
{
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);

	DrawCoordinateSystem();

	const auto scaleX = (std::abs(MIN_X_RANGE_BOUND) + std::abs(MAX_X_RANGE_BOUND)) / 2;
	glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_STRIP);
	for (float x = MIN_X_RANGE_BOUND; x <= MAX_X_RANGE_BOUND; x += X_STEP)
	{
		glVertex2f((x) / scaleX,
			GetHarmonicOscillation(x) / 2);
	}
	glEnd();
}
