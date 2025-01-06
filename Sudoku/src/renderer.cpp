#include "renderer.h"

#include <cassert>
#include <iostream>

GLFWwindow* Renderer::InitWindow() {
    GLFWwindow *window;
    assert(glfwInit());
    window = glfwCreateWindow(640, 480, "Sudoku", NULL, NULL);

    if (!window) {
		glfwTerminate();
        std::cout << "Unable to initialize window." << std::endl;
        assert(false);
	}

    glfwMakeContextCurrent(window);

    return window;
}
