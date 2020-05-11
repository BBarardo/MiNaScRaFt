#ifndef CHUNK_H
#define CHUNK_H

#include <unordered_set>
#include <vector>  //for std::vector

#include "Cube.h"

class Chunk
{
private:
	int id;
	glm::vec3 pos;
	std::vector<Cube> cubes;
public:
	Chunk(glm::vec3 pos);
	~Chunk();
	std::vector<Cube> getCubes() const;
	static std::unordered_set<int> existingChunks;
	static int idCount;
};

#endif
