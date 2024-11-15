#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <set>

class Board {
	int size;
	std::mt19937 gen;
	int total_squares;

public:	
	Board(std::mt19937 gen) : size(9), gen(gen), total_squares(size * size) {
		for (int i = 0; i < size; i++) {
			nums[i] = i + 1;
		}	
	}

	std::array<std::array<int,9>, 9> grid {0};
	std::array<int, 9> nums {0};

	void print() {
		for (std::array<int, 9> row : grid) {
			for (int c : row) {
				std::cout << c << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}

	bool is_valid() {
		/** 
		 * Checks if there are any repeated values in any
		 * of the rows, columns, or squares.
		 */

		// Check rows
		for (std::array<int, 9> row : grid) {
			std::set<int> unique(row.begin(), row.end());	
			if (row.size() != unique.size()) {
				return false;
			}
		}

		// Check columns
		for (int i = 0; i < 9; i++) {
			std::array<int, 9> column = get_column(i);
			std::set<int> unique(column.begin(), column.end());
			if (column.size() != unique.size()) {
				return false;
			}
		}

		// Handle the squares below
		// Check squares

		return true;
	}

	bool fill() {
		/**
		 * Fills in all of the empty cells to solve or fill the grid.
		 */
		std::shuffle(nums.begin(), nums.end(), gen);
		int row;
		int col;
		std::array<int, 9> full_column;
		std::array<int, 9> full_square;
		
		// Fill every empty cell
		for (int i = 0; i < total_squares; i++) {
			row = i / 9;
			col = i % 9;
	
			// Check if the cell is empty
			if (grid[row][col] == 0) {
				for (int val : nums) {
					// Check if val is already in the row
					if (!in_array(val, grid[row])) {	
						full_column = get_column(col);

						// Check if val is in the column
						if (!in_array(val, full_column)) {
							full_square = get_square(row, col);
							// Check if val is in the square
							if (!in_array(val, full_square)) {
								grid[row][col] = val;
								if (is_full()) {
									return true;
								} else {
									if(fill()){
										return true;
									}
								}
							}
						}
					}
				}
				grid[row][col] = 0;
				return false;
			}
		}
		return false;
	}

private:

	bool is_full() {
		/**
		 * Returns true if grid is filled, false if not.
		 */
		for (std::array<int, 9> row : grid) {
			for (int cell : row) {
				if (cell == 0) {
					return false;
				}
			}
		}
		return true;
	}

	std::array<int, 9> get_column(int col) {
		return {
			grid[0][col], grid[1][col], grid[2][col], 
			grid[3][col], grid[4][col], grid[5][col], 
			grid[6][col], grid[7][col], grid[8][col],
		};
	}

	std::array<int, 9> get_square(int row, int col) {
		/**
		 * Returns an array for the full square that the current cell is in.
		 */
		int r = (row / 3) * 3;  // row start
		int c = (col / 3) * 3;  // col start
		std::array<int, 9> square {
			grid[r][c], grid[r][c + 1], grid[r][c + 2],
			grid[r + 1][c], grid[r + 1][c + 1], grid[r + 1][c + 2],
			grid[r + 2][c], grid[r + 2][c + 1], grid[r + 2][c + 2],
		};
		return square;
	}

	bool in_array(int num, std::array<int, 9> squares) {
		/*
		 * Checks if num is found in squares. Returns true if so, false if not.
		 */
		bool is_found = false;
		if (std::find(squares.begin(), squares.end(), num) != squares.end()) {
			is_found = true;
		}
		return is_found;
	}

	int rand_num() {
		/**
		 * Returns a random integer between 0 and 8 inclusive
		 */
		std::uniform_int_distribution<> distr(0, 8);
		return distr(gen);
	}
}; 
