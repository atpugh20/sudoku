#include "./board.cpp"

int main() {
	
	// Set up random
	std::random_device rd;
	std::mt19937 gen(rd());

	Board board = Board(gen);
	board.make_puzzle(40);

	board.print(board.grid);
	board.print(board.solution);

	if (board.is_full(board.grid)) {
		std::cout << "FULL\n";
	} else {
		std::cout << "NOT\n";
	}

	std::cout << "\nProgram completed." << std::endl;
    return 0;
}
