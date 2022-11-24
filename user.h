#include<iostream>
#include <iomanip>
#include <string>
#include <algorithm>

struct process {
    const size_t ID;
    const std::wstring NAME;
    process(size_t id, std::wstring name) : ID(id), NAME(name) {};
};

class User {
public:
    void printProcesses();
    void killerProcess(std::string name);
    const std::string killer_path = "/home/tatti/OS/lab4lin/killer/cmake-build-debug/killer";
};

void printProcesses() {
    std::cout << '\n';
    system("ps -e");
    std::cout << '\n';
}

void killerProcess(std::string name) {
    system((killer_path + " " + name).c_str());
}