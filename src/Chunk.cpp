#include "Chunk.h"

Chunk::Chunk()
{
}

Chunk::Chunk(glm::vec3 pos)
{
	this->pos = pos;
	for (unsigned int z = 0; z < CHUNK_SIZE; ++z) {
		for (unsigned int x = 0; x < CHUNK_SIZE; ++x) {
			for (unsigned int y = 0; y < CHUNK_SIZE; ++y) {
				Cube cube(glm::vec3(x, y, z), CubeType::dirt);
				cubes.push_back(cube);
			}
		}
	}
	
	ChunkMeshBuilder builder(*this);
	builder.build(this->mesh);
	mesh.createModel();
}

Chunk::~Chunk()
{
}

bool Chunk::checkBounds(int val)
{
	return val >= CHUNK_SIZE || val < 0;
}

void Chunk::setCube(int x, int y, int z, Cube cube)
{
	if (checkBounds(x)) return;
	if (checkBounds(y)) return;
	if (checkBounds(z)) return;

	cubes[getIndex(x, y, z)] = cube;
}

glm::vec3 Chunk::getPos() const
{
	return pos;
}

Cube Chunk::getCube(int x, int y, int z)
{
	if (checkBounds(x)) return Cube(glm::vec3(), CubeType::air);
	if (checkBounds(y)) return Cube(glm::vec3(), CubeType::air);
	if (checkBounds(z)) return Cube(glm::vec3(), CubeType::air);

	return cubes[getIndex(x, y, z)];
}

ChunkMesh Chunk::getMesh() const
{
	return mesh;
}

int Chunk::getIndex(int x, int y, int z)
{
	return  y * CHUNK_AREA + z * CHUNK_SIZE + x;
}
