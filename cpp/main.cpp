#include "./board.cpp"

int main() {
	
	// Set up random
	std::random_device rd;
	std::mt19937 gen(rd());

	Board board = Board(gen);

	std::cout << "\nProgram completed." << std::endl;
    return 0;
}
