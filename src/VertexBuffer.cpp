#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    const float* vert = (const float*)data;
    std::cout << "[VertexBuffer]começar a iterar array de data\n";
    for (int i = 0; i < 10; ++i)
    {
        std::cout << i << ": " << vert[i] << "\n";
    }

    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    std::cout << "[VERTEXBUFFER]:: " << glGetError() << "\n";

}

VertexBuffer::VertexBuffer()
{
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}