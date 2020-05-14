#include "Renderer.h"



Renderer::Renderer() : r_shader("shaders/shader.vs", "shaders/shader.fs") { }

Renderer::~Renderer() { }

void Renderer::draw(Model model)
{
	this->r_shader.use();
	
	glBindVertexArray(model.vao());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.ebo());
	std::cout << "[RENDERER::draw]:: " << glGetError() << "\n";
	
	
	GLCall(
		glDrawElements(GL_TRIANGLES, model.get_i_count(), GL_UNSIGNED_INT, 0);
	);
}

void Renderer::setMatrix(glm::mat4 projection, glm::mat4 view, glm::mat4 model) const
{
	this->r_shader.use();
	this->r_shader.setMat4("projection", projection);
	this->r_shader.setMat4("view", view);
	this->r_shader.setMat4("model", model);
	std::cout << "[RENDERER::setMatrix]:: " << glGetError() << "\n";
	
}

void Renderer::set_r_shader(const Shader& r_shader)
{
	this->r_shader = r_shader;
}



