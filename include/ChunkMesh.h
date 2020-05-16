#ifndef CHUNK_MESH_H
#define CHUNK_MESH_H

#include <vector>
#include <glm/glm.hpp>
#include <iostream>

#include "Mesh.h"
#include "Model.hpp"
#include "WorldConstants.h"

class ChunkMesh
{
public:
	ChunkMesh() = default;

	void addCubeFace(const std::vector<GLfloat>& cubeFace,
		const std::vector<float>& textureCoords,
		const glm::vec3 chunkPos,
		const glm::vec3& cubePosition);


	void createModel();

	const Model& getModel() const;


private:
	Mesh  m_mesh;
	Model m_model;
	GLuint m_indexIndex = 0;
};

#endif
