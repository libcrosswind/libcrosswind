#pragma once

#include <functional>
#include <map> 
#include <string>

#include <crosswind/concurrent/mutex_container.hpp>
#include <crosswind/platform/sdl/sdl_exception.hpp>

namespace cw{
namespace container{

    template<class T>
    class cache;

}// namespace container
}// namespace cw

template<class T>
class cw::container::cache{
public:
    typedef std::function<void(std::map<std::string, T>&)> cache_manipulation;

    void store(const std::string& resource_name, const T& data){
        cache[resource_name] = data;
    }

    void store(const std::string& resource_name){
        if(!source)
            throw platform::sdl::sdl_exception("No source loaded");
        else
            cache[resource_name] = source(resource_name);
    }

    T load(const std::string& resource_name){
        return cache[resource_name];
    }

    void swap(const std::string& previous_resource, const std::string& new_resource){
   //     cache(previous_resource, cache(new_resource));
    }

    void clear(){
        cache.clear();
    }

    void add_manipulation(const std::string& name, cache_manipulation manipulation){
 //       manipulations(name, manipulation);
    }

    void remove_manipulation(std::string name){
        
    }

    void apply_manipulation(const std::string& name){
       // cache.apply(manipulations(name));
    }

    std::function<T(const std::string&)> source;

private:
    //std::map<std::string, T> cache;
    //std::map<std::string, cache_manipulation> manipulations;
    
};// class cache

