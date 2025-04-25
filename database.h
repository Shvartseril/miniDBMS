#pragma once
#include <string>
#include <vector>
#include <variant>
#include <utility>
#include "globals.h"


class Database;

class TableRow {
protected:
	std::vector<std::variant<bool, float, double, int, std::string>> vectValues; // вектор значений для конкретной строки

public:
	TableRow() = default;
};

class Table {
protected:
	std::string name; // имя таблицы 
	std::vector<ColumnDescription> vectHeader; // список заголовков для колонок
	std::vector<TableRow> vectRows; // содержание колонок

	Database* parent = nullptr;

public:
	Table() = default;

	Table(Database* database, std::string name, std::vector<ColumnDescription> vectHeader) : parent(database), name(name), vectHeader(vectHeader) {}

	std::string get_name() {
		return name;
	}
};

class Database {
protected:
	std::vector<Table> vectTables; // список таблиц

	void Edrop_table(std::string name);

	std::vector<Table>::iterator Eget_table(std::string name);

public:
	Database() = default;

	void create_table(std::string name, std::vector<ColumnDescription> vectHeader);

	void drop_table(std::string name);

}; 



