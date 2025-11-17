#include <iostream>

// Итеративная функция для вычисления n-го числа Фибоначчи
int fibonacci(int n) {
    // Обработка базовых случаев
    if (n == 0) return 0;
    if (n == 1) return 1;

    int a = 0, b = 1, c; // Переменные для хранения двух предыдущих чисел
    for (int i = 2; i <= n; ++i) {
        c = a + b; // Следующее число Фибоначчи
        a = b;     // Обновление a до текущего b
        b = c;     // Обновление b до нового c
    }
    return b;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int n;
    std::cout << "Введите n для вычисления n-го числа Фибоначчи: ";
    std::cin >> n;

    int result = fibonacci(n);
    std::cout << "Число Фибоначчи для n = " << n << " равно: " << result << std::endl;

    return 0;
}