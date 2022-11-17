#include "killer.h"

int main(int argc, char* argv[]){
    Killer process_killer;

    if (strcmp(argv[1], "id") == 0) {
        process_killer.AddProcessId(atoi(argv[2]));
    }
    else if (strcmp(argv[1], "name") == 0) {
        std::string str(argv[2]);
        std::wstring w_str(str.begin(), str.end());
        process_killer.FindProcessesByName(w_str.c_str());
    }
    process_killer.KillAllProcesses();
    return 0;
}