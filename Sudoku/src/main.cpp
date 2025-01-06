#include "GLFW/glfw3.h"

#include "board.h"
#include "renderer.h"

int main() {
	
	// Set up window
	Renderer renderer;
	GLFWwindow* window = renderer.InitWindow();
	
	// Set up random
	std::random_device rd;
	std::mt19937 gen(rd());

	const unsigned short clue_count = 40;
	// Easy    = 40
	// Medium  = 35
	// Hard    = 30
	// Expert  = 25 

	Board board = Board(gen);
	board.MakePuzzle(clue_count);

	board.Print(board.grid);
	board.Print(board.solution);

	int clues = 0;

	for (std::array<int, 9> r : board.grid) {
		for (int c : r) {
			if (c != 0) clues++;
		}
	}

	std::cout << clues << '\n';

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();

	std::cout << "\nProgram completed." << std::endl;
	return 0;
}