#include <iostream>

using namespace std;

int* append_to_dynamic_array(int* arr, int& logical_size, int& actual_size, int new_element) {
    if (logical_size < actual_size) {
        arr[logical_size] = new_element;
        logical_size++;
        return arr;
    }
    else {
        int* new_arr = new int[actual_size * 2];
        for (int i = 0; i < actual_size; ++i) {
            new_arr[i] = arr[i];
        }
        new_arr[logical_size] = new_element;
        logical_size++;
        actual_size *= 2;

        delete[] arr;
        return new_arr;
    }
}

void print_dynamic_array(int* arr, int logical_size, int actual_size) {
    cout << "Динамический массив: ";
    for (int i = 0; i < logical_size; ++i) {
        cout << arr[i] << " ";
    }
    for (int i = logical_size; i < actual_size; ++i) {
        cout << "_ ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int actual_size;
    int logical_size;

    cout << "Введите фактический размер массива: ";
    cin >> actual_size;

    cout << "Введите логический размер массива: ";
    cin >> logical_size;

    if (logical_size > actual_size) {
        cout << "Ошибка! Логический размер массива не может превышать фактический!" << endl;
        return 0;
    }

    int* arr = new int[actual_size];

    for (int i = 0; i < logical_size; ++i) {
        cout << "Введите arr[" << i << "]: ";
        cin >> arr[i];
    }

    print_dynamic_array(arr, logical_size, actual_size);

    int new_element;
    while (true) {
        cout << "Введите элемент для добавления: ";
        cin >> new_element;

        if (new_element == 0) {
            break;
        }

        arr = append_to_dynamic_array(arr, logical_size, actual_size, new_element);
        print_dynamic_array(arr, logical_size, actual_size);
    }

    cout << "Спасибо! Ваш массив: ";
    for (int i = 0; i < logical_size; ++i) {
        cout << arr[i] << " ";
    }
    for (int i = logical_size; i < actual_size; ++i) {
        cout << "_ ";
    }
    cout << endl;

    delete[] arr;

    return 0;
}
