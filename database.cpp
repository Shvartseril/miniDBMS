#include "globals.h"
#include "database.h"


////////////////////////////////////////
// class Table implementation///////////
////////////////////////////////////////
void Table::Einsert_value2column(TableRow& tableRow, ColumnDescription& columnDescription, DataValType dataValType, size_t i) {

}

void Table::Einsert_row2table(TableRow& tableRow, std::vector<DataValType> vectColumnValues) {
	for (size_t i = 0; i < vectColumnValues.size(); i++) {
		tableRow.SetColumnValue(i, vectColumnValues[i]);
	}
}

void Table::Einsert_row2table(TableRow& tableRow, std::vector<std::string> vectColumnNames, std::vector<DataValType> vectColumnValues) {
	if (vectColumnNames.size() != vectColumnValues.size()) throw DatabaseException(ExceptionType::InvalidColumnIndex);

	for (size_t i = 0; i < vectColumnValues.size(); i++) {
		std::string columnName = vectColumnNames[i];
		std::vector<ColumnDescription>::iterator it = std::find_if(vectHeader.begin(), vectHeader.end(), [columnName](ColumnDescription& columnDescription) {return columnName == columnDescription.name; });
		if (it == vectHeader.end()) throw DatabaseException(ExceptionType::ColumnNotFound);
		size_t colIndex = it - vectHeader.begin();
		tableRow.SetColumnValue(colIndex, vectColumnValues[i]); 
	}
}

void Table::insert_row2table(std::vector<std::string>& vectColumnNames, std::vector<DataValType>& vectColumnValues) {
	if (vectColumnNames.size() > vectHeader.size()) throw DatabaseException(ExceptionType::ColumnNotFound);
	vectRows.push_back(TableRow(vectHeader));
	if (vectColumnNames.empty()) Einsert_row2table(vectRows.back(), vectColumnValues);
	else Einsert_row2table(vectRows.back(), vectColumnNames, vectColumnValues);
}

////////////////////////////////////////
// class Database implementation ///////
////////////////////////////////////////
void Database::Edrop_table(std::string name) {
	auto it = Eget_table(name);
	if (it == vectTables.end()) throw DatabaseException(ExceptionType::UnknownTable);
	vectTables.erase(it);
}

std::vector<Table>::iterator Database::Eget_table(std::string name) {
	std::vector<Table>::iterator it = std::find_if(vectTables.begin(), vectTables.end(), [name](Table& tab) {return name == tab.get_name(); });
	return it;
}


void Database::create_table(std::string name, std::vector<ColumnDescription> vectHeader){
	vectTables.push_back(Table(this, name, vectHeader));
}


void Database::drop_table(std::string name) {
	Edrop_table(name);
}

void Database::insert_row2table(std::string name, std::vector<std::string> vectColumnNames, std::vector<DataValType> vectColumnValues) {
	auto it = Eget_table(name);
	if (it == vectTables.end()) throw DatabaseException(ExceptionType::UnknownTable);
	it->insert_row2table(vectColumnNames, vectColumnValues);
}

