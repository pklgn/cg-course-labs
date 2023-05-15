#include "Cube.h"
#include "../PolytopeReader/PolytopeReader.h"
#include <glm/gtx/transform.hpp>

using namespace glance;

// FIXED: ������� ��� �������� � ���������� ������ � ������ � ������� ����� � ������������� �� ����
Cube::Cube(Size size, Vector3d position, Vector3d angle)
	: BasePolytope("Model\\Assets\\cube.txt", size, position, angle)
{
}
