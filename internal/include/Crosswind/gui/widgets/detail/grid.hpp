#pragma once

namespace cw{
	class grid{

public:
       void attach(std::shared_ptr<widget> element) {
            std::lock_guard<std::mutex> lock(element_mutex);
            elements.push_back(element);
        }

        void detach(std::shared_ptr<widget> element){
            std::lock_guard<std::mutex> lock(element_mutex);//TODO

        }

protected:
	 std::vector<std::shared_ptr<widget>> elements; //Attached elements.

private:
     std::mutex element_mutex;
       
	};
}