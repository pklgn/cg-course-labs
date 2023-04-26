#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <DimensionTypes.h>
#include <ColorTypes.h>

class PolytopeReader
{
public:
	PolytopeReader(std::string const& filename);

	void Read(std::vector<Vector3d>& vertices, std::vector<unsigned int>& indices, std::vector<RGB>& colors);

private:
	std::ifstream m_inputStream;
};
