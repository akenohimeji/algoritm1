#define NOMINMAX
#include <iostream>
#include <string>
#include <vector>
#include <libpq-fe.h> 
#include <clocale>

class ClientManager {
    PGconn* conn;

    // Вспомогательный метод для проверки статуса выполнения запроса
    bool checkResult(PGresult* res, const std::string& errorMsg) {
        ExecStatusType status = PQresultStatus(res);
        if (status != PGRES_COMMAND_OK && status != PGRES_TUPLES_OK) {
            std::cerr << errorMsg << ": " << PQerrorMessage(conn) << std::endl;
            PQclear(res);
            return false;
        }
        return true;
    }

public:
    ClientManager(const char* connInfo) {
        conn = PQconnectdb(connInfo);
        if (PQstatus(conn) != CONNECTION_OK) {
            std::cerr << "Ошибка подключения: " << PQerrorMessage(conn) << std::endl;
        }
        else {
            // Принудительно устанавливаем UTF8 для работы с кириллицей
            PQclear(PQexec(conn, "SET client_encoding TO 'UTF8'"));
            std::cout << "Соединение с БД установлено (UTF-8)." << std::endl;
        }
    }

    ~ClientManager() { if (conn) PQfinish(conn); }

    // 1. Создать структуру БД (таблицы)
    void createStructure() {
        const char* sql =
            "CREATE TABLE IF NOT EXISTS clients (id SERIAL PRIMARY KEY, f_name VARCHAR(50), l_name VARCHAR(50), email VARCHAR(100) UNIQUE);"
            "CREATE TABLE IF NOT EXISTS phones (id SERIAL PRIMARY KEY, client_id INTEGER REFERENCES clients(id) ON DELETE CASCADE, phone VARCHAR(20));";
        PGresult* res = PQexec(conn, sql);
        if (checkResult(res, "Ошибка создания таблиц")) {
            std::cout << "Структура таблиц проверена/создана." << std::endl;
            PQclear(res);
        }
    }

    // 2. Добавить нового клиента
    int addClient(std::string f, std::string l, std::string e) {
        const char* params[] = { f.c_str(), l.c_str(), e.c_str() };
        PGresult* res = PQexecParams(conn, "INSERT INTO clients (f_name, l_name, email) VALUES ($1, $2, $3) RETURNING id", 3, NULL, params, NULL, NULL, 0);
        if (!checkResult(res, "Ошибка добавления клиента")) return -1;
        int id = std::stoi(PQgetvalue(res, 0, 0));
        PQclear(res);
        return id;
    }

    // 3. Добавить телефон для существующего клиента
    void addPhone(int id, std::string p) {
        std::string sid = std::to_string(id);
        const char* params[] = { sid.c_str(), p.c_str() };
        PGresult* res = PQexecParams(conn, "INSERT INTO phones (client_id, phone) VALUES ($1, $2)", 2, NULL, params, NULL, NULL, 0);
        if (checkResult(res, "Ошибка добавления телефона")) PQclear(res);
    }

    // 4. Изменить данные о клиенте
    void updateClient(int id, std::string f, std::string l, std::string e) {
        std::string sid = std::to_string(id);
        const char* params[] = { f.c_str(), l.c_str(), e.c_str(), sid.c_str() };
        PGresult* res = PQexecParams(conn, "UPDATE clients SET f_name=$1, l_name=$2, email=$3 WHERE id=$4", 4, NULL, params, NULL, NULL, 0);
        if (checkResult(res, "Ошибка обновления клиента")) PQclear(res);
    }

    // 5. Удалить телефон у существующего клиента
    void deletePhone(int id, std::string p) {
        std::string sid = std::to_string(id);
        const char* params[] = { sid.c_str(), p.c_str() };
        PGresult* res = PQexecParams(conn, "DELETE FROM phones WHERE client_id=$1 AND phone=$2", 2, NULL, params, NULL, NULL, 0);
        if (checkResult(res, "Ошибка удаления телефона")) PQclear(res);
    }

    // 6. Удалить существующего клиента
    void deleteClient(int id) {
        std::string sid = std::to_string(id);
        const char* params[] = { sid.c_str() };
        PGresult* res = PQexecParams(conn, "DELETE FROM clients WHERE id=$1", 1, NULL, params, NULL, NULL, 0);
        if (checkResult(res, "Ошибка удаления клиента")) PQclear(res);
    }

    // 7. Найти клиента по его данным (имя, фамилия, email или телефон)
    void findClient(std::string query) {
        const char* params[] = { query.c_str() };
        PGresult* res = PQexecParams(conn,
            "SELECT DISTINCT c.id, f_name, l_name, email FROM clients c "
            "LEFT JOIN phones p ON c.id = p.client_id "
            "WHERE f_name=$1 OR l_name=$1 OR email=$1 OR phone=$1", 1, NULL, params, NULL, NULL, 0);

        if (!checkResult(res, "Ошибка поиска")) return;

        int rows = PQntuples(res);
        if (rows == 0) {
            std::cout << "По запросу '" << query << "' ничего не найдено." << std::endl;
        }
        else {
            for (int i = 0; i < rows; i++) {
                std::cout << "Найдено -> ID: " << PQgetvalue(res, i, 0)
                    << " | Имя: " << PQgetvalue(res, i, 1)
                    << " | Фамилия: " << PQgetvalue(res, i, 2)
                    << " | Email: " << PQgetvalue(res, i, 3) << std::endl;
            }
        }
        PQclear(res);
    }
};

int main() {
    // Настройка кодировок для консоли
    system("chcp 65001 > nul");
    setlocale(LC_ALL, ".65001");

    // Данные для подключения (проверьте пароль и dbname!)
    const char* connInfo = "host=localhost port=5432 dbname=test_db user=postgres password=doom3vad";

    ClientManager manager(connInfo);

    // Демонстрация работы по условиям ДЗ:
    manager.createStructure();

    // Добавляем клиента
    int id = manager.addClient("Иван", "Иванов", "ivan@example.com");
    if (id != -1) {
        // Добавляем несколько телефонов
        manager.addPhone(id, "+79001112233");
        manager.addPhone(id, "88005553535");

        std::cout << "\nПоиск по фамилии 'Иванов':" << std::endl;
        manager.findClient("Иванов");

        // Обновляем данные клиента
        manager.updateClient(id, "Иван", "Сидоров", "sidorov@example.com");
        std::cout << "\nДанные изменены (Фамилия стала Сидоров)." << std::endl;

        // Удаляем один из телефонов
        manager.deletePhone(id, "88005553535");
        std::cout << "Один телефон удален." << std::endl;

        std::cout << "\nПоиск по новому email:" << std::endl;
        manager.findClient("sidorov@example.com");

        // Если нужно протестировать удаление клиента целиком:
        // manager.deleteClient(id);
        // std::cout << "\nКлиент удален из базы." << std::endl;
    }

    return 0;
}
