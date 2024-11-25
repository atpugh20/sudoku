#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <set>
#include <unordered_map>

class Board {
	/**
	 * The the board contains all data and methods relating
	 * to the numbers grid.
	 */
	int size;
	int total_squares;
	std::mt19937 gen;

public:
	std::array<std::array<int, 9>, 9> grid {0};
	std::array<std::array<int, 9>, 9> solution {0};
	std::array<int, 9> nums = {1,2,3,4,5,6,7,8,9};

	// Constructor
	Board(std::mt19937 gen) : gen(gen) {}
	
	void fill(std::array<std::array<int, 9>, 9>& g) {}

	void make_puzzle() {}

	void empty_cells(int num) {}

private:
	std::array<int, 9> get_column(int col, 
							   const std::array<std::array<int, 9>, 9>& g) {
		return {
			g[0][col], g[1][col], g[2][col],
			g[3][col], g[4][col], g[5][col],
			g[6][col], g[7][col], g[8][col]
		};
	}

	std::array<int, 9> get_square(int row, int col, 
							   std::array<std::array<int, 9>, 9>& g) {
		return {};
	}

	bool is_valid() {
		return true;
	}

	bool is_unique() {
		return true;
	}

	bool is_full(const std::array<std::array<int, 9>, 9>& g) {
		return true;
	}

	bool in_group(int n, const std::array<int, 9>& group) {
		return true;	
	}

	int rand_num() {
		// Returns a random number between 0 and 8 (inclusive)
		std::uniform_int_distribution<> dis(0, 8);
		return dis(gen);
	}
}; 
