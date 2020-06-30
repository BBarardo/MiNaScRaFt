#include "ChunkMesh.h"

void ChunkMesh::addCubeFace(const std::vector<GLfloat>& cubeFace,
						    const std::vector<float>& norm, 
						    const std::vector<float>& textureCoords,
                            const glm::vec3 chunkPos,
                            const glm::vec3& cubePosition)
{
    auto& verticies = m_mesh.vertexPositions;
    auto& texCoords = m_mesh.textureCoords;
    auto& indices = m_mesh.indices;
    auto& normals = m_mesh.normals;

    texCoords.insert(texCoords.end(), textureCoords.begin(), textureCoords.end());

    ///Vertex: The current vertex in the "blockFace" vector, 4 vertex in total hence "< 4"
	///Index: X, Y, Z
    for (int i = 0, indexVert = 0, indexNorm = 0; i < 4; ++i)
    {
        verticies.push_back(cubeFace[indexVert++] + chunkPos.x * CHUNK_SIZE + cubePosition.x);
        verticies.push_back(cubeFace[indexVert++] + chunkPos.y * CHUNK_SIZE + cubePosition.y);
        verticies.push_back(cubeFace[indexVert++] + chunkPos.z * CHUNK_SIZE + cubePosition.z);

        normals.push_back(norm[indexNorm++]);
        normals.push_back(norm[indexNorm++]);
        normals.push_back(norm[indexNorm]);
        indexNorm = 0;
    }

    indices.insert(indices.end(),
        {
            m_indexIndex,
            m_indexIndex + 1,
            m_indexIndex + 2,

            m_indexIndex + 2,
            m_indexIndex + 3,
            m_indexIndex
        });
    m_indexIndex += 4;
}

void ChunkMesh::createModel()
{
    std::cout << "Buffered"
        << "\nVertex:   " << m_mesh.vertexPositions.size()
        << "\nTextures: " << m_mesh.textureCoords.size()
        << "\nIndices:  " << m_mesh.indices.size() << "\n";
    m_model.fill(m_mesh);

    m_mesh.vertexPositions.clear();
    m_mesh.textureCoords.clear();
    m_mesh.indices.clear();

    m_mesh.vertexPositions.shrink_to_fit();
    m_mesh.textureCoords.shrink_to_fit();
    m_mesh.indices.shrink_to_fit();

    m_indexIndex = 0;
}


const Model& ChunkMesh::getModel() const
{
	return m_model;
}

