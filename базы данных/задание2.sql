CREATE TABLE IF NOT EXISTS Employees (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    department VARCHAR(100),
    manager_id INTEGER REFERENCES Employees(id)
);

-- Сначала добавляем директора (у него нет начальника)
INSERT INTO Employees (name, department, manager_id) 
VALUES ('Иван Иванов', 'Дирекция', NULL);

-- Добавляем подчиненного (manager_id ссылается на id = 1)
INSERT INTO Employees (name, department, manager_id) 
VALUES ('Петр Петров', 'IT', 1);
