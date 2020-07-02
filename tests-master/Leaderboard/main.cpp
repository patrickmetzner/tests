#include <iostream>
#include <vector>
#include <array>

const int nPlayers = 6;
std::array<int, nPlayers> leaderBoard = { 100, 90, 90, 80, 75, 60 };
const int nAlice = 5;
std::array<int, nAlice> aliceScore = { 50, 65, 77, 90, 102 };

std::array<int, nAlice> climbingLeaderboard(std::array<int, leaderBoard.size()> leaderBoard, std::array<int, aliceScore.size()> aliceScore) {

	std::array<int, aliceScore.size()> res;
	std::vector<int> clearedLeaderBoard; 
	int i_cLB=0;

	clearedLeaderBoard.push_back(leaderBoard[0]);
	for (int i = 1; i < leaderBoard.size(); i++) {
		if (leaderBoard[i] != clearedLeaderBoard[i_cLB]) {
			clearedLeaderBoard.push_back(leaderBoard[i]);
			i_cLB++;
		}
	}

	for (int i = 0; i<aliceScore.size(); i++) {
		int count = 0;
		while (clearedLeaderBoard[count] > aliceScore[i]) {
			count++;
			if (count == clearedLeaderBoard.size())
				break;
		}
		res[i] = count+1;
	}

	for (int i = 0; i < res.size(); i++) {
		std::cout << res[i] << std::endl;
	}

	return res;
}

int main() {

	climbingLeaderboard(leaderBoard, aliceScore);

	std::cin.get();
}
