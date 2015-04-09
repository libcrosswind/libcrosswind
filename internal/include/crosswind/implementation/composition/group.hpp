#pragma once

namespace cw{
namespace implementation{
namespace composition{
	
	class group;

}// namespace composition
}// namespace implementation
}// namespace cw

class cw::implementation::composition::group{
public:
	group(){

	}

	void add_actor(){

	}

	void get_actor(){

	}

	void remove_actor(){

	}

	std::function<void()> init;
	std::function<void()> deinit;
	std::function<void(const float&)> logic;

	virtual void update(const float& delta){

	}



private:
//	std::map<std::string, actor_ptr> actors;

};// class group