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
	
	bool fill(std::array<std::array<int, 9>, 9>& g) {
		/**
		 * Fills the passed in grid with random numbers from the
		 * nums array.
		 */
		std::shuffle(nums.begin(), nums.end(), gen);
		for (int i = 0; i < total_squares; ++i) {
			int r = i / 9;
			int c = i % 9;
			// Make sure the cell is empty
			if (g[r][c] == 0) {
				for (int n : nums) {	
					g[r][c] = n;
					if (is_valid_move(r, c, g)) {
						if (is_full(g)) {
							return true;
						} else {
							if (fill(g)) {
								return true;
							}
						}
					}
				}
				g[r][c] = 0;
				return false;
			}	
		}	
		return false;
	}

	bool solve(std::array<std::array<int, 9>, 9>& g, int& counter) {
		/**
		 * Solves the input grid while keeping track of the number of
		 * solutions.
		 */
		for (int i = 0; i < total_squares; ++i) {
			int r = i / 9;
			int c = i % 9;
			// Make sure the cell is empty
			if (g[r][c] == 0) {
				for (int n : nums) {	
					g[r][c] = n;
					if (is_valid_move(r, c, g)) {
						if (is_full(g)) {
							counter++;
							break;
						} else {
							if (solve(g, counter)) {
								return true;		
							}
						}
					}
				}
				g[r][c] = 0;
				return false;
			}	
		}	
		return false;
	}

	void make_puzzle(int goal_clues) {
		/**
		 * Create the puzzle by removing numbers from the solution one by one
		 * and ensuring that there is a unique solution each time.
		 */
		int r, c, original;
		int current_clues;
		std::array<std::array<int, 9>, 9> temp;
		
		// Create the solution
		fill(solution);
		grid = solution;
		
		while (current_clues != goal_clues) {
			// Get non-zero cell	
			r = rand_num();
			c = rand_num();
			while (grid[r][c] == 0) {
				r = rand_num();
				c = rand_num();
			}
			
			// Save original value of cell and remove it from grid
			original = grid[r][c];
			grid[r][c] = 0;
			temp = grid;
			
			// Solve from current point
			int counter = 0;
			solve(temp, counter);
			
			// If there are more solutions, revert the cell back to original value
			if (counter != 1) {
				grid[r][c] = original;
			}

			// Check number of clues
			current_clues = 0;
			for (std::array<int, 9> r : grid) {
				for (int c : r) {
					if (c != 0) current_clues++;
				}
			}
		}
	}

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

	bool is_same_grid(const std::array<std::array<int, 9>, 9>& g1,
				      const std::array<std::array<int, 9>, 9>& g2) {
		/**
		 * Checks if the two passed in grids are the same. This is used to
		 * check for a unique solution.
		 */
		for (int r = 0; r < size; ++r) {
			for (int c = 0; c < size; ++c) {
				if (g1[r][c] != g2[r][c]) {
					return false;
				}
			}
		}
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
