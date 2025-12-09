#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>

/**
 * @brief Выводит целочисленную пирамиду, реализованную на std::vector,
 * в форматированном виде с указанием уровней и связей родитель-потомок.
 *
 * @param heap_array Вектор целых чисел, представляющий пирамиду.
 */
void print_pyramid(const std::vector<int>& heap_array) {
    int n = heap_array.size();

    if (n == 0) {
        std::cout << "Пирамида пуста." << std::endl;
        return;
    }

    std::cout << "Пирамида:" << std::endl;

    // Итерируемся по массиву, каждый индекс соответствует элементу в пирамиде
    for (int i = 0; i < n; ++i) {
        int value = heap_array[i];

        if (i == 0) {
            // Корень
            std::cout << "0 root " << value << std::endl;
        }
        else {
            // Индекс родителя для любого i > 0
            int parent_index = (i - 1) / 2;
            int parent_value = heap_array[parent_index];

            // Уровень элемента можно определить через логарифм или через уровень родителя + 1.
            // Для точности и простоты воспользуемся log2
            int level = static_cast<int>(std::floor(std::log2(i + 1)));

            std::string child_type;
            // Проверка, является ли текущий индекс левым или правым ребенком
            // Левый потомок имеет индекс 2*parent_index + 1
            if (i == 2 * parent_index + 1) {
                child_type = "left";
            }
            else {
                child_type = "right";
            }

            std::cout << level << " " << child_type << "(" << parent_value << ") " << value << std::endl;
        }
    }
}

/**
 * @brief Вспомогательная функция для вывода исходного массива на консоль.
 *
 * @param arr Вектор целых чисел.
 */
void print_array_source(const std::vector<int>& arr) {
    std::cout << "Исходный массив: ";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << (i == arr.size() - 1 ? "" : " ");
    }
    std::cout << std::endl;
}

// --- Основная функция программы (Тестирование) ---
int main() {
    setlocale(LC_ALL, "Russian");
    // Пример 1
    std::vector<int> array1 = { 1, 3, 6, 5, 9, 8 };
    print_array_source(array1);
    print_pyramid(array1);
    std::cout << std::string(30, '-') << std::endl;

    // Пример 2
    std::vector<int> array2 = { 94, 67, 18, 44, 55, 12, 6, 42 };
    print_array_source(array2);
    print_pyramid(array2);
    std::cout << std::string(30, '-') << std::endl;

    // Пример 3
    std::vector<int> array3 = { 16, 11, 9, 10, 5, 6, 8, 1, 2, 4 };
    print_array_source(array3);
    print_pyramid(array3);
    std::cout << std::string(30, '-') << std::endl;

    return 0;
}
