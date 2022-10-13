#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

std::chrono::time_point<std::chrono::steady_clock> start, end;
std::chrono::duration<float> duration{};

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

void multiplyBlocks(const std::vector<std::vector<int>> &a, const std::vector<std::vector<int>> &b, std::vector<std::vector<int>> &res, int blockI, int blockJ, int size, int count) {
    for (int i = blockI; i < std::min(blockI + count, size); i++) {
        for (int j = blockJ; j < std::min(blockJ + count, size); j++) {
            for (int k = 0; k < size; k++) {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

std::mutex mutex;

void multiplyMatrices(const std::vector<std::vector<int>> &a, const std::vector<std::vector<int>> &b, std::vector<std::vector<int>> &res, int size, int count) {
    std::vector<std::thread> threads;
    for (int blockI = 0; blockI < size; blockI += count) {
        for (int blockJ = 0; blockJ < size; blockJ += count) {
            mutex.lock();
            threads.emplace_back(multiplyBlocks, std::cref(a), std::cref(b), std::ref(res), blockI, blockJ, size, count);
            mutex.unlock();
        }
    }
    for (std::thread &thread : threads) {
        thread.join();
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
