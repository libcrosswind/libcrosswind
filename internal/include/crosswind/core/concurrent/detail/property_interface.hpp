#pragma once

#include <functional>

namespace cw{
namespace core{
namespace concurrent{
namespace detail{

	template<class T>
	class property_interface;

}// namespace detail
}// namespace concurrent
}// namespace core
}// namespace cw



template<class T>
class cw::core::concurrent::detail::property_interface{
public:
    property_interface(){
        init();
    }

    property_interface(const T& value){
        init();
    }


/*    virtual operator T(){//Won't implement yet, SFINAE not ready
        return this->get();
    }

    virtual void operator=(const T& other){
        this->set(other);
    }

    virtual operator +(const T& other){

        if(has_plus<T>::value){
            return this->get() + other;
        } else {
            return this->get();
        }

    }

    virtual operator -(const T& other){
        return this->get() - other;
    }*/

    std::function<void(const T&)> set;
    std::function<T(void)> get;

protected:
    ~property_interface(){

    }
    
    virtual void init() {
        
        set = [this](const T& value){

        };

        get = [this](){
            return T();
        };

    }

};