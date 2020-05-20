#ifndef WORLD_H
#define WORLD_H
#include <vector>

#include "Chunk.h"

class World
{
	int min;
	int max;
	std::vector<Chunk> chunks;

	int getIndex(int x, int y, int z);
	bool checkBounds(int val);
	
public:
	World(int size);
	
	std::vector<Chunk> getChunks() const;

	Chunk getChunk(int x, int y, int z);
	void setChunk(int x, int y, int z, Chunk chunk);


};


#endif