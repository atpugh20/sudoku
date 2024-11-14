#include <iostream>
#include <map>
#include <cstdlib>
#include <ctime>

#include "./board.cpp"

int main() {
	srand(time(NULL));

	Board board;	
	board.print();
	board.grid[0][8] = 1;
	board.print();
	board.solve();
	
	std::cout << "\nProgram completed." << std::endl;
    return 0;
}
