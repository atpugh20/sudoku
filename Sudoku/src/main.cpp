#include "board.h"
#include "renderer.h"

int main(void) {
	
	int window_w = 600;
	int window_h = 600;

	GLFWwindow* window;

    // Create a window
	
	if (!glfwInit()) return -1;
  
	window = glfwCreateWindow(window_h, window_h, "Sudoku", NULL, NULL);
    if (!window) {
		glfwTerminate();
		return -1;
	}

    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
	if (GLEW_OK != err)
		std::cout << "GLEW_OKAY != err" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	Renderer renderer;

	// Vertices
	float positions[6] = {
		-0.5f, -0.5f,
		 0.0f,  0.5f,
		 0.5f, -0.5f
	};

	unsigned int buffer;
	GLCall(glGenBuffers(1, &buffer));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
	GLCall(glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW));

	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));

	// Index

	// Draw Loop
	while (!glfwWindowShouldClose(window)) {
		renderer.Clear();

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	std::cout << "\nProgram completed." << std::endl;
	return 0;
}

// SUDOKU CODE

//// Set up random
//std::random_device rd;
//std::mt19937 gen(rd());

//const unsigned short clue_count = 40;
//// Easy    = 40
//// Medium  = 35
//// Hard    = 30
//// Expert  = 25 

//Board board = Board(gen);
//board.MakePuzzle(clue_count);

//board.Print(board.grid);
//board.Print(board.solution);

//int clues = 0;

//for (std::array<int, 9> r : board.grid) {
//	for (int c : r) {
//		if (c != 0) clues++;
//	}
//}

//std::cout << clues << '\n';