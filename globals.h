#pragma once
#include <string>
#include <variant>


using DataValType = std::variant<bool, float, double, int, std::string>;

enum class DataType {
	Null, Bool, Int, Float, Double, VarChar
};

enum class ExceptionType {
	Null, 
	UnknownTable,
	ColumnNotFound,
	InvalidColumnIndex
};

std::string ExceptionTypeText[];

struct ColumnDescription {
	std::string name;
	DataType type;
};

struct DatabaseException : public std::exception {
	ExceptionType type = ExceptionType::Null;
	std::string table_name;

	DatabaseException(ExceptionType type) : type(type) {}

	DatabaseException(ExceptionType type, std::string table_name) : type(type), table_name(table_name) {}
};



