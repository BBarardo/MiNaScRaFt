#ifndef CHUNK_MESH_BUILDER_H
#define CHUNK_MESH_BUILDER_H

#include <vector>
#include <iostream>

#include "Chunk.h"
#include "ChunkMesh.h"


class Chunk;
class ChunkMesh;

class ChunkMeshBuilder
{
	static const std::vector<float> frontFace;
	static const std::vector<float> backFace;
	static const std::vector<float> leftFace;
	static const std::vector<float> rightFace;
	static const std::vector<float> topFace;
	static const std::vector<float> bottomFace;
	static const std::vector<float> textCoordsDirt;
	static const std::vector<float> textCoordsStone;
	static const std::vector<float> textCoordsGrass;
	
	Chunk * b_chunk = nullptr;
	ChunkMesh * b_mesh = nullptr;

	void tryAddFaceToMesh(const std::vector<float>& blockFace,
						  const std::vector<float>& textureCoords,
						  const glm::vec3& blockPosition,
						  const glm::vec3& blockFacing);
	bool shouldMakeFace(const glm::vec3& adjBlock);

	
public:
	ChunkMeshBuilder(Chunk& chunk);
	void build(ChunkMesh& mesh);
};

#endif
