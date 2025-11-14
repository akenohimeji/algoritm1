#include <iostream>
#include <vector>

// Функция для нахождения количества элементов, больше заданного числа
int countGreaterThan(const std::vector<int>& arr, int threshold) {
    int left = 0;
    int right = arr.size();

    while (left < right) {
        int mid = left + (right - left) / 2; // Находим середину
        // Ищем первое число, большее по сравнению с threshold
        if (arr[mid] > threshold) {
            right = mid; // Сужаем правую границу
        }
        else {
            left = mid + 1; // Сужаем левую границу
        }
    }

    // Количество элементов, больше threshold
    return arr.size() - left;
}

int main() {
    setlocale(LC_ALL, "Russian");
    // Создаём отсортированный массив
    std::vector<int> sortedArray = { 14, 16, 19, 32, 32, 32, 56, 69, 72 };

    // Запрашиваем у пользователя точку отсчёта
    int threshold;
    std::cout << "Введите точку отсчёта: ";
    std::cin >> threshold;

    // Вызываем функцию и выводим результат
    int count = countGreaterThan(sortedArray, threshold);
    std::cout << "Количество элементов в массиве больших, чем " << threshold << ": " << count << std::endl;

    return 0;
}