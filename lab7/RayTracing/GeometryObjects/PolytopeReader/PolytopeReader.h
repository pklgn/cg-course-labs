#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "../../TriangleMesh/TriangleMesh.h"

class PolytopeReader
{
public:
	PolytopeReader(std::string const& filename);

	void Read(std::vector<Vertex>& vertices, std::vector<Face>& faces);

private:
	std::ifstream m_inputStream;
};
