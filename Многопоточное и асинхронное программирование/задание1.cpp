#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

std::atomic<int> client_counter(0);

// Поток клиента
void client_stream(int max_clients) {
    for (int i = 0; i < max_clients; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        client_counter.fetch_add(1);
        std::cout << "[Клиент] Пришел. Всего в очереди: " << client_counter.load() << std::endl;
    }
}

// Поток операциониста
void operator_stream(int max_clients) {
    int served_count = 0;

    while (served_count < max_clients) {
        std::this_thread::sleep_for(std::chrono::seconds(2));

        if (client_counter.load() > 0) {
            client_counter.fetch_sub(1);
            served_count++;
            std::cout << "[Оператор] Обслужил. Осталось в очереди: " << client_counter.load() << std::endl;
        }
        else {
            std::cout << "[Оператор] Ждет клиентов..." << std::endl;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    const int MAX_CLIENTS = 5;

    std::cout << "Очередь открыта. Всего ожидается клиентов: " << MAX_CLIENTS << std::endl;
    std::cout << "-------------------------------------------" << std::endl;

    std::thread t1(client_stream, MAX_CLIENTS);
    std::thread t2(operator_stream, MAX_CLIENTS);

    t1.join();
    t2.join();

    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "Все клиенты обслужены. Очередь пуста." << std::endl;

    return 0;
}
