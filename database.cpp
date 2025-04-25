#include "globals.h"
#include "database.h"


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

