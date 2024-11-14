#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>

class Board {
	int size;
	std::array<int, 9> nums {0};

public:	
	Board() : size(9) {
		for (int i = 0; i < size; i++) {
			nums[i] = i + 1;
		}	
	}

	std::array<std::array<int,9>, 9> grid {0};

	void print() {
		for (std::array<int, 9> row : grid) {
			for (int c : row) {
				std::cout << c << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}

	void solve() {
		/**
		 * Fills in the entire grid
		 */
		int total_squares = size * size;
		
		// Find the next empty square
		for (int i = 0; i < total_squares; i++) {
			int row = i / 9;
			int col = i % 9;

			// Check if empty
			if (grid[row][col] == 0) {
				for (int val : nums) {
					// Check if the selected val is in the row
					if (!in_square_group(val, grid[row])) {
						std::cout << "Not in the row!\n";
					} 
				}
			} else {
				std::cout << "Filled\n";
			}	
		}
	}

	int rand_num() {
		/**
		 * Returns a random integer between 0 and 8 inclusive
		 */
		return rand() /  (RAND_MAX + 1.0) * 9;
	}

	bool in_square_group(int num, std::array<int, 9> squares) {
		/*
		 * Checks if num is found in squares. Returns true if so, false if not.
		 */
		bool is_found = false;
		if (std::find(squares.begin(), squares.end(), num) != squares.end()) {
			is_found = true;
		}
		return is_found;
	}


}; 
