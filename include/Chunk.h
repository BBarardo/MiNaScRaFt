#ifndef CHUNK_H
#define CHUNK_H

#include <array>
#include <vector>

#include "Cube.h"
#include "WorldConstants.h"
#include "ChunkMesh.h"
#include "ChunkMeshBuilder.h"


class Chunk
{
	glm::vec3 pos;
	std::vector<Cube> cubes;
	ChunkMesh mesh;
	
	int getIndex(int x, int y, int z);
	bool checkBounds(int val);
	
public:
	Chunk();
	Chunk(glm::vec3 pos);
	~Chunk();
	
	Cube getCube(int x, int y, int z);
	ChunkMesh getMesh() const;
	void setCube(int x, int y, int z, Cube cube);
	glm::vec3 getPos() const;
	

};

#endif
