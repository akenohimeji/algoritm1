#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <iomanip>
#include <string>  
#include <clocale>

void sum_vectors(const std::vector<int>& v1, const std::vector<int>& v2, std::vector<int>& res, int start, int end) {
    for (int i = start; i < end; ++i) {
        res[i] = v1[i] + v2[i];
    }
}

double run_test(int num_elements, int num_threads) {
    std::vector<int> v1(num_elements, 1);
    std::vector<int> v2(num_elements, 2);
    std::vector<int> res(num_elements, 0);

    std::vector<std::thread> threads;
    int chunk_size = num_elements / num_threads;

    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_threads; ++i) {
        int start = i * chunk_size;
        int end = (i == num_threads - 1) ? num_elements : (i + 1) * chunk_size;
        threads.emplace_back(sum_vectors, std::cref(v1), std::cref(v2), std::ref(res), start, end);
    }

    for (auto& t : threads) {
        t.join();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end_time - start_time;
    return duration.count();
}

int main() {
    setlocale(LC_ALL, "Russian");

    unsigned int cores = std::thread::hardware_concurrency();
    std::cout << "Количество аппаратных ядер: " << cores << "\n\n";

    std::vector<int> sizes = { 1000, 10000, 100000, 1000000 };
    std::vector<int> thread_counts = { 1, 2, 4, 8, 16 };

    std::cout << std::left << std::setw(15) << "Кол-во эл-тов";
    for (int t : thread_counts) {
        std::cout << std::setw(12) << t << " пот.";
    }
    std::cout << "\n" << std::string(80, '-') << "\n";

    for (int size : sizes) {
        std::cout << std::left << std::setw(15) << size;
        for (int t : thread_counts) {
            double time = run_test(size, t);
            std::cout << std::fixed << std::setprecision(5) << std::setw(15) << time;
        }
        std::cout << "\n";
    }

    return 0;
}
