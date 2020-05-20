#include "World.h"

World::World(int size)
{
	this->min = -size / 2;
	this->max = size / 2;
	for (int x = min; x < max; ++x)
	{
		for (int z = min; z < max; ++z)
		{
			Chunk chunk(glm::vec3(x, -1, z));

			chunks.push_back(chunk);
		}
	}
}

std::vector<Chunk> World::getChunks() const
{
	return chunks;
}

Chunk World::getChunk(int x, int y, int z)
{
	if (checkBounds(x)) return Chunk();
	if (checkBounds(y)) return Chunk();
	if (checkBounds(z)) return Chunk();

	return chunks[getIndex(x, y, z)];
}

void World::setChunk(int x, int y, int z, Chunk chunk)
{
	if (checkBounds(x)) return;
	if (checkBounds(y)) return;
	if (checkBounds(z)) return;

	chunks[getIndex(x, y, z)] = chunk;
}

int World::getIndex(int x, int y, int z)
{
	return  y * CHUNK_AREA + z * CHUNK_SIZE + x;
}

bool World::checkBounds(int val)
{
	return val >= min || val < max;
}