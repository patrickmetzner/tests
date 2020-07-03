/*

Complexity analysis
	when WHILE(n>7) loop is not implemented{
		3 nested loops with O(n) complexity = O(n^3)
	}

    when WHILE(n>7) is implemented{
		O(n) + [ 2 nested O(n) loops ]  =  O(n) + O(n^2)  =   O(n^2)
	}

*/

#include <iostream>
#include <string>
#include <array>

#if 0			//   1 for input00 and 0 for input25
const int n = 3;
bool input0 = 1;
bool input25 = 0;
#else
const int n = 5;
bool input0 = 0;
bool input25 = 1;
#endif

const int r = 6;
const int c = 7;

void PrintGrid(std::array<std::array<std::string, r>, 3>& stateT, int element);
std::array<std::string, r> bomberMan(std::array<std::array<std::string, r>, 3>& stateT, const int& n);

int main() {

	std::array<std::string, r> initialState;
	if (input0) {
		initialState[0] = ".......";
		initialState[1] = "...O...";
		initialState[2] = "....O..";
		initialState[3] = ".......";
		initialState[4] = "OO.....";
		initialState[5] = "OO.....";
	}
	if (input25) {
		initialState[0] = ".......";
		initialState[1] = "...O.O.";
		initialState[2] = "....O..";
		initialState[3] = "..O....";
		initialState[4] = "OO...OO";
		initialState[5] = "OO.O...";
	}

	char emptyString[c];
	for (int i = 0; i < c; i++) {
		emptyString[i] = '.';
	}

	std::array<std::string, r> emptyArray;
	for (int i = 0; i < r; i++) {
		emptyArray[i] = emptyString;
	}

	std::array<std::array<std::string, r>, 3> stateT; // this array stores the grid state for T, T-1, T-2. T is the present state while T-1 and T-2 are past states. 
	stateT[1] = emptyArray;
	stateT[0] = stateT[2] = initialState;

	std::cout << "Initial State " << std::endl;
	PrintGrid(stateT, 2);

	bomberMan(stateT, n);

	std::cin.get();
}

std::array<std::string, r> bomberMan(std::array<std::array<std::string, r>, 3>& stateT,const int& n) {

	int t = 2; // t is set to 2 so it is more intuitive to think about T-1 and T-2 seconds
	int i, j;
	bool firstBatch=false;

	int ajustedIterator = n;
	int ajustedI_n = 0;
	if (n > 3) {
		while (ajustedIterator > 7) { 
			ajustedIterator -= 7;
			ajustedI_n += 7;
		}
	}
	
	for (int i_n = 1; i_n <= ajustedIterator; i_n++) {																			
		if ((i_n % 2) == 0) {
			firstBatch = !firstBatch;
		}

		for (i = 0; i < r; i++) {																								
			for (j = 0; j < c; j++) {																							
				int up, down, left, right;
				up = i - 1;
				down = i + 1;
				left = j - 1;
				right = j + 1;
				
				if ((i_n % 2)==0) {
					//std::cout << "i_n % 2 = 0" << std::endl;
					if ((i_n % 4)==0) { // when [(i_n % 4) == 0], we will reallocate bombs that were planted initially 
						//std::cout << "i_n % 4 = 0" << std::endl;
						if (stateT[t][i][j] == '.') { 
							stateT[t][i][j] = 'O';
							stateT[t - 2][i][j] = 'O';
						}
					}
					if ((i_n % 4) != 0) {           // when [(i_n % 4) != 0], we will reallocate bombs that were planted in i_n == 2 seconds
						//std::cout << "i_n % 4 != 0" << std::endl;
						if (stateT[t][i][j] == '.') { 
							stateT[t][i][j] = 'O';
							stateT[t - 1][i][j] = 'O';
						}
					}
				}
				if(i_n>2 && ((i_n % 2) != 0)){
					//std::cout << "i_n % 2 != 0" << std::endl;
					if (firstBatch==true){
						//std::cout << "firstBatch" << std::endl;
						if (stateT[t - 2][i][j] == 'O') { 
							stateT[t - 2][i][j] = '.'; //clear stateT[t - 2]
							stateT[t][i][j] = '.';
							if (up >= 0) {
								stateT[t][up][j] = '.';
								stateT[t - 1][up][j] = '.'; //clear stateT[t - 1]
							}
							if (down < r) {
								stateT[t][down][j] = '.';
								stateT[t - 1][down][j] = '.'; //clear stateT[t - 1]
							}
							if (left >= 0) {
								stateT[t][i][left] = '.';
								stateT[t - 1][i][left] = '.'; //clear stateT[t - 1]
							}
							if (right < c) {
								stateT[t][i][right] = '.';
								stateT[t - 1][i][right] = '.'; //clear stateT[t - 1]
							}
						}
					}
					if (firstBatch == false) {
						//std::cout << "not firstBatch" << std::endl;
						if (stateT[t - 1][i][j] == 'O') { 
							stateT[t - 1][i][j] = '.'; //clear stateT[t - 1]
							stateT[t][i][j] = '.';
							if (up >= 0) {
								stateT[t][up][j] = '.';
								stateT[t - 2][up][j] = '.'; //clear stateT[t - 2]
							}
							if (down < r) {
								stateT[t][down][j] = '.';
								stateT[t - 2][down][j] = '.'; //clear stateT[t - 2]
							}
							if (left >= 0) {
								stateT[t][i][left] = '.';
								stateT[t - 2][i][left] = '.'; //clear stateT[t - 2]
							}
							if (right < c) {
								stateT[t][i][right] = '.';
								stateT[t - 2][i][right] = '.'; //clear stateT[t - 2]
							}
						}
					}
				}			
			}
		}

		std::cout << "i_n = " << i_n + ajustedI_n << std::endl;
		PrintGrid(stateT, t);
	}

	return stateT[t];
}

void PrintGrid(std::array<std::array<std::string, r>, 3>& stateT, int element) {
	int t = element;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			std::cout << stateT[t][i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
