#ifndef MODEL_HPP
#define MODEL_HPP

#include <GL/glew.h>
#include "Mesh.h"

class Model
{
public:
	//TODO: Organizar isto private e n private
	
    Model() = default;
    Model(Mesh& mesh);
    ~Model() = default;
    void fill(Mesh& mesh);
    void addVBO(int dimenson, std::vector<float> data);
    void addEBO(std::vector<unsigned int> indices);
    void deleteData();
    unsigned int getIndicesCount() const;
    void bindEBO() const;
    void bindVAO() const;

    unsigned get_i_count() const;
    void set_vao(unsigned vao);
  
    //unsigned vao() const;
    //unsigned ebo() const;

private:

    unsigned int VBO_count = 0,
	VAO = 0,
	EBO = 0,
	i_count = 0;
    std::vector<unsigned int> VBOs;
};

#endif
