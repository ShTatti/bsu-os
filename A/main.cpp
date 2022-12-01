#include <iostream>
#include <sstream>

int main() {
    int current_number;
    int my_number = 26;
    std::string string;
    std::getline(std::cin, string);
    std::stringstream ss(string);
    while(ss >> current_number) {
        std::cout << current_number + my_number << " ";
    }

    std::cout << std::endl;
    return 0;
}