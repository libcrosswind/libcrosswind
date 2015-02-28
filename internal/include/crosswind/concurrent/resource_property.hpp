#pragma once

#include <memory>

namespace cw{
namespace concurrent{

	template<class Resource>
	class resource_property;

}// namespace concurrent
}// namespace cw


template<class Resource>
class cw::concurrent::resource_property{

	typedef std::unique_ptr<Resource, void (*)(Resource*)> resource_ptr;

public:
	template<class Creator, class Destructor, class... Arguments>
	resource_property(Creator c, Destructor d, Arguments&&... args): resource(make_resource(c, d, args...)){
	}



	Resource* acquire(){
        property_mutex.lock();
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
		return std::unique_ptr<ResourceType, void(*)(ResourceType*)>(r, d);
	}


private:
    std::mutex property_mutex;

	resource_ptr resource;
};// class resource_property


