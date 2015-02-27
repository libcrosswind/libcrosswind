#pragma once

#include <ostream>
#include <cassert>
#include <string>
#include <memory>

#include <sqlite3.h>

#include <crosswind/standard/database/sqlite/sqlite_error.hpp>


namespace cw{
namespace standard{
namespace database{
namespace sqlite{

    class sqlite_statement;

    enum class null_t {
        null
    };
    
}// namespace sqlite
}// namespace database
}// namespace standard
}// namespace cw


class cw::standard::database::sqlite::sqlite_statement{


    sqlite_statement(const std::shared_ptr<sqlite3_stmt> &sqlite_statement):
            stmt(sqlite_statement) {
        assert(sqlite_statement && "attempt to create sqlite_statement with null sqlite3_stmt");
    }

    template<>
    void bind<blob>(const std::string &parameter, const blob &value) {
        assert(false && "blob support not implemented");
    }

    template<>
    void bind<double>(
            const std::string &parameter,
            const double &value
    ) {
        auto index(find_parameter_index(parameter, stmt));
        throw_on_bind_error(
            sqlite3_bind_double(stmt.get(), index, value),
            parameter
        );
    }

    template<>
    void bind<int>(const std::string &parameter, const int &value) {
        auto index(find_parameter_index(parameter, stmt));
        throw_on_bind_error(sqlite3_bind_int(stmt.get(), index, value), parameter);
    }

    template<>
    void bind<int64_t>(
            const std::string &parameter,
            const int64_t &value
    ) {
        auto index(find_parameter_index(parameter, stmt));
        throw_on_bind_error(
            sqlite3_bind_int64(stmt.get(), index, value),
            parameter
        );
    }

    template<>
    void bind<std::size_t>(
            const std::string &parameter,
            const std::size_t &value
    ) {
        auto index(find_parameter_index(parameter, stmt));
        throw_on_bind_error(
            sqlite3_bind_int64(stmt.get(), index, value),
            parameter
        );
    }

    template<>
    void bind<bool>(const std::string &parameter, const bool &value) {
        auto index(find_parameter_index(parameter, stmt));
        throw_on_bind_error(
            sqlite3_bind_int(stmt.get(), index, static_cast<int>(value)),
            parameter
        );
    }

    template<>
    void bind<null_t>(
            const std::string &parameter,
            const null_t &value
    ) {
        (void) value;
        auto index(find_parameter_index(parameter, stmt));
        throw_on_bind_error(sqlite3_bind_null(stmt.get(), index), parameter);
    }

    template<>
    void bind<std::string>(
            const std::string &parameter,
            const std::string &value
    ) {
        auto index(find_parameter_index(parameter, stmt));
        auto status(sqlite3_bind_text(
            stmt.get(), index, value.c_str(), value.size(), SQLITE_STATIC
        ));
        throw_on_bind_error(status, parameter);
    }

    void bind(const std::string &parameter, const char * value) {
        auto index(find_parameter_index(parameter, stmt));
        auto status(sqlite3_bind_text(
            stmt.get(), index, value, -1, SQLITE_STATIC
        ));
        throw_on_bind_error(status, parameter);
    }

    void clear_bindings() {
        assert(stmt && "clear_bindings() called on null sqlite::sqlite_statement");
        auto status(sqlite3_clear_bindings(stmt.get()));
        if (status != SQLITE_OK)
            throw sqlite_error(status);
    }

    std::size_t parameter_count() const {
        assert(stmt && "parameter_count() called on null sqlite::sqlite_statement");
        return sqlite3_bind_parameter_count(stmt.get());
    }

    void throw_on_bind_error(
            const int status,
            const std::string &parameter
    ) const {
        if (status != SQLITE_OK)
            throw sqlite_error(stmt, "while binding parameter '" + parameter + "'");
    }

    std::ostream& operator<<(std::ostream &os, const sqlite_statement &statement) {
        os << "sqlite_statement:\n"
              "  sql: " << sqlite3_sql(statement.stmt.get()) << "\n";
        return os;
    }

    result make_result(const sqlite_statement &statement) {
        (void) sqlite3_reset(statement.stmt.get());
        return statement.stmt;
    }

private:

    std::size_t find_parameter_index(const std::string &parameter, const std::shared_ptr<sqlite3_stmt> &stmt) {
        
        assert(stmt && "bind() called on null sqlite::sqlite_statement");
        sqlite3_reset(stmt.get());
        auto index(sqlite3_bind_parameter_index(stmt.get(), parameter.c_str()));
        if (! index)
            throw sqlite_error(stmt, "while binding parameter '" + parameter + "'");
        return index;
    }

};// class sqlite_statement