#pragma once

#include "database.hpp"
#include "error.hpp"

#include <sqlite3.h>

#include <ostream>
#include <sstream>
#include <cassert>

namespace cw{
namespace standard{
namespace database{
namespace sqlite{

    class sqlite_database;
    
}// namespace sqlite
}// namespace database
}// namespace standard
}// namespace cw

class cw::standard::database::sqlite::sqlite_database{

public:
    enum access_mode {
        read_only         = 0x01,
        read_write        = 0x02,
        read_write_create = 0x06
    };

    enum cache_type {
        shared_cache  = 0x00020000,
        private_cache = 0x00040000
    };



public:
    sqlite_database(const std::string &path,
             const access_mode &permissions,
             const cache_type &visibility) {

        int perms(permissions | visibility);

        [](const auto status, auto* db){
            if (status != SQLITE_OK) {
                    sqlite3_close_v2(db);
                    throw error(status);
            }
        }(sqlite3_open_v2(path.c_str(), &db, perms, nullptr), db);


    }

    sqlite_database(const special_t &,
             const access_mode &permissions,
             const cache_type &visibility) {
        std::stringstream uri;
        uri << "file::memory:?" << permissions << "&" << visibility;
        std::string path(uri.str());

        [](const auto status, auto* db){
            if (status != SQLITE_OK) {
                    sqlite3_close_v2(db);
                    throw error(status);
            }
        }(sqlite3_open_v2(path.c_str(), &db, permissions | SQLITE_OPEN_URI, nullptr), 
          db);

    }

    ~sqlite_database() {
        close();
    }

    result execute(const std::string &sql) {
        return create_statement(sql);
    }

    result execute(const statement &statement) {
        return make_result(statement);
    }

    std::size_t size() const {
        std::size_t page_count(execute_scalar<std::size_t>("PRAGMA page_count;"));
        std::size_t page_size(execute_scalar<std::size_t>("PRAGMA page_size;"));
        return page_count * page_size;
    }

    void close() noexcept {
        auto status(sqlite3_close(db));
        db = nullptr;
        // Can't throw, called from destructor
        assert(status == SQLITE_OK &&
            "sqlite_database closed with active statements or unfinished backups");
    }

    std::shared_ptr<sqlite3_stmt> create_statement(const std::string &sql) const {
        sqlite3_stmt *stmt(nullptr);
        auto status(sqlite3_prepare_v2(
            db, sql.c_str(), sql.size(), &stmt, nullptr
        ));
        if (status != SQLITE_OK)
            throw error(status, "while preparing sql statement '" + sql + "'");
        return std::shared_ptr<sqlite3_stmt>(stmt, &sqlite3_finalize);
    }

    statement prepare_statement(
            const std::string &sql
    ) const {
        return create_statement(sql);
    }

    std::ostream& operator<<(std::ostream &os, const sqlite_database &db) {
        os << "sqlite_database:\n"
              "  open: " << ((db.db == nullptr) ? "false" : "true") << "\n";
        return os;
    }

    void as_transaction(
            sqlite_database &db,
            const std::function<void(sqlite_database &)> &operations
    ) try {
        db.execute("BEGIN;");
        operations(db);
        db.execute("COMMIT;");
    } catch (...) {
        db.execute("ROLLBACK;");
        throw;
    }


 
    std::ostream& operator<<(std::ostream &os, const access_mode &mode) {
        os << "mode=";
        switch (mode) {
        case read_only:         os << "ro";  break;
        case read_write:        os << "rw";  break;
        case read_write_create: os << "rwc"; break;
        }
        return os;
    }

    std::ostream& operator<<(std::ostream &os, const cache_type &cache) {
        os << "cache=";
        switch (cache) {
        case private_cache: os << "private"; break;
        case shared_cache:  os << "shared";  break;
        }
        return os;
    }


};// class sqlite_database
