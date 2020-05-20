#ifndef GLCore_h
#define GLCore_h

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <iostream>
#include <memory>
#include <string>

#include <Shader.hpp>
#include <camera.h>

#include "Chunk.h"
#include "Cube.h"
#include "Model.hpp"
#include "Renderer.h"
#include "World.h"


#endif
