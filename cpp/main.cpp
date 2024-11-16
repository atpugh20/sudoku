#include <iostream>
#include <random>

#include "./board.cpp"

int main() {
	
	// Set up random
	std::random_device rd;
	std::mt19937 gen(rd());

	Board board = Board(gen);

	board.make_puzzle(1);

	/*bool filled = board.fill();*/	
	/*if (filled) {*/
	/*	std::cout << "Complete grid!\n";*/
	/*} else {*/
	/*	std:: cout << "Unsolvable...\n";*/
	/*}*/

	std::cout << "\nProgram completed." << std::endl;
    return 0;
}
