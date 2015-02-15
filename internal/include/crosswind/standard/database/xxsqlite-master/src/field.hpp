


#include <memory>
#include <string>
#include <cstddef>

struct sqlite3_stmt;

namespace sqlite {

class field {
public:
    field(
            const std::shared_ptr<sqlite3_stmt> &statement,
            const std::size_t &parameter_index
    );

    bool is_null() const;
    explicit operator bool() const;

    std::string column_name() const;
    template<typename T>
    T as() const;

private:
    std::shared_ptr<sqlite3_stmt> stmt;
    const std::size_t index;
};

}   // namespace sqlite

#endif // SQLITE_FIELD_H
