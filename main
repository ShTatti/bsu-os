#include <iostream>
#include <vector>
#include <fstream>
#include <thread>
#include <mutex>
#include "channel.h"

std::vector<double> threadResults;
std::mutex g_lock;

std::vector<std::vector<int>> createMatrix(int size) {
    std::vector<std::vector<int>> newMatrix(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            newMatrix[i].push_back(rand() % 10);
        }
    }
    return newMatrix;
}

void multiplyBlocks(const std::vector <std::vector <int>>& a, const std::vector <std::vector <int>>& b, std::vector < std::vector <int>>& res, std::pair<int, int>& pair, int size, int count) {
    for (int i = pair.first; i < std::min(pair.first + count, size); ++i) {
        for (int j = pair.second; j < std::min(pair.second + count, size); ++j){
            for (int k = 0; k < size; ++k) {
                g_lock.lock();
                res[i][j] += a[i][k] * b[k][j];
                g_lock.unlock();
            }
        }
    }
}

void multiplyMatricesByChannels(const std::vector <std::vector <int>>& a, const std::vector <std::vector <int>>& b, std::vector < std::vector <int>>& res, int size, int count, BufferedChannel < std::pair<int, int>>& channel) {
    std::pair<std::pair<int, int>, bool> pair = channel.Receive();
    while (pair.second) {
        multiplyBlocks(a, b, res, pair.first, size, count);
        pair = channel.Receive();
    }
}

void multiplyMatrices(const std::vector <std::vector <int>>& m1, const std::vector <std::vector <int>>& m2, std::vector < std::vector <int>>& resM, int size, int count, int countThreads) {
    int buffSize = std::pow(size % count == 0 ? size / count : size / count + 1,2);
    BufferedChannel<std::pair<int,int>> channel(buffSize);
    for (int blockI = 0; blockI < size; blockI += count) {
        for (int blockJ = 0; blockJ < size; blockJ += count) {
            std::pair<int, int> blockPair(blockI,blockJ);
            channel.Send(std::move(blockPair));
        }
    }
    channel.Close();
    std::vector<std::thread> threads;
    for (int i = 0; i < countThreads; ++i) {
        threads.emplace_back(multiplyMatricesByChannels, std::ref(m1), std::ref(m2), std::ref(resM), size, count, std::ref(channel));
    }
    for (auto& thread: threads) {
        thread.join();
    }
}

int main() {
    int s = 100;
    std::vector<std::vector<int>> m1 = createMatrix(s);
    std::vector<std::vector<int>> m2 = createMatrix(s);
    std::vector<std::vector<int>> mFinal(s, std::vector<int>(s));
    int blockSize = 10;
    int countThreads = 40;
    std::ofstream out("output.txt");
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= countThreads; i++) {
        multiplyMatrices(m1, m2, mFinal, s, blockSize, i);
        auto tempStart = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> temp = tempStart - start;
        threadResults.push_back(temp.count());
        mFinal = std::vector<std::vector<int>>(s, std::vector<int>(s));
    }
    for (int i = 0; i < threadResults.size() - 1; ++i) {
        out << "thread's count " << i + 1  << ", time: " << threadResults[i] << '\n';
    }
}
