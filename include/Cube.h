#ifndef CUBE_H
#define CUBE_H

#include <glm/glm.hpp>
#include "CubeType.h"

class Cube
{
public:

	explicit Cube(const glm::vec3& pos, CubeType type): pos(pos), type(type){}
	~Cube() = default;

    glm::vec3 getPos() const;
	CubeType getType();
private:
	glm::vec3 pos;
	CubeType type;
};


#endif