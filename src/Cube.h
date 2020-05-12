#ifndef CUBE_H
#define CUBE_H
#include <glm/glm.hpp>

class Cube
{
public:
    static const float vertices[288];
	
	static const float vertices2[72];
	static const float textCords[8];
	static const unsigned int indices[36];

	explicit Cube(const glm::vec3& pos): pos(pos){}
	~Cube();

    glm::vec3 getPos() const;
private:
	glm::vec3 pos;
};


#endif