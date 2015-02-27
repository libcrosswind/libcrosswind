#pragma once

#include <memory>
#include <string>
#include <cstddef>
#include <cassert>

#include <sqlite3.h>

namespace cw{
namespace standard{
namespace database{
namespace sqlite{

  class sqlite_field;

}// namespace sqlite
}// namespace database
}// namespace standard
}// namespace cw

class cw::standard::database::sqlite::sqlite_field{
public:
    sqlite_field(
            const std::shared_ptr<sqlite3_stmt> &statement,
            const std::size_t &parameter_index
    ): stmt(statement), index(parameter_index) {
        assert(statement && "received null sqlite3_stmt");
    }

    bool is_null() const {
        return sqlite3_column_type(stmt.get(), index) == SQLITE_NULL;
    }

    explicit operator bool() const {
        return ! is_null();
    }

    std::string column_name() const {
        const char *name(sqlite3_column_name(stmt.get(), index));
        return name ? name : "";
    }

    template<>
    blob as<blob>() const {
        assert(false && "blob support not implemented");
        return blob();
    }

    template<>
    double as<double>() const {
        if (is_null())
            return 0.0;
        return sqlite3_column_double(stmt.get(), index);
    }

    template<>
    int as<int>() const {
        if (is_null())
            return 0;
        return sqlite3_column_int(stmt.get(), index);
    }

    template<>
    bool as<bool>() const {
        if (is_null())
            return false;
        return static_cast<bool>(sqlite3_column_int(stmt.get(), index));
    }

    template<>
    int64_t as<int64_t>() const {
        if (is_null())
            return 0;
        return sqlite3_column_int64(stmt.get(), index);
    }

    template<>
    std::size_t as<std::size_t>() const {
        if (is_null())
            return 0;
        return sqlite3_column_int64(stmt.get(), index);
    }

    template<>
    char as<char>() const {
        if (is_null())
            return '\0';
        return *reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), index));
    }

    template<>
    std::string as<std::string>() const {
        if (is_null())
            return "";
        return reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), index));
    }

private:
    std::shared_ptr<sqlite3_stmt> stmt;
    const std::size_t index;
};