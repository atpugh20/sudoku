#pragma once

#include "GLFW/glfw3.h"

class Renderer {
public:
    Renderer() {}
    ~Renderer() {}

    GLFWwindow* InitWindow();
};
