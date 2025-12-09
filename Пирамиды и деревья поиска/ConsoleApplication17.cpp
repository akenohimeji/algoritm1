#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>

using namespace std;

/**
 * @brief Выводит целочисленную пирамиду, реализованную на std::vector,
 * в форматированном виде с указанием уровней и связей родитель-потомок.
 *
 * @param heap_array Вектор целых чисел, представляющий пирамиду.
 */
void print_pyramid(const vector<int>& heap_array) {
    int n = heap_array.size();

    if (n == 0) {
        cout << "Пирамида пуста." << endl;
        return;
    }

    cout << "Пирамида:" << endl;

    // Итерируемся по массиву, каждый индекс соответствует элементу в пирамиде
    for (int i = 0; i < n; ++i) {
        int value = heap_array[i];

        if (i == 0) {
            // Корень
            cout << "0 root " << value << endl;
        }
        else {
            // Индекс родителя для любого i > 0
            int parent_index = (i - 1) / 2;
            int parent_value = heap_array[parent_index];

            // Уровень элемента можно определить через логарифм или через уровень родителя + 1.
            // Для точности и простоты воспользуемся log2
            int level = static_cast<int>(floor(log2(i + 1)));

            string child_type;
            // Проверка, является ли текущий индекс левым или правым ребенком
            // Левый потомок имеет индекс 2*parent_index + 1
            if (i == 2 * parent_index + 1) {
                child_type = "left";
            }
            else {
                child_type = "right";
            }

            cout << level << " " << child_type << "(" << parent_value << ") " << value << endl;
        }
    }
}

/**
 * @brief Вспомогательная функция для вывода исходного массива на консоль.
 *
 * @param arr Вектор целых чисел.
 */
void print_array_source(const vector<int>& arr) {
    cout << "Исходный массив: ";
    for (size_t i = 0; i < arr.size(); ++i) {
        cout << arr[i] << (i == arr.size() - 1 ? "" : " ");
    }
    cout << endl;
}

// Функции для получения индексов родителя и потомков
bool get_parent_index(int index, const vector<int>& heap, int& parent_index) {
    if (index <= 0 || index >= heap.size()) return false;
    parent_index = (index - 1) / 2;
    return true;
}

bool get_left_child_index(int index, const vector<int>& heap, int& left_index) {
    left_index = 2 * index + 1;
    return (left_index < heap.size());
}

bool get_right_child_index(int index, const vector<int>& heap, int& right_index) {
    right_index = 2 * index + 2;
    return (right_index < heap.size());
}

// Функция для путешествия по пирамиде
void travel_pyramid(const vector<int>& heap_array) {
    int current_index = 0; // Начинаем с корня
    int n = heap_array.size();

    while (true) {
        cout << "Вы находитесь здесь: " << current_index << " " << (current_index == 0 ? "root " : "") << heap_array[current_index] << endl;
        string command;
        cout << "Введите команду: ";
        cin >> command;

        if (command == "exit") {
            break;
        }
        else if (command == "up") {
            int parent_index;
            if (get_parent_index(current_index, heap_array, parent_index)) {
                current_index = parent_index;
                cout << "Ок" << endl;
            }
            else {
                cout << "Ошибка! Отсутствует родитель." << endl;
            }
        }
        else if (command == "left") {
            int left_index;
            if (get_left_child_index(current_index, heap_array, left_index)) {
                current_index = left_index;
                cout << "Ок" << endl;
            }
            else {
                cout << "Ошибка! Отсутствует левый потомок." << endl;
            }
        }
        else if (command == "right") {
            int right_index;
            if (get_right_child_index(current_index, heap_array, right_index)) {
                current_index = right_index;
                cout << "Ок" << endl;
            }
            else {
                cout << "Ошибка! Отсутствует правый потомок." << endl;
            }
        }
        else {
            cout << "Ошибка! Неизвестная команда." << endl;
        }
    }
}

// --- Основная функция программы (Тестирование) ---
int main() {
    setlocale(LC_ALL, "Russian");

    // Пример массива для проверки
    vector<int> array1 = { 1, 3, 6, 5, 9, 8 };
    print_array_source(array1);
    print_pyramid(array1);
    travel_pyramid(array1);
    cout << string(30, '-') << endl;

    vector<int> array2 = { 94, 67, 18, 44, 55, 12, 6, 42 };
    print_array_source(array2);
    print_pyramid(array2);
    travel_pyramid(array2);
    cout << string(30, '-') << endl;

    vector<int> array3 = { 16, 11, 9, 10, 5, 6, 8, 1, 2, 4 };
    print_array_source(array3);
    print_pyramid(array3);
    travel_pyramid(array3);
    cout << string(30, '-') << endl;

    return 0;
}
