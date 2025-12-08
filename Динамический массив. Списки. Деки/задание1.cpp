#include <iostream>

// Функция вывода динамического массива на экран
void print_dynamic_array(int* arr, int logical_size, int actual_size) {
    std::cout << "Динамический массив: ";
    for (int i = 0; i < actual_size; ++i) {
        if (i < logical_size) {
            std::cout << arr[i] << " ";
        }
        else {
            std::cout << "_ ";
        }
    }
    std::cout << std::endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int actual_size;
    int logical_size;

    // Ввод фактического размера массива
    std::cout << "Введите фактический размер массива: ";
    std::cin >> actual_size;

    // Ввод логического размера массива с проверкой
    while (true) {
        std::cout << "Введите логический размер массива: ";
        std::cin >> logical_size;

        if (logical_size <= actual_size) {
            break; // Выход из цикла, если размеры корректны
        }
        else {
            std::cout << "Ошибка! Логический размер массива не может превышать фактический!" << std::endl;
        }
    }

    // Создание динамического массива
    int* dynamic_array = new int[actual_size];

    // Заполнение массива элементами до логического размера
    for (int i = 0; i < logical_size; ++i) {
        std::cout << "Введите arr[" << i << "]: ";
        std::cin >> dynamic_array[i];
    }

    // Вывод массива на экран с помощью созданной функции
    print_dynamic_array(dynamic_array, logical_size, actual_size);

    // Освобождение памяти, выделенной под динамический массив
    delete[] dynamic_array;

    return 0;
}
