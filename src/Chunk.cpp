#include "Chunk.h"


Chunk::Chunk(glm::vec3 pos)
{
	for (unsigned int z = 0; z < 16; ++z) {
		for (unsigned int x = 0; x < 16; ++x) {
			for (unsigned int y = 0; y < 16; ++y) {
				Cube cube(glm::vec3(pos.x + x, y, pos.z + z));
				this->cubes.push_back(cube);
			}
		}
	}
}

Chunk::~Chunk()
{
}

std::vector<Cube> Chunk::getCubes() const
{
	return cubes;
}
