#include "Model.hpp"

#include <iostream>

Model::Model(const void* vertices, unsigned int v_size, const void* textCoord, unsigned int t_size, const unsigned int* indices, unsigned int i_count) {
	this->onAttach2(vertices, v_size, textCoord, t_size, indices, i_count);
}

Model::~Model() {}

void Model::onAttach2(const void* vertices, unsigned int v_size, const void* textCoord, unsigned int t_size, const unsigned int* indices, unsigned int i_count)
{
	unsigned int vVBO, tVBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vVBO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &tVBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, vVBO);
	glBufferData(GL_ARRAY_BUFFER, v_size, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, tVBO);
	glBufferData(GL_ARRAY_BUFFER, t_size, textCoord, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_count * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
	
	this->VAO = VAO;
	this->vVBO = vVBO;
	this->tVBO = tVBO;
	this->EBO = EBO;
	this->i_count = i_count;
	std::cout << "[MODEL]:: " << glGetError() << "\n";

}

unsigned Model::get_i_count() const
{
	return i_count;
}

void Model::set_vao(unsigned vao)
{
	VAO = vao;
}

void Model::bindVAO()
{
	glBindVertexArray(this->VAO);
}

void Model::bindEBO()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
}

//////Vertices 3 a 3 ||  texturas 2 a 2
////void Model::onAttach(const void* vertices,unsigned int v_size, const void* textCoord,unsigned int t_size, const unsigned int* indices, unsigned int i_count)
////{
////	const unsigned int* vert = (const unsigned int*)indices;
////
////	std::cout << "começar a iterar array de vert\n";
////	for (int i = 0; i < 8; ++i)
////	{
////		std::cout << vert[i] << "\n";
////	}
////
////	glEnable(GL_DEPTH_TEST);
////
////	VA = VertexArray(); // checked
////	vVB = VertexBuffer(); // checked
////	tVB = VertexBuffer(); // checked
////	IB = IndexBuffer(); // checked
////	
////	VA.bind();
////	vVB = VertexBuffer(vertices, v_size);
////	vVB.bind();
////	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
////	glEnableVertexAttribArray(0);
////	
////	tVB = VertexBuffer(textCoord, t_size);
////	tVB.bind();
////	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
////	glEnableVertexAttribArray(1);
////
////	glBindBuffer(GL_ARRAY_BUFFER, 0);
////	glBindVertexArray(0);
////
////	IB = IndexBuffer(indices, i_count);
////}
////
////VertexArray Model::get_VA() const
////{
////	return VA;
////}
////IndexBuffer Model::get_IB() const
////{
////	return IB;
////}

unsigned Model::vao() const
{
	return VAO;
}

unsigned Model::ebo() const
{
	return EBO;
}




//void Model::onAttach()
//{
//	glEnable(GL_DEPTH_TEST);
//
//	glGenVertexArrays(1, &m_VA);
//	glBindVertexArray(m_VA);
//
//	float vertices[] = {
//		-0.5f, -0.5f, 0.0f,
//		 0.5f, -0.5f, 0.0f,
//		 0.5f,  0.5f, 0.0f,
//		-0.5f,  0.5f, 0.0f,
//		0.0f,  1.0f, 0.0f
//	};
//
//	glGenBuffers(1, &m_VB);
//	glBindBuffer(GL_ARRAY_BUFFER, m_VB);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
//
//	int indices[] = { 0, 1, 2, 2, 3, 0, 2, 3, 4 };
//	glGenBuffers(1, &m_IB);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IB);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	m_ibCount = sizeof(indices) / sizeof(int);
//}
//
//
//void Model::onDetach()
//{
//	glDeleteVertexArrays(1, &m_VA);
//	glDeleteBuffers(1, &m_VB);
//	glDeleteBuffers(1, &m_IB);
//}

//void Model::onUpdate()
//{
//	m_Shader.use();
//
//	glBindVertexArray(m_casaVA);
//	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
//}


//void Model::SetModelMatrix(const char* uniformName, glm::mat4 model) {
//	m_Shader.setMat4(uniformName, model);
//}
