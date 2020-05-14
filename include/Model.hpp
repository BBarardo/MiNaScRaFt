#ifndef MODEL_HPP
#define MODEL_HPP
#include <GL/glew.h>

class Model
{
public:
    Model();
    Model(const void* vertices, unsigned int v_size, const void* textCoord, unsigned int t_size, const unsigned int* indices, unsigned int i_count);
    ~Model();

    void onAttach(const void* vertices, unsigned int v_size, const void* textCoord, unsigned int t_size, const unsigned* indices, unsigned int i_size);
    void onAttach2(const void* vertices, unsigned int v_size, const void* textCoord, unsigned int t_size, const unsigned* indices, unsigned int i_size);
    void onDetach();
    void bindVAO();
    void bindEBO();
    unsigned get_i_count() const;
	
    //int get_m_ibCount() const;
	
    //void onUpdate();
    //void SetModelMatrix(const char*, glm::mat4);


    void set_vao(unsigned vao);
    unsigned vao() const;
    unsigned ebo() const;

    //IndexBuffer get_IB() const;
    //VertexArray get_VA() const;
private:
    //VertexArray VA;
    //IndexBuffer IB;
    //VertexBuffer vVB;
    //VertexBuffer tVB;

    unsigned int vVBO, tVBO, VAO, EBO, i_count;
};

#endif
