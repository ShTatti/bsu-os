#include <iostream>
#include <vector>
#include <windows.h>
#include <mutex>
#include <algorithm>

std::chrono::time_point<std::chrono::steady_clock> start, end;
std::chrono::duration<float> duration{};

struct threadParams {
    const std::vector<std::vector<int>> &A;
    const std::vector<std::vector<int>> &B;
    std::vector<std::vector<int>> &D;
    int start1,start2, m_size,count;
    threadParams(const std::vector<std::vector<int>> &a, const std::vector<std::vector<int>> &b, std::vector<std::vector<int>> &res, int i, int j, int size, int count) :
    A(a), B(b), D(res), start1(i), start2(j), m_size(size), count(count){}
};

float getTime() {
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;

    float ms = duration.count() * 1000.0f;
    return ms;
}

std::vector<std::vector<int>> createMatrix(int size) {
    std::vector<std::vector<int>> newMatrix(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            newMatrix[i].push_back(rand() % 10);
        }
    }
    return newMatrix;
}
#undef min
void multiplyBlocks(const std::vector<std::vector<int>> &a, const std::vector<std::vector<int>> &b, std::vector<std::vector<int>> &res, int blockI, int blockJ, int size, int count) {
    for (int i = blockI; i < std::min(blockI + count, size); i++) {
        for (int j = blockJ; j < std::min(blockJ + count, size); j++) {
            for (int k = 0; k < size; k++) {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

DWORD WINAPI callMultiply(LPVOID args)
{
    threadParams *castedArgs = (threadParams *)args;
    multiplyBlocks(castedArgs->A, castedArgs->B, castedArgs->D, castedArgs->start1, castedArgs->start2, castedArgs->m_size, castedArgs->count);
    ExitThread(0);
}

void multiplyMatrices(const std::vector<std::vector<int>> &a, const std::vector<std::vector<int>> &b, std::vector<std::vector<int>> &res, int size, int count) {
    std::vector<HANDLE> threads;
    for (int blockI = 0; blockI < size; blockI += count) {
        for (int blockJ = 0; blockJ < size; blockJ += count) {
            threads.emplace_back(
                    CreateThread(NULL, 0, &callMultiply, new threadParams(a, b, res, blockI, blockJ, size, count), 0,NULL));
        }
    }
    for (HANDLE &thread : threads)
    {
        WaitForSingleObject(thread, INFINITE);
    }
}

int main(){
    int s;
    std::cout << "size is: ";
    std::cin >> s;

    std::vector<std::vector<int>> m1 = createMatrix(s);
    std::vector<std::vector<int>> m2 = createMatrix(s);
    std::vector<std::vector<int>> mFinal(s, std::vector<int>(s));

    start = std::chrono::high_resolution_clock::now();
    multiplyBlocks(m1, m2, mFinal, 0, 0,  s, 1);
    float t = getTime();

    std::vector<float> threadsTime;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= s; i++) {
        multiplyMatrices(m1, m2, mFinal, s, i);
        threadsTime.push_back(getTime());
    }

    std::cout<< "multiply without threads: " << t << std::endl;

    for (int i = 0; i < s; i++) {
        std::cout << "blocks: " << i + 1 << ",  thread time: " << threadsTime[i] << '\n';
    }

    return 0;
}
