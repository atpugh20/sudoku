#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>
#include <iostream>

#include "./board.cpp"

int main() {
	// Set up random
	std::random_device rd;
	std::mt19937 gen(rd());

	Board board = Board(gen);

	board.grid[1][1] = 1;
	/*board.grid[2][1] = 1;*/
	board.print();

	bool filled = board.fill();
	board.print();
	
	if (filled) {
		std::cout << "Complete grid!\n";
	} else {
		std:: cout << "Unsolvable...\n";
	}

	std::cout << "\nProgram completed." << std::endl;
    return 0;
}
