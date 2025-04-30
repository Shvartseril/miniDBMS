#pragma once
#include <string>
#include <vector>
#include <variant>
#include <utility>
#include "globals.h"


class Database;

class TableRow {
protected:
	std::vector<DataValType> vectValues; // вектор значений для конкретной строки

	void EinitColums(std::vector<ColumnDescription>& vectHeader) {
		for (ColumnDescription item : vectHeader)
			vectValues.push_back({});
	}

public:
	// TableRow() = default;

	TableRow(std::vector<ColumnDescription>& vectHeader) { EinitColums(vectHeader); };

	void SetColumnValue(size_t index, DataValType dataValType) {
		if (index >= vectValues.size()) throw DatabaseException(ExceptionType::InvalidColumnIndex);
		vectValues[index] = dataValType;
	}
};
 
class Table {
protected:
	std::string name; // имя таблицы 
	std::vector<ColumnDescription> vectHeader; // список заголовков для колонок
	std::vector<TableRow> vectRows; // все строки таблицы

	Database* parent = nullptr;

	void Einsert_value2column(TableRow& tableRow, ColumnDescription& columnDescription, DataValType dataValType, size_t i);

	void Einsert_row2table(TableRow& tableRow, std::vector<DataValType> vectColumnValues);

	void Einsert_row2table(TableRow& tableRow, std::vector<std::string> vectColumnNames, std::vector<DataValType> vectColumnValues);
public:
	Table() = default;

	Table(Database* database, std::string name, std::vector<ColumnDescription> vectHeader) : parent(database), name(name), vectHeader(vectHeader) {}

	std::string get_name() { return name; }

	void insert_row2table(std::vector<std::string>& vectColumnNames, std::vector<DataValType>& vectColumnValues);
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

	void insert_row2table(std::string name, std::vector<std::string> vectColumnNames, std::vector<DataValType> vectColumnValues);
}; 



