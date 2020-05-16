#include "Model.hpp"

#include <iostream>

Model::Model(Mesh& mesh)
{
	fill(mesh);
}

void Model::fill(Mesh& mesh)
{
	if (VAO != 0)
		deleteData();

	i_count = mesh.indices.size();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	addVBO(3, mesh.vertexPositions);
	addVBO(2, mesh.textureCoords);
	addEBO(mesh.indices);
}

void Model::addVBO(int dimenson, std::vector<float> data)
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
		data.size() * sizeof(GLfloat),
		data.data(),
		GL_STATIC_DRAW);

	glVertexAttribPointer(VBO_count,
		dimenson,
		GL_FLOAT,
		GL_FALSE,
		0,
		(GLvoid*)0);

	glEnableVertexAttribArray(VBO_count++);

	VBOs.push_back(vbo);
}

void Model::addEBO(std::vector<unsigned int> indices)
{
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		indices.size() * sizeof(GLuint),
		indices.data(),
		GL_STATIC_DRAW);
	EBO = ebo;
}


void Model::deleteData()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(VBOs.size(),
		VBOs.data());

	VBOs.clear();

	VBO_count = 0;
	VAO = 0;
	i_count = 0;
}

unsigned int Model::getIndicesCount() const
{
	return i_count;
}

void Model::bindVAO() const
{
	glBindVertexArray(this->VAO);
}

void Model::bindEBO() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
}

unsigned Model::get_i_count() const
{
	return i_count;
}

//for debug
void Model::set_vao(unsigned vao)
{
	VAO = vao;
}


///-----------------------------------------------------------------------------------------
///-----------------------------------------------------------------------------------------
///-----------------------------------------IGNORE------------------------------------------
///-----------------------------------------------------------------------------------------
///-----------------------------------------------------------------------------------------
///
///Model::Model(const void* vertices, unsigned int v_size, const void* textCoord, unsigned int t_size, const unsigned int* indices, unsigned int i_count) {
///	this->onAttach2(vertices, v_size, textCoord, t_size, indices, i_count);
///}
///
///Model::~Model() {}
///
///void Model::onAttach2(const void* vertices, unsigned int v_size, const void* textCoord, unsigned int t_size, const unsigned int* indices, unsigned int i_count)
///{
///	unsigned int vVBO, tVBO, VAO, EBO;
///	glGenVertexArrays(1, &VAO);
///	glGenBuffers(1, &vVBO);
///	glGenBuffers(1, &EBO);
///	glGenBuffers(1, &tVBO);
///	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
///	glBindVertexArray(VAO);
///
///	glBindBuffer(GL_ARRAY_BUFFER, vVBO);
///	glBufferData(GL_ARRAY_BUFFER, v_size, vertices, GL_STATIC_DRAW);
///
///	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
///	glEnableVertexAttribArray(0);
///
///	glBindBuffer(GL_ARRAY_BUFFER, tVBO);
///	glBufferData(GL_ARRAY_BUFFER, t_size, textCoord, GL_STATIC_DRAW);
///
///	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
///	glEnableVertexAttribArray(1);
///
///	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
///	glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
///
///	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
///	glBindBuffer(GL_ARRAY_BUFFER, 0);
///
///	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
///	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
///
///	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
///	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
///	glBindVertexArray(0);
///	
///	this->VAO = VAO;
///	//this->vVBO = vVBO;
///	//this->tVBO = tVBO;
///	this->EBO = EBO;
///	this->i_count = i_count;
///	std::cout << "[MODEL]:: " << glGetError() << "\n";
///
///}