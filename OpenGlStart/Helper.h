#pragma once
#include <glew.h>
#include <stdio.h>
#include <stdlib.h>

#include <glfw3.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm.hpp>
#include <vec4.hpp>
#include <vec3.hpp>
#include <gtc/matrix_transform.hpp>

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);

