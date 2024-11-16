#include <algorithm>
#include <iostream>
#include <random>

#include "./board.cpp"

int main() {
	
	// Set up random
	std::random_device rd;
	std::mt19937 gen(rd());

	Board board = Board(gen);
	board.make_puzzle(0);	
		
	board.print();
	
	for (int n : board.nums) std::cout << n << std::endl;
	std::shuffle(board.nums.begin(), board.nums.end(), gen);
	for (int n : board.nums) std::cout << n << std::endl;

	int wins = 0;
	for (int i = 0; i < 100; i++) {
		if(board.can_win()) {
			wins++;
			std::cout << "Can win!" << std::endl;
		} else {
			std::cout << "Cannot win!" << std::endl;
		}
	}
	std::cout << wins << std::endl;
	


	/*if(board.is_valid_board()) {*/
	/*	std::cout << "valid" << std::endl;*/
	/*} else {*/
	/*	std::cout << "not valid" << std::endl;*/
	/*}*/

	/*bool filled = board.fill();*/	
	/*if (filled) {*/
	/*	std::cout << "Complete grid!\n";*/
	/*} else {*/
	/*	std:: cout << "Unsolvable...\n";*/
	/*}*/

	std::cout << "\nProgram completed." << std::endl;
    return 0;
}
