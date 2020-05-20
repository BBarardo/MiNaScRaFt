#include "ChunkMeshBuilder.h"


const std::vector<float> ChunkMeshBuilder::frontFace
{
	0, 0, 1,
	1, 0, 1,
	1, 1, 1,
	0, 1, 1,
};

const std::vector<float> ChunkMeshBuilder::backFace
{
	1, 0, 0,
	0, 0, 0,
	0, 1, 0,
	1, 1, 0,
};

const std::vector<float> ChunkMeshBuilder::leftFace
{
	0, 0, 0,
	0, 0, 1,
	0, 1, 1,
	0, 1, 0,
};

const std::vector<float> ChunkMeshBuilder::rightFace
{
	1, 0, 1,
	1, 0, 0,
	1, 1, 0,
	1, 1, 1,
};

const std::vector<float> ChunkMeshBuilder::topFace
{
	0, 1, 1,
	1, 1, 1,
	1, 1, 0,
	0, 1, 0,
};

const std::vector<float> ChunkMeshBuilder::bottomFace
{
	0, 0, 0,
	1, 0, 0,
	1, 0, 1,
	0, 0, 1
};

const std::vector<float> ChunkMeshBuilder::textCoordsDirt
{
	0, 0,
	0, 1,
	0.33333, 1,
	0.33333, 0
};
const std::vector<float> ChunkMeshBuilder::textCoordsStone
{
	0.33333, 0,
	0.33333, 1,
	0.66667, 1,
	0.66667, 0
};
const std::vector<float> ChunkMeshBuilder::textCoordsGrass
{
	0.66667, 0,
	0.66667, 1,
	1, 1,
	1, 0
};

struct AdjacentBlockPositions
{
	void update(int x, int y, int z)
	{
		up = { x,     y + 1,  z };
		down = { x,     y - 1,  z };
		left = { x - 1, y,      z };
		right = { x + 1, y,      z };
		front = { x,     y,      z + 1 };
		back = { x,     y,      z - 1 };
	}

	glm::vec3 up;
	glm::vec3 down;
	glm::vec3 left;
	glm::vec3 right;
	glm::vec3 front;
	glm::vec3 back;
};

int faces = 0;

ChunkMeshBuilder::ChunkMeshBuilder(Chunk& chunk) : b_chunk(&chunk)
{
}

void ChunkMeshBuilder::build(ChunkMesh& mesh)
{
	//float currentTime = glfwGetTime();
	std::cout << "Begin mesh build\n";
	b_mesh = &mesh;

	AdjacentBlockPositions adjacent_blocks;

	for (unsigned int y = 0; y < CHUNK_SIZE; ++y)
		for (unsigned int x = 0; x < CHUNK_SIZE; ++x)
			for (unsigned int z = 0; z < CHUNK_SIZE; ++z)
			{
				glm::vec3 position(x, y, z);
				Cube cube = b_chunk->getCube(x, y, z);
				CubeType cubeType = cube.getType();
				
				if (cubeType == CubeType::air)
					continue;

				adjacent_blocks.update(x, y, z);
				
				std::vector<float> textCorrds;
				if(cubeType == CubeType::stone)
				{
					textCorrds = textCoordsStone;
				}else if(cubeType == CubeType::dirt)
				{
					textCorrds = textCoordsDirt;
				}else if (cubeType == CubeType::grass)
				{
					textCorrds = textCoordsDirt;
					//Up/ Down
					tryAddFaceToMesh(topFace, textCoordsGrass, position, adjacent_blocks.up);
					tryAddFaceToMesh(bottomFace, textCorrds, position, adjacent_blocks.down);

					//Left/ Right
					tryAddFaceToMesh(leftFace, textCorrds, position, adjacent_blocks.left);
					tryAddFaceToMesh(rightFace, textCorrds, position, adjacent_blocks.right);

					//Front/ Back
					tryAddFaceToMesh(frontFace, textCorrds, position, adjacent_blocks.front);
					tryAddFaceToMesh(backFace, textCorrds, position, adjacent_blocks.back);
					
					continue;
				}
				//Up/ Down
				tryAddFaceToMesh(topFace, textCorrds, position, adjacent_blocks.up);
				tryAddFaceToMesh(bottomFace, textCorrds, position, adjacent_blocks.down);

				//Left/ Right
				tryAddFaceToMesh(leftFace, textCorrds, position, adjacent_blocks.left);
				tryAddFaceToMesh(rightFace, textCorrds, position, adjacent_blocks.right);

				//Front/ Back
				tryAddFaceToMesh(frontFace, textCorrds, position, adjacent_blocks.front);
				tryAddFaceToMesh(backFace, textCorrds, position, adjacent_blocks.back);


			}
}

void ChunkMeshBuilder::tryAddFaceToMesh(const std::vector<float>& blockFace,
	const std::vector<float>& textureCoords,
	const glm::vec3& blockPosition,
	const glm::vec3& blockFacing)
{
	if (shouldMakeFace(blockFacing))
	{
		faces++;
		//auto texCoords = BlockDatabase::get().textureAtlas.getTexture(textureCoords);

		b_mesh->addCubeFace(blockFace, textureCoords, b_chunk->getPos(), blockPosition);
	}
}


bool ChunkMeshBuilder::shouldMakeFace(const glm::vec3& adjBlock)
{
	auto block = b_chunk->getCube(adjBlock.x, adjBlock.y, adjBlock.z);

	if (block.getType() == CubeType::air)
	{
		return true;
	}

	return false;
}
