#include <sstream>
#include <array>
#include <iostream>
#include "PolytopeReader.h"

PolytopeReader::PolytopeReader(const std::string& filename)
	: m_inputStream(filename)
{
}

void PolytopeReader::Read(std::vector<Vertex>& vertices, std::vector<Face>& faces)
{
	vertices.clear();
	faces.clear();

	std::string str;
	std::istringstream strStream;
	std::string token;

	CVector3d currVector3d;
	unsigned linePos = 0;
	double x, y, z;

	std::istringstream faceStream;
	std::vector<unsigned> indices;
	while (std::getline(m_inputStream, str))
	{
		strStream.str(str);
		strStream.clear();
		++linePos;

		strStream >> token;
		if (token == "v")
		{
			// обрабатываем данные для вершин
			strStream >> x >> y >> z;
			currVector3d.x = x;
			currVector3d.y = y;
			currVector3d.z = z;

			// https://en.cppreference.com/w/cpp/io/basic_ios/rdstate
			if (!strStream.fail())
			{
				vertices.push_back(Vertex(currVector3d));
			}
			else
			{
				std::cout << "Error found in v string with position " << linePos << "\n";
			}
		}
		else if (token == "f")
		{
			// обрабатываем грани
			indices.clear();
			while (strStream >> token)
			{
				faceStream.str(token);
				faceStream.clear();
				if (std::getline(faceStream, token, '/'))
				{
					indices.push_back(std::stoi(token));
				}
				else
				{
					indices.clear();
					std::cout << "Error found in f string with position " << linePos << "\n";
					break;
				}
			}
			if (indices.size() == 3)
			{
				faces.push_back(Face(indices.at(0) - 1, indices.at(1) - 1, indices.at(2) - 1));
			}
		}
	}
}
