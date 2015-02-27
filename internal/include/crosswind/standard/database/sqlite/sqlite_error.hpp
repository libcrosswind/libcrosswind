#pragma once

#include <memory>
#include <sstream>
#include <cassert>

#include <sqlite3.h>

namespace cw{
namespace standard{
namespace database{
namespace sqlite{

    class sqlite_error;

}
}// namespace database
}// namespace standard
}// namespace cw

class sqlite_error: public std::runtime_error {
public:

    sqlite_error(const int error_code, const std::string &msg):
    std::runtime_error(sqlite_error_message(error_code) + " " + msg),
    code(error_code) {

    }

    sqlite_error(const std::string &msg): std::runtime_error(msg) {

    }

    sqlite_error(const std::shared_ptr<sqlite3_stmt> &stmt, const std::string &msg):
    std::runtime_error(sqlite_error_message(stmt) + " " + msg) {

    }

    const int sqlite_error_code() const noexcept { return code; }

private:
    std::string sqlite_error_message(const int status) { return sqlite3_errstr(status); }

    std::string sqlite_error_message(sqlite3 *db) { return sqlite3_errmsg(db); }

    std::string sqlite_error_message(const std::shared_ptr<sqlite3_stmt> &stmt) {
        sqlite3 *db(sqlite3_db_handle(stmt.get()));
        std::stringstream ss;
        ss << sqlite_error_message(db) << " while executing sql statement '"
           << sqlite3_sql(stmt.get()) << "'";
        return ss.str();
    }

    const int sqlite_error_code(sqlite3* db) { return sqlite3_errcode(db); }

    const int sqlite_error_code(const std::shared_ptr<sqlite3_stmt> &stmt) {
        sqlite3 *db(sqlite3_db_handle(stmt.get()));
        return sqlite3_errcode(db);
    }

private:
    const int code = 0;

};// class sqlite_error