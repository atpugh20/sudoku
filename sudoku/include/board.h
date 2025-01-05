#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <unordered_map>

class Board {
/**
 * The the board contains all data and methods relating
 * to the numbers grid.
 */
private:
	int size = 9;
	int total_squares = size * size;
	std::mt19937 gen;

public:
	std::array<std::array<int, 9>, 9> grid {0};
	std::array<std::array<int, 9>, 9> solution {0};
	std::array<int, 9> nums = {1,2,3,4,5,6,7,8,9};

	Board(std::mt19937 gen) : gen(gen) {}

	void Print(const std::array<std::array<int, 9>, 9>& g);
	bool Fill(std::array<std::array<int, 9>, 9>& g);
	bool Solve(std::array<std::array<int, 9>, 9>& g, int& counter);
	void MakePuzzle(int goal_clues);

	std::array<int, 9> GetColumn(int col, 
		const std::array<std::array<int, 9>, 9>& g);

	std::array<int, 9> GetSquare(int row, int col,
		const std::array<std::array<int, 9>, 9>& g);

	bool IsValidGroup(const std::array<int, 9>& group);

	bool IsValidMove(int r, int c, const std::array<std::array<int, 9>, 9>& g);

	bool IsSameGrid(const std::array<std::array<int, 9>, 9>& g1, 
		const std::array<std::array<int, 9>, 9>& g2);
	
	bool IsFull(const std::array<std::array<int, 9>, 9>& g);

	inline int RandNum() {
		/**
		 * Returns a random number between 0 and 8 (inclusive).
		 */
		std::uniform_int_distribution<> dis(0, 8);
		return dis(gen);
	}

};
