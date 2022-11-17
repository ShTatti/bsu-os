#include "user.h"

int main() {
    User manager;
    SetEnvironmentVariableA("PROC_TO_KILL", "Telegram;browser");
    LPCSTR killer_process_path="С:\\Tatti\\OS\\lab4_w\\Killer\\Debug\\Killer.exe";
    manager.CreateProcessW(killer_process_path,L"");
    _putenv("PROC_TO_KILL");

    if (!manager.IsActiveProcess(L"Telegram")) {
        std::cout << "Telegram.exe process is terminated" << std::endl;
    } else{
        std::cout << "Telegram.exe process is not terminated" << std::endl;
    }

    if (manager.IsActiveProcess(L"browser")) {
        std::cout << "browser.exe process is terminated"<<std::endl;
    }
    else {
        std::cout << "browser.exe process is not terminated" << std::endl;
    }

    std::wstring process_argument;
    while (process_argument != L"end") {
        std::wcin >> process_argument;
        manager.CreateProcessW(killer_process_path,process_argument);
    }
    return 0;
}