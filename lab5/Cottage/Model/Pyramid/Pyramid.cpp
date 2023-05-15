#include "Pyramid.h"
#include "../PolytopeReader/PolytopeReader.h"
#include <glm/gtx/transform.hpp>

Pyramid::Pyramid(Size size, Vector3d position, Vector3d angle)
	: BasePolytope("Model\\Assets\\pyramid.txt", size, position, angle)
{
}

