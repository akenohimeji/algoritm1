#include <iostream>

using namespace std;

int* remove_dynamic_array_head(int* arr, int& logical_size, int& actual_size) {
    if (logical_size == 0) {
        cout << "Невозможно удалить первый элемент, так как массив пустой. До свидания!" << endl;
        return arr;
    }

    if ((logical_size - 1) > (actual_size / 3.0)) {
        for (int i = 0; i < logical_size - 1; ++i) {
            arr[i] = arr[i + 1];
        }
        logical_size--;
        return arr;
    }
    else {
        int new_actual_size = actual_size / 3;
        if (new_actual_size == 0) {
            new_actual_size = 1;
        }
        int* new_arr = new int[new_actual_size];
        for (int i = 0; i < logical_size - 1; ++i) {
            new_arr[i] = arr[i + 1];
        }
        logical_size--;
        actual_size = new_actual_size;

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

    string answer;
    while (true) {
        cout << "Удалить первый элемент? ";
        cin >> answer;

        if (answer == "да") {

            arr = remove_dynamic_array_head(arr, logical_size, actual_size);

            if (logical_size == 0) {
                return 0;
            }
            print_dynamic_array(arr, logical_size, actual_size);


        }
        else {
            cout << "Спасибо! Ваш динамический массив: ";

            if (logical_size == 1) {
                cout << arr[0] << endl;
            }
            else {
                for (int i = 0; i < logical_size; ++i) {
                    cout << arr[i] << " ";
                }
                for (int i = logical_size; i < actual_size; ++i) {
                    cout << "_ ";
                }
                cout << endl;
            }


            delete[] arr;
            return 0;
        }
    }


    return 0;
}
