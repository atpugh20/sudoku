#include "board.h"

void Board::Print(const std::array<std::array<int, 9>, 9>& g) {
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

bool Board::Fill(std::array<std::array<int, 9>, 9>& g) {
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
				if (IsValidMove(r, c, g)) {
					if (IsFull(g)) {
						return true;
					} else {
						if (Fill(g)) {
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

bool Board::Solve(std::array<std::array<int, 9>, 9>& g, int& counter) {
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
				if (IsValidMove(r, c, g)) {
					if (IsFull(g)) {
						counter++;
						break;
					} else {
						if (Solve(g, counter)) {
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

void Board::MakePuzzle(int goal_clues) {
	/**
	 * Create the puzzle by removing numbers from the solution one by one
	 * and ensuring that there is a unique solution each time.
	 */
	int r, c, original;
	int current_clues;
	std::array<std::array<int, 9>, 9> temp;
	
	// Create the solution
	Fill(solution);
	grid = solution;
	
	while (current_clues != goal_clues) {
		// Get non-zero cell	
		r = RandNum();
		c = RandNum();
		while (grid[r][c] == 0) {
			r = RandNum();
			c = RandNum();
		}
		
		// Save original value of cell and remove it from grid
		original = grid[r][c];
		grid[r][c] = 0;
		temp = grid;
		
		// Solve from current point
		int counter = 0;
		Solve(temp, counter);
		
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

std::array<int, 9> Board::GetColumn(int col, 
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

std::array<int, 9> Board::GetSquare(int row, int col, 
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

bool Board::IsValidGroup(const std::array<int, 9>& group) {
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

bool Board::IsValidMove(int r, int c, const std::array<std::array<int, 9>, 9>& g) {
	/**
	 * Uses the is_valid_group function for row, column, and square of the
	 * selected cell. It returns true if it is a unique non-zero integer
	 * accross all three of these groups. Otherwise, returns false.
	 */

	// Check Row
	if (!IsValidGroup(g[r])) {
		return false;	
	}
	// Check Column
	if (!IsValidGroup(GetColumn(c, g))) {
		return false;
	}
	// Check Square
	if (!IsValidGroup(GetSquare(r, c, g))) {
		return false;
	}
	return true;
}

bool Board::IsSameGrid(const std::array<std::array<int, 9>, 9>& g1,
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

bool Board::IsFull(const std::array<std::array<int, 9>, 9>& g) {
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
