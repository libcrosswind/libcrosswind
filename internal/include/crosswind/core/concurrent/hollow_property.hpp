#pragma once

#include <functional>

namespace cw{
namespace core{
namespace concurrent{
	
	template<class T>
	class hollow_property;

}// namespace concurrent
}// namespace core
}// namespace cw


template<class T>
class cw::core::concurrent::hollow_property{
public:
	hollow_property(){
        init();
	}

    virtual operator T(){
        return this->get();
    }

    void operator=(const T& other){
        this->set(other);
    }

	std::function<void(const T&)> set;
	std::function<T(void)> get;

protected:
    virtual void init(){
        
        set = [this](const T& new_value){
            
        };

        get = [this](){
            return T();
        };

    }
};//class hollow_property