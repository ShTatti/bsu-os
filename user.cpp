#include "user.h"

int main() {
    User us;
    us.printProcesses();
    setenv("PROC_TO_KILL", "bash,", 0);
    us.killerProcess("");
    us.printProcesses();
    unsetenv("PROC_TO_KILL");
    return 0;
}