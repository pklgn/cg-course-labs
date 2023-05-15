#include "Cube.h"
#include "../PolytopeReader/PolytopeReader.h"
#include <glm/gtx/transform.hpp>

using namespace glance;

// FIXED: вынести код создания и считывания данных о вершин в базовый класс и наследоваться от него
Cube::Cube(Size size, Vector3d position, Vector3d angle)
	: BasePolytope("Model\\Assets\\cube.txt", size, position, angle)
{
}
