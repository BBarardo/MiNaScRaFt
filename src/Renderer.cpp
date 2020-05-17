#include "Renderer.h"



Renderer::Renderer() : r_shader("shaders/shader.vs", "shaders/shader.fs") { }

Renderer::~Renderer() { }

void Renderer::addChunkMesh(const ChunkMesh& mesh)
{
	const ChunkMesh& chMesh = mesh;
	r_chunks.push_back(&chMesh);
}

void Renderer::render(const Camera& camera)
{
	r_shader.use();
	//glEnable(GL_CULL_FACE);
	
	//BlockDatabase::get().textureAtlas.bindTexture();

	//r_shader.loadProjectionViewMatrix(camera.getProjectionViewMatrix());
	
	for (const ChunkMesh* mesh : r_chunks)
	{
		const ChunkMesh& m = *mesh;

		
		m.getModel().bindVAO();
		glDrawElements(GL_TRIANGLES, m.getModel().get_i_count(), GL_UNSIGNED_INT, nullptr);
		std::cout << "[RENDERER::render]:: " << glGetError() << "\n";
	}

	//r_chunks.clear();
}

//void Renderer::draw(Model model)
//{
//	this->r_shader.use();
//	
//	glBindVertexArray(model.vao());
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.ebo());
//	//std::cout << "[RENDERER::draw]:: " << glGetError() << "\n";
//	
//	
//	//GLCall(
//		glDrawElements(GL_TRIANGLES, model.get_i_count(), GL_UNSIGNED_INT, 0);
//		std::cout << "[RENDERER::render]:: " << glGetError() << "\n";
//	//);
//}

void Renderer::setMatrix(glm::mat4 projection, glm::mat4 view, glm::mat4 model) const
{
	this->r_shader.use();
	this->r_shader.setMat4("projection", projection);
	this->r_shader.setMat4("view", view);
	this->r_shader.setMat4("model", model);
	//std::cout << "[RENDERER::setMatrix]:: " << glGetError() << "\n";
	
}

//for debug
void Renderer::set_r_shader(const Shader& r_shader)
{
	this->r_shader = r_shader;
}



