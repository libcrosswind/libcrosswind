#pragma once

#include <cassert>
#include <memory>

#include <sqlite3.h>

namespace cw{
namespace standard{
namespace database{
namespace sqlite{

  class sqlite_result;
  class sqlite_transaction_failed;

}// namespace sqlite
}// namespace database
}// namespace standard
}// namespace cw


class cw::standard::database::sqlite::sqlite_transaction_failed: public sqlite_error {
public:
    sqlite_transaction_failed(const int status): error(status) {}
};


class cw::standard::database::sqlite::sqlite_result{
public:
  class sqlite_const_iterator {
    public:

        sqlite_const_iterator(const std::shared_ptr<sqlite3_stmt> &statement, 
                              bool &at_end): 
        stmt(statement), end_reached(at_end), current_row(statement) {
            assert(statement && "null sqlite3_stmt provided");
        }

        bool operator==(const sqlite_const_iterator &other) const {
            return stmt == other.stmt && end_reached == other.end_reached;
        }

        bool operator!=(const sqlite_const_iterator &other) const {
            return ! (*this == other);
        }

        sqlite_const_iterator& operator++() {
            assert(!end_reached && "attempt to increment past last result");
            end_reached = step_result(stmt);
            current_row = stmt;
            return *this;
        }

        const sqlite_row& operator*() const {
            return current_row;
        }

        const sqlite_row* operator->() const {
            return &current_row;
        }


    private:
        std::shared_ptr<sqlite3_stmt> stmt;
        bool &end_reached;
        row current_row;
    };// class sqlite_const_iterator


    sqlite_result(const std::shared_ptr<sqlite3_stmt> &statement):
            stmt(statement), iterator_end(true){
        assert(statement && "null sqlite3_stmt provided");
        end_reached = step_result(stmt);
    }

    sqlite_result(sqlite_result &&other): iterator_end(true) {
        assert(&other != this && "attempt to move into self");
        stmt = std::move(other.stmt);
        end_reached = other.end_reached;
    }

    sqlite_result& operator=(sqlite_result &&other) {
        assert(&other != this && "attempt to move into self");
        stmt = std::move(other.stmt);
        end_reached = other.end_reached;
        return *this;
    }

    std::size_t row_modification_count() const {
        sqlite3 *db(sqlite3_db_handle(stmt.get()));
        assert(db && "unable to aquire associated database");
        return sqlite3_stmt_readonly(stmt.get()) ? 0 : sqlite3_changes(db);
    }

    const_iterator begin() const {
        return {stmt, end_reached};
    }

    const_iterator end() const {
        return {stmt, iterator_end};
    }


private:
  bool step_result(const std::shared_ptr<sqlite3_stmt> &stmt) {
    assert(stmt && "attempt to step null sqlite3_stmt");
    auto status(sqlite3_step(stmt.get()));
    switch (status) {
    case SQLITE_DONE:   return true;
    case SQLITE_ROW:    return false;
    case SQLITE_LOCKED: // fall-through
    case SQLITE_BUSY:   throw transaction_failed(status);
    default:            throw error(stmt);
    }
  }

  bool iterator_end; //(true);


private:
    std::shared_ptr<sqlite3_stmt> stmt;
    mutable bool end_reached = false;

};// class sqlite_result
