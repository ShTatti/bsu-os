#include <iostream>
#include <string>
#include <sstream>

class Killer {
public:
    bool killProcessById(unsigned long long id);
    bool killProcessByName(const std::string& name);
    void printState(bool killed, const std::string& name);
};
bool killProcessById(unsigned long long id) {
    std::string command = "kill " + std::to_string(id);
    auto ret = system(command.c_str());
    return ret == 0;
}

bool killProcessByName(const std::string& name) {
    std::string command = "killall " + name;
    auto ret = system(command.c_str());
    return ret == 0;
}

void printState(bool killed, const std::string& name) {
    if (killed) {
        std::cout << "\n[ Process " << name << " was terminated ]";
    } else {
        std::cout << "\n[ An error occurred while trying to terminate process " << name << " ]";
    }
}
