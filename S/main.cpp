#include <iostream>
#include <sstream>

int main() {
    int current_number;
    int sum = 0;
    std::string s;
    std::getline(std::cin, s);
    std::stringstream ss(s);
    while(ss >> current_number) {
        sum += current_number;
    }
    std::cout << sum << std::endl;
    return 0;
}