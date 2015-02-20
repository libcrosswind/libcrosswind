#pragma once


namespace cw{
namespace core{
namespace concurrent{

	template<class Resource>
	class resource_property;

}// namespace concurrent
}// namespace core
}// namespace cw


template<class Resource>
class cw::core::concurrent::resource_property{

	typedef std::unique_ptr<Resource, void (*)(Resource*)> resource_ptr;

public:
	template<class Creator, class Destructor, class... Arguments>
	resource_property(Creator c, Destructor d, Arguments&&... args){
	    auto r = c(std::forward<Arguments>(args)...);
	    if (!r) { throw std::runtime_error {"Unable to create resource"}; }
	    typedef typename std::decay<decltype(*r)>::type ResourceType;
	    resource = std::unique_ptr<ResourceType, void(*)(ResourceType*)>(r, d);
	}

    T& acquire(){
        property_mutex.lock();
        return resource;
    }

    void release(){
        property_mutex.unlock();
    }


private:
    std::mutex property_mutex;

	resource_ptr resource;
};


