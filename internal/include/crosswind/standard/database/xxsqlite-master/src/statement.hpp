#pragma once 

namespace cw{
namespace standard{
namespace database{

class sqlite_statemet;
class sqlite_blob;


}
}
}


#include "result.hpp"

#include <cstddef>

struct sqlite3;
struct sqlite3_stmt;

namespace sqlite {

class blob;
class statement;

enum class null_t {
    null
};
static const null_t null = null_t::null;

class statement
{
public:
    statement(const std::shared_ptr<sqlite3_stmt> &statement);
    statement(const statement &other) = delete;
    statement(statement &&other) = default;

    statement& operator=(const statement &other) = delete;
    statement& operator=(statement &&other) = default;

    std::size_t parameter_count() const;
    template<typename T>
    void bind(const std::string &parameter, const T &value);
    void bind(const std::string &parameter, const char *value);
    void clear_bindings();

    friend std::ostream& operator<<(
        std::ostream &os, const statement &statement
    );

private:
    void throw_on_bind_error(
            const int status,
            const std::string &parameter
    ) const;
    friend result make_result(const statement &statement);

private:
    std::shared_ptr<sqlite3_stmt> stmt;
};

} // namespace sqlite

