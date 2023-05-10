#include <sstream>
#include <array>
#include "PolytopeReader.h"
#include <Types/ColorTypes.h>

PolytopeReader::PolytopeReader(const std::string& filename)
	: m_inputStream(filename)
{
}

void PolytopeReader::Read(std::vector<Vector3d>& vertices, std::vector<unsigned int>& indices, std::vector<RGB>& colors, std::vector<Vector2d>& textures)
{
	vertices.clear();
	indices.clear();
	colors.clear();
	textures.clear();

	std::string polygonLine;
	std::istringstream polygonLineStream;
	Vector3d vertex;
	std::array<std::string, 3> vertexPositionString;
	RGB color;
	std::array<std::string, 3> colorSpectrumString;
	int vertexIndex = 0;
	std::array<std::string, 2> textureCoord;
	while (std::getline(m_inputStream, polygonLine))
	{
		polygonLineStream.str(polygonLine);
		polygonLineStream.clear();
		for (int i = 0; i < 3; ++i)
		{
			std::getline(polygonLineStream, vertexPositionString[0], '\t');
			std::getline(polygonLineStream, vertexPositionString[1], '\t');
			std::getline(polygonLineStream, vertexPositionString[2], '\t');

			vertex = {
				std::stof(vertexPositionString[0]),
				std::stof(vertexPositionString[1]),
				std::stof(vertexPositionString[2])
			};

			vertices.push_back(vertex);
			indices.push_back(vertexIndex++);
		}

		std::getline(polygonLineStream, colorSpectrumString[0], '\t');
		std::getline(polygonLineStream, colorSpectrumString[1], '\t');
		std::getline(polygonLineStream, colorSpectrumString[2], '\t');

		color = {
			std::stof(colorSpectrumString[0]),
			std::stof(colorSpectrumString[1]),
			std::stof(colorSpectrumString[2])
		};

		colors.push_back(color);
		colors.push_back(color);
		colors.push_back(color);

		for (int i = 0; i < 3; ++i)
		{
			std::getline(polygonLineStream, textureCoord[0], '\t');
			std::getline(polygonLineStream, textureCoord[1], '\t');

			Vector2d texture = {
				std::stof(textureCoord[0]),
				std::stof(textureCoord[1]),
			};

			textures.push_back(texture);
		}
	}
	int a = 1;
}
