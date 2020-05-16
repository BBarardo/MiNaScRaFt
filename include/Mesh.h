#ifndef MESH_H
#define MESH_H


#include <vector>

struct Mesh
{
	std::vector<float> vertexPositions;
	std::vector<float> textureCoords;
	std::vector<unsigned int>  indices;
};


#endif
