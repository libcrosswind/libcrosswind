#pragma once

#include <exception>
#include <string>

namespace cw{
namespace interface{
namespace platform{

    class exception;

}// namespace platform
}// namespace interface
}// namespace cw


class cw::interface::platform::exception: public std::exception{
public:
    explicit exception(const char* message):
      msg_(message){

    }

    explicit exception(const std::string& message):
      msg_(message){

    }

    virtual ~exception() throw (){

    }

    virtual const char* what() const throw (){
       return msg_.c_str();
    }

protected:
    std::string msg_;
    
};// class exception