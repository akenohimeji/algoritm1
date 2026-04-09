#include <iostream>
#include <vector>
#include <string>
#include <pqxx/pqxx>

struct Client {
    int id;
    std::string first_name;
    std::string last_name;
    std::string email;
    std::vector<std::string> phones;
};

class ClientManager {
private:
    pqxx::connection& c;

public:
    ClientManager(pqxx::connection& conn) : c(conn) {}

    void create_db_structure() {
        pqxx::work w(c);
        w.exec("CREATE TABLE IF NOT EXISTS clients ("
            "id SERIAL PRIMARY KEY, "
            "first_name VARCHAR(50) NOT NULL, "
            "last_name VARCHAR(50) NOT NULL, "
            "email VARCHAR(100) UNIQUE NOT NULL);");

        w.exec("CREATE TABLE IF NOT EXISTS phones ("
            "id SERIAL PRIMARY KEY, "
            "client_id INTEGER REFERENCES clients(id) ON DELETE CASCADE, "
            "phone_number VARCHAR(20));");
        w.commit();
    }

    void add_client(const std::string& first_name, const std::string& last_name, const std::string& email) {
        pqxx::work w(c);
        w.exec_params("INSERT INTO clients (first_name, last_name, email) VALUES ($1, $2, $3)",
            first_name, last_name, email);
        w.commit();
    }

    void add_phone(int client_id, const std::string& phone) {
        pqxx::work w(c);
        w.exec_params("INSERT INTO phones (client_id, phone_number) VALUES ($1, $2)", client_id, phone);
        w.commit();
    }

    void update_client(int id, const std::string& f_name, const std::string& l_name, const std::string& email) {
        pqxx::work w(c);
        w.exec_params("UPDATE clients SET first_name=$1, last_name=$2, email=$3 WHERE id=$4",
            f_name, l_name, email, id);
        w.commit();
    }

    void delete_phone(int client_id, const std::string& phone) {
        pqxx::work w(c);
        w.exec_params("DELETE FROM phones WHERE client_id=$1 AND phone_number=$2", client_id, phone);
        w.commit();
    }

    void delete_client(int id) {
        pqxx::work w(c);
        w.exec_params("DELETE FROM clients WHERE id=$1", id);
        w.commit();
    }

    // Теперь возвращаем вектор структур, а не просто выводим в консоль
    std::vector<Client> find_clients(const std::string& query) {
        pqxx::work w(c);
        std::vector<Client> results;

        // Поиск по всем полям, включая телефоны через JOIN
        pqxx::result r = w.exec_params(
            "SELECT DISTINCT c.id, c.first_name, c.last_name, c.email "
            "FROM clients c "
            "LEFT JOIN phones p ON c.id = p.client_id "
            "WHERE c.first_name = $1 OR c.last_name = $1 OR c.email = $1 OR p.phone_number = $1",
            query);

        for (auto row : r) {
            Client cl{ row[0].as<int>(), row[1].as<std::string>(), row[2].as<std::string>(), row[3].as<std::string>() };

            // Догружаем телефоны для каждого найденного клиента
            pqxx::result ph_res = w.exec_params("SELECT phone_number FROM phones WHERE client_id=$1", cl.id);
            for (auto ph_row : ph_res) {
                cl.phones.push_back(ph_row[0].as<std::string>());
            }
            results.push_back(cl);
        }
        return results;
    }
};

int main() {
    try {
        // Укажите свои данные подключения
        pqxx::connection c("host=localhost port=5432 dbname=clients_db user=postgres password=doom3vad");
        ClientManager manager(c);

        manager.create_db_structure();

        // 1. Добавление
        manager.add_client("Ivan", "Ivanov", "ivan@mail.ru");
        manager.add_phone(1, "+79991234567");

        // 2. Поиск (теперь возвращает данные)
        auto found = manager.find_clients("Ivanov");

        for (const auto& cl : found) {
            std::cout << "Найдено: " << cl.first_name << " " << cl.last_name << " (" << cl.email << ")\n";
            for (const auto& p : cl.phones) std::cout << " - Тел: " << p << "\n";
        }

        // 3. Удаление телефона
        manager.delete_phone(1, "+79991234567");

    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка БД: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
