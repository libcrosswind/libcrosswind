#pragma once

#include <memory>
#include <mutex>

namespace cw{
namespace functional{

	template<class Resource>
	class resource_property;

}// namespace functional
}// namespace cw


template<class Resource>
class cw::functional::resource_property{

public:
	template<class Creator, class Destructor, class... Arguments>
	resource_property(Creator c, Destructor d, Arguments&&... args): resource(make_resource(c, d, args...)){
	
	}

	Resource* acquire(){
        property_mutex.lock();
        return resource.get();
    }

    Resource* ptr(){ //This returns a raw pointer without locking the property. Not thread-safe.
        return resource.get();
    }

    void release(){
        property_mutex.unlock();
    }

protected:
	template<typename Creator, typename Destructor, typename... Arguments>
	auto make_resource(Creator c, Destructor d, Arguments&&... args)
	{
		auto r = c(std::forward<Arguments>(args)...);
		if (!r) { throw std::runtime_error {"Unable to create resource"}; }
		typedef typename std::decay<decltype(*r)>::type ResourceType;
		return std::shared_ptr<ResourceType>(r, d);
	}


private:
    std::mutex property_mutex;

	std::shared_ptr<Resource> resource;
};// class resource_property