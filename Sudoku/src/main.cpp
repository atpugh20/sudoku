#include "Board.h"
#include "Renderer.h"

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
    {
        Renderer renderer;

        // Vertices
        float positions[] = {
            -0.5f, -0.5f, // 0
             0.0f,  0.0f, // 1
             0.5f, -0.5f, // 2
             0.5f,  0.5f, // 3
        };
        unsigned int positionCount = sizeof(positions) / sizeof(positions[0]);
        
        unsigned int indices[] = {
            0, 1,
            1, 2,
            0, 3
        };
        unsigned int indexCount = sizeof(indices) / sizeof(indices[0]);


        /*unsigned int buffer;
        GLCall(glGenBuffers(1, &buffer));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
        GLCall(glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW));

        GLCall(glEnableVertexAttribArray(0));
        GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));*/


        // Index Array
        

        IndexBuffer ib(indices, indexCount);
        Shader shader("res/shaders/line.shader");

        shader.Bind();

        ib.Unbind();
        shader.Unbind();

        float inc = 0.01f;

        // Draw Loop
        while (!glfwWindowShouldClose(window)) {
            renderer.Clear();

            int c = 1;
            
            if (positions[c] < -0.5f || positions[c] > 0.5f) 
                inc *= -1;
            
            positions[c] += inc;

            VertexArray va;
            VertexBuffer vb(positions, positionCount * sizeof(float));
            VertexBufferLayout layout;
            layout.Push<float>(2);
            va.AddBuffer(vb, layout);
            
            shader.Bind();
            renderer.Draw(va, ib, shader);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
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