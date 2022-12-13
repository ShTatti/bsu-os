#include <iostream>
#include <windows.h>
#include <vector>
#include <algorithm>

int main() {
    std::vector<HANDLE> handle;

    auto close = [&handle]() {
        std::for_each(handle.begin(), handle.end(), CloseHandle);
    };

    SECURITY_ATTRIBUTES saPipe = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};

    HANDLE hMARead, hMAWrite;
    bool MAPipe = CreatePipe(&hMARead, &hMAWrite, &saPipe, 0);
    if (!MAPipe) {
        std::cout << "MAPipe isn't created";
        return 1;
    }
    handle.push_back(hMARead);
    handle.push_back(hMAWrite);

    HANDLE hAPWrite, hAPRead;
    bool APPipe = CreatePipe(&hAPRead, &hAPWrite, &saPipe, 0);
    if (!APPipe) {
        std::cout << "APPipe isn't created";
        close();
        return 1;
    }
    handle.push_back(hAPRead);
    handle.push_back(hAPWrite);

    HANDLE hPSWrite, hPSRead;
    bool PSPipe = CreatePipe(&hPSRead, &hPSWrite, &saPipe, 0);
    if (!PSPipe) {
        std::cout << "PSPipe isn't create";
        close();
        return 1;
    }
    handle.push_back(hPSRead);
    handle.push_back(hPSWrite);

    STARTUPINFO startInfoM, startInfoA, startInfoP, startInfoS;

    GetStartupInfo(&startInfoM);
    startInfoM.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    startInfoM.hStdOutput = hMAWrite;
    startInfoM.dwFlags = STARTF_USESTDHANDLES;

    std::vector<PROCESS_INFORMATION> processes;
    auto closeAllProcesses = [&processes]() {
        std::for_each(processes.begin(), processes.end(), [](const PROCESS_INFORMATION& process_Info) {
            TerminateProcess(process_Info.hProcess, 1);
            CloseHandle(process_Info.hThread);
            CloseHandle(process_Info.hProcess);
        });
    };

    const wchar_t* path0 = L"../../A/cmake-build-debug/A";
    const wchar_t* path1 = L"../../M/cmake-build-debug/M";
    const wchar_t* path2 = L"../../P/cmake-build-debug/P";
    const wchar_t* path3 = L"../../S/cmake-build-debug/S";

    PROCESS_INFORMATION processM_Info;
    if (!CreateProcess(path1, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &startInfoM, &processM_Info)) {
        return 1;
    }
    processes.push_back(processM_Info);

    GetStartupInfo(&startInfoA);
    startInfoA.hStdInput = hMARead;
    startInfoA.hStdOutput = hAPWrite;
    startInfoA.dwFlags = STARTF_USESTDHANDLES;

    PROCESS_INFORMATION processA_Info;
    if (!CreateProcess(path0, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &startInfoA, &processA_Info)) {
        closeAllProcesses();
        return 1;
    }
    processes.push_back(processA_Info);

    GetStartupInfo(&startInfoP);
    startInfoP.hStdInput = hAPRead;
    startInfoP.hStdOutput = hPSWrite;
    startInfoP.dwFlags = STARTF_USESTDHANDLES;

    PROCESS_INFORMATION processP_Info;
    if (!CreateProcess(path2, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &startInfoP, &processP_Info)) {
        closeAllProcesses();
        return 1;
    }
    processes.push_back(processP_Info);

    GetStartupInfo(&startInfoS);
    startInfoS.hStdInput = hPSRead;
    startInfoS.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    startInfoS.dwFlags = STARTF_USESTDHANDLES;

    PROCESS_INFORMATION processS_Info;
    if (!CreateProcess(path3, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &startInfoS, &processS_Info)) {
        closeAllProcesses();
        return 1;
    }
    processes.push_back(processS_Info);

    std::for_each(processes.begin(), processes.end(), [](const PROCESS_INFORMATION& process_Info) {
        WaitForSingleObject(process_Info.hProcess, INFINITY);
        CloseHandle(process_Info.hThread);
        CloseHandle(process_Info.hProcess);
    });

    close();
}