#include "killer.h"

int main(int argc, char *argv[]) {
    Killer killer;
    auto var = getenv("PROC_TO_KILL");
    unsigned int count = 0;
    unsigned int all_processes = 0;
    if (var) {
        std::string str(var);
        std::stringstream ss(str);
        while (ss.getline(var, str.size(), ',')) {
            all_processes++;
            std::string name(var);
            auto killed = killer.killProcessByName(name);
            killer.printState(killed,name);
            count += killed;
        }
    }
    std::cout << "\n[ " << count << " of " << all_processes << " PROC_TO_KILL processes were terminated ]";
    return 0;
}