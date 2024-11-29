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
	int size = 9;
	int total_squares = size * size;
	std::mt19937 gen;

public:
	std::array<std::array<int, 9>, 9> grid {0};
	std::array<std::array<int, 9>, 9> solution {0};
	std::array<int, 9> nums = {1,2,3,4,5,6,7,8,9};

	// Constructor
	Board(std::mt19937 gen) : gen(gen) {}

	void print(const std::array<std::array<int, 9>, 9>& g) {
		/**
		 * Prints the passed in grid to the console.
		 */
		for (int r = 0; r < 9; ++r) {
			std::cout << '\n';
			for (int c = 0; c < 9; ++c) {
				std::cout << g[r][c] << ' ';
			}
		}
		std::cout << '\n';
	}
	
	int fill(std::array<std::array<int, 9>, 9>& g, bool check_repeats=false) {
		int solutions = 0;
		for (int r = 0; r < size; ++r) {
			std::shuffle(nums.begin(), nums.end(), gen);
			for (int c = 0; c < size; ++c) {
				// Make sure the cell is empty
				for (int n : nums) {	
					if (g[r][c] != 0) break;
					g[r][c] = n;
					if (!is_valid_move(r, c, g)) {
						g[r][c] = 0;
					}

				}
			}			
		}	
		return solutions;
	}

	void make_puzzle() {}

	void empty_cells(int num) {}  // For creating the puzzle

// private:

	std::array<int, 9> get_column(int col, 
							   const std::array<std::array<int, 9>, 9>& g) {
		/**
		 * Returns an array for the full column that the current cell is in.
		 */
		return {
			g[0][col], g[1][col], g[2][col],
			g[3][col], g[4][col], g[5][col],
			g[6][col], g[7][col], g[8][col]
		};
	}

	std::array<int, 9> get_square(int row, int col, 
							   const std::array<std::array<int, 9>, 9>& g) {
		/**
		 * Returns an array for the full square that the current cell is in.
		 */
		int r = (row / 3) * 3;  // Row start
		int c = (col / 3) * 3;  // Column start
		return {
			g[r][c],   g[r][c+1],   g[r][c+2],
			g[r+1][c], g[r+1][c+1], g[r+1][c+2],
			g[r+2][c], g[r+2][c+1], g[r+2][c+2]
		};
	}

	bool is_valid_group(const std::array<int, 9>& group) {
		/**
		 * Checks if there are any repeating numbers in the group passed in.
		 * Total will not iterate to 9 if there repeating non-zero integers.
		 * So, if total == 9, return true. Otherwise, return false.
		 */
		std::unordered_map<int, int> rates;
		for (int cell : group) {
			if (cell == 0) {
				rates[cell]++;
			} else {
				rates[cell] = 1;
			}
		}
		
		int total = 0;
		for (auto& [key, value] : rates) {
			total += value;
		}

		if (total == 9) return true;
		return false;
	}

	bool is_valid_move(int r, int c, const std::array<std::array<int, 9>, 9>& g) {
		/**
		 * Uses the is_valid_group function for row, column, and square of the
		 * selected cell. It returns true if it is a unique non-zero integer
		 * accross all three of these groups. Otherwise, returns false.
		 */

		// Check Row
		if (!is_valid_group(g[r])) {
			return false;	
		}
		// Check Column
		if (!is_valid_group(get_column(c, g))) {
			return false;
		}
		// Check Square
		if (!is_valid_group(get_square(r, c, g))) {
			return false;
		}
		return true;
	}

	bool is_unique() {
		return true;
	}

	bool is_full(const std::array<std::array<int, 9>, 9>& g) {
		/**
		 * Checks if the grid has any empty cells. If so return true, otherwise false.
		 */
		for (std::array<int, 9> row : g) {
			for (int cell : row) {
				if (cell == 0) {
					return false;
				}
			}
		}
		return true;
	}	

	int rand_num() {
		/**
		 * Returns a random number between 0 and 8 (inclusive).
		 */
		std::uniform_int_distribution<> dis(0, 8);
		return dis(gen);
	}
};
