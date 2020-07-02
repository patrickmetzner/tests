#include <iostream>
#include <string>
#include <algorithm>


int n = 8;
std::string s = "UDDDUDUU";

int heightCounter = 0;
int valleyCounter = 0;

int CountValleys(int n, std::string s) {
    for (int i = 0; i < n; i++) {

        if (heightCounter == 0 && s[i] == 'D') {
            valleyCounter++;
        }

        if (s[i] == 'U') {
            heightCounter++;
        }
        else if (s[i] == 'D') {
            heightCounter--;
        }
    }

    return valleyCounter;
}

int main() {

    int res = CountValleys(n, s);

    std::cout << res << std::endl;

    std::cin.get();
}
