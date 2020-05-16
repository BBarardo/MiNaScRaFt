#pragma once

#include "ChunkMesh.h"
#include "Shader.hpp"
#include "Model.hpp"
#include "camera.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();x;ASSERT(GLLogCall(#x,__FILE__,__LINE__));



static void GLClearError()
{
	
	while (GLenum error = glGetError())
		std::cout << "[CLEANING]::" << error << "\n";
		//std::cout << "estou ca dentro";
}

static bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << ")\n"
			<< "Function: " << function << "\n"
			<< "File: " << file << "\n"
			<< "Line: " << line << "\n";
		return false;
	}
	return true;
}

class Renderer
{
public:
	Renderer();
	~Renderer();
	void addChunkMesh(const ChunkMesh& mesh);
	void render(const Camera& camera);
	void draw(Model model);
	void setMatrix(glm::mat4 projection, glm::mat4 view, glm::mat4 model) const;


	void set_r_shader(const Shader& r_shader);
private:

	std::vector<const ChunkMesh*> r_chunks;

	Shader r_shader;
};
