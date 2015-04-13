#pragma once

#include <string>
#include <exception>

namespace cw{
namespace platform{

class exception: public std::exception{
public:
	exception(const std::string& function);

    virtual ~exception() throw();

    virtual const char* what() const throw ();

private:
    std::string msg_;

};// class exception

}// namespace platform
}// namespace cw
 