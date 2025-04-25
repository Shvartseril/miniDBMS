#include "database.h"



void test() {
	Database database;

	database.create_table("first", { { "firstcolumn", DataType::Int }, {"secondcolumn", DataType::Float} });
	database.drop_table("first");

}

int main() {
	test();
	return 0;
}