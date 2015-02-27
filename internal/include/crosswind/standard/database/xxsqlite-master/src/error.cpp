#pragma once

#include "error.hpp"

#include <sqlite3.h>

#include <sstream>
#include <cassert>

namespace cw{
namespace standard{
namespace database{

class sqlite_error;

}
}
}

namespace sqlite {

namespace {

std::string error_message(const int status) { return sqlite3_errstr(status); }

std::string error_message(sqlite3 *db) { return sqlite3_errmsg(db); }

std::string error_message(const std::shared_ptr<sqlite3_stmt> &stmt) {
    sqlite3 *db(sqlite3_db_handle(stmt.get()));
    std::stringstream ss;
    ss << error_message(db) << " while executing sql statement '"
       << sqlite3_sql(stmt.get()) << "'";
    return ss.str();
}

const int error_code(sqlite3* db) { return sqlite3_errcode(db); }

const int error_code(const std::shared_ptr<sqlite3_stmt> &stmt) {
    sqlite3 *db(sqlite3_db_handle(stmt.get()));
    return sqlite3_errcode(db);
}

}

error::error(const int error_code, const std::string &msg):
    std::runtime_error(error_message(error_code) + " " + msg),
    code(error_code) {}

error::error(const std::string &msg): std::runtime_error(msg) {}

error::error(const std::shared_ptr<sqlite3_stmt> &stmt, const std::string &msg):
    std::runtime_error(error_message(stmt) + " " + msg) {}



} // namespace sqlite
