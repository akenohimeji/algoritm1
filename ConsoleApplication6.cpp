#include <iostream>
#include <vector>

int fibonacci_dp(int n, std::vector<int>& memo) {
    // Если значение уже вычислено - возвращаем его из memo.
    if (memo[n] != -1) {
        return memo[n];
    }

    // Базовый случай: если n равно 0 или 1, возвращаем n.
    if (n <= 1) {
        memo[n] = n; // Запоминаем значение.
        return n;
    }

    // Рекурсивный случай: вычисляем n-ое число Фибоначчи, используя memoization.
    memo[n] = fibonacci_dp(n - 1, memo) + fibonacci_dp(n - 2, memo); // Запоминаем и возвращаем.
    return memo[n];
}

int fibonacci(int n) {
    //Создаем вектор memo для хранения вычисленных значений, изначально заполненный -1.
    std::vector<int> memo(n + 1, -1);
    return fibonacci_dp(n, memo);
}

int main() {
    setlocale(LC_ALL, "Rus");
    int n = 10;
    int result = fibonacci(n);
    std::cout << "Число Фибоначчи для n = " << n << ": " << result << std::endl;
    return 0;
}
