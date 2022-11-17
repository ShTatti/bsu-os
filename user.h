#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include <vector>
#include <thread>
#include <algorithm>
#include <iostream>

class User {
public:
    static void CreateProcessW(LPCSTR process_path, const std::wstring& argument);
    bool IsActiveProcess(DWORD id);
    bool IsActiveProcess(const std::wstring& name);

private:
    void UpdateActiveProcessesList();
    std::vector<std::pair<DWORD,std::wstring>> active_processes_;
};

void User::CreateProcessW(LPCSTR process_path, const std::wstring& argument) {
    STARTUPINFOA startUpInf = {0};
    PROCESS_INFORMATION procInf = {nullptr};
    if (CreateProcessA(process_path, (char*)argument.c_str(), nullptr, nullptr, FALSE, 0, nullptr, nullptr, &startUpInf, &procInf)) {
        WaitForSingleObject(procInf.hProcess, INFINITE);
        CloseHandle(procInf.hProcess);
        CloseHandle(procInf.hThread);
    } else {
        std::cout << "Failed to create process: " << GetLastError() << std::endl;
    }
}

void User::UpdateActiveProcessesList() {
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof(PROCESSENTRY32);
    auto hRes = Process32First(hSnapShot, &pEntry);
    active_processes_.clear();
    while (hRes) {
        active_processes_.emplace_back(pEntry.th32ProcessID, std::wstring(
                reinterpret_cast<const wchar_t *const>(pEntry.szExeFile)));
        hRes = Process32Next(hSnapShot, &pEntry);
    }
    CloseHandle(hSnapShot);
}

bool User::IsActiveProcess(DWORD id) {
    UpdateActiveProcessesList();
    for (const std::pair<DWORD, std::wstring>& process : active_processes_) {
        if (process.first == id) {
            return true;
        }
    }
    return false;
}

bool User::IsActiveProcess(const std::wstring& name) {
    UpdateActiveProcessesList();
    for (const std::pair<DWORD, std::wstring>& process : active_processes_) {
        if (process.second == name) {
            return true;
        }
    }
    return false;
}