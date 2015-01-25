#pragma once

#include <algorithm>
#include <functional>
#include <forward_list>

namespace cw{
	template<typename... Arguments>
	class delegate{

	public:

		void operator()(Arguments... args){

			std::for_each(
			    callbacks.begin(),
			    callbacks.end(),
			    [&](std::function<void(Arguments... args)> const& callback) {  callback(args...); }
			);
		}


		void operator+=(std::function<void(Arguments... args)> function){
	        auto before_end = callbacks.before_begin();
	        for (auto& _ : callbacks)
	            ++ before_end;

	        callbacks.insert_after(before_end, function); //TODO need to replace this and check performance.
		}

	/* //TODO

		void operator-=(std::function<void(Arguments... args)> function){
			callbacks.erase(function);
		}
	*/

	private:
	    std::forward_list<std::function<void(Arguments... args)> > callbacks;

	};	
}
