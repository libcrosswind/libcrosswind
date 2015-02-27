#pragma once

#include <cassert>
#include <string>
#include <memory>

#include <sqlite3.h>

namespace cw{
namespace standard{
namespace database{

class sqlite_row;

}// namespace database
}// namespace standard
}// namespace cw


class cw::standard::database::sqlite_row{
public:
  sqlite_row(const std::shared_ptr<sqlite3_stmt> &statement): stmt(statement) {
      assert(statement && "received null sqlite3_stmt");
  }

  std::size_t column_count() const {
      return sqlite3_column_count(stmt.get());
  }

  std::size_t find_column_index(const std::string &column_name, const std::shared_ptr<sqlite3_stmt> &stmt) {

    assert(stmt && "null sqlite3_stmt provided");
    std::size_t column_count(sqlite3_column_count(stmt.get()));
    for (std::size_t i(0); i < column_count; ++i) {
        if (sqlite3_column_name(stmt.get(), i) == column_name)
            return i;
    }
    assert(false && "invalid column name provided");
    throw error("invalid column name '" + column_name + "'");
  }


  field operator[](const std::string &column_name) const {
      return {stmt, find_column_index(column_name, stmt)};
  }

  field operator[](const std::size_t &column_index) const {
      assert(is_valid_index(column_index) && "invalid column index requested");
      if (! is_valid_index(column_index))
          throw error("no column at index " + std::to_string(column_index));
      return {stmt, column_index};
  }

  bool is_valid_index(const std::size_t &index) const {
      return index < column_count();
  }


};// class sqlite_row
