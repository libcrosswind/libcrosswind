#pragma once

#include <exception>

namespace cw{
namespace platform{
namespace backend{
namespace interface{
namespace core{

    class exception;

}// namespace core
}// namespace interface
}// namespace backend
}// namespace platform
}// namespace cw


class cw::platform::backend::interface::core::exception: public std::exception{
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
    /** Error message.
     */
    std::string msg_;
};// class exception