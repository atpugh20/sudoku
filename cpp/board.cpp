#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <unordered_map>

class Board {
	int size;
	std::mt19937 gen;
	int total_squares;

public:	
	Board(std::mt19937 gen) : size(9), gen(gen), total_squares(size * size) {
		for (int i = 0; i < size; i++) {
			nums[i] = i + 1;
		}
		std::shuffle(nums.begin(), nums.end(), gen);
	}

	std::array<std::array<int,9>, 9> grid {0};
	std::array<int, 9> nums {0};

	void print() {
		/**
		 * Prints the grid to the console as a matrix
		 */
		for (std::array<int, 9> row : grid) {
			for (int c : row) {
				std::cout << c << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}

	void get_move() {
		/**
		 * Gets a move from the user. Loops until the move is valid.
		 */
		int move;
		int move_row;
		int move_col;
		bool valid;

		while (true) {
			// Get user's move
			std::cout << "Input the col then row:\n";
			std::cin >> move_col;
			std::cin >> move_row;
			std::cout << "Input the number you wish to fill\n";
			std::cin >> move;

			// Check if the move is valid
			if (grid[move_row][move_col] == 0) {
				grid[move_row][move_col] = move;
				if (is_valid_board()) {
					if (can_win()) {
						valid = true;
					} else {
						valid = false;
						grid[move_row][move_col] = 0;
					}
				} else {
					valid = false;
					grid[move_row][move_col] = 0;
				}
			} else {
				valid = false;
			}

			// Handle loop break
			if (valid) {
				break;
			} else {
				std::cout << "Invalid move!" << std::endl;
				print();
			}
		}
	}

	void make_puzzle(int difficulty) {
		int clues;
		switch (difficulty) {
			case 1: clues = 35; break;  // Medium
			case 2: clues = 30; break;  // Hard
			case 3: clues = 25; break;  // Expert
			default: clues = 40; break; // Easy
		}
		
		while (true) {
			fill();
			while(true) {		
				int zeros = 0;
				grid[rand_num()][rand_num()] = 0;

				for (std::array<int, 9> row : grid) {
					for (int cell : row) {
						if (cell == 0) {
							zeros++;
						}
					}
				}
				if (zeros == 81 - clues) {
					break;
				}
			}

			if (can_win()) {
				break;
			} else {
				grid = {0};
			}
		}

		print();
	}

	bool is_valid_board() {
		/** 
		 * Checks if there are any repeated values in any
		 * of the rows, columns, or squares.
		 */

		// Check rows
		for (std::array<int, 9> row : grid) {
			if (!is_valid(row)) {
				return false;
			}	
		}

		// Check columns
		for (int i = 0; i < 9; i++) {
			std::array<int, 9> column = get_column(i);
			if (!is_valid(column)) {
				return false;
			}
		}

		// Check squares
		for (int i = 0; i < 81; i += 3) {
			int row =  i / 9;
			int col = i % 9;
			std::array<int, 9> square = get_square(row, col);
			if (!is_valid(square)) {
				return false;
			}
		}

		return true;
	}

	bool fill() {
		/**
		 * Fills in all of the empty cells to solve or fill the grid.
		 */
		std::array<int, 9> full_column;
		std::array<int, 9> full_square;
		
		// Fill every empty cell
		for (int i = 0; i < total_squares; i++) {
			int row = i / 9;
			int col = i % 9;
	
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

	bool can_win() {
		std::array<std::array<int, 9>, 9> temp = grid;	
		bool winnable;	
		if (fill()) {
			winnable = true;
		} else {
			winnable = false;
		}
		grid = temp;
		return winnable;
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

	bool is_valid(const std::array<int, 9>& cells) {
		/**
		 * Uses the rates of each number in the array to check if it is valid.
		 * If the rate = 9, then we return true. Otherwise, we return false.
		 */
		std::unordered_map<int, int> rates;
		int rate = 0;
		for (int c : cells) {
			if (c == 0) {
				rates[c]++;
			} else {
				rates[c] = 1;
			}
		}
		// Sum up the rates
		for (auto& [key, value] : rates) {
			rate += value;
		}

		if (rate != 9) {
			return false;
		}
		return true;
	}

	bool in_array(int num, std::array<int, 9> cells) {
		/*
		 * Checks if num is found in squares. Returns true if so, false if not.
		 */
		bool is_found = false;
		if (std::find(cells.begin(), cells.end(), num) != cells.end()) {
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
