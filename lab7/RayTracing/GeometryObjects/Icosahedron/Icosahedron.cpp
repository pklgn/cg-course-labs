#include "Icosahedron.h"

Icosahedron::Icosahedron(CMatrix4d const& transform)
	: WavefrontObject("GeometryObjects/Icosahedron/icosahedron.obj", transform)
{
}
