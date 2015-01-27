#pragma once


namespace cw{
	class widget_container{
		
		
		
	};
}

	on_mouse_down += [this](){

		class data{
		public:
		    data():num(10){}
		    int num;
		};

		std::shared_ptr<data> number_data(new data());

		return [number_data](int x, int y, int button){

		        if(!this->pressed.load()){
		            if(this->contains_xy(x, y)){
		                this->pressed.store(true);
		                this->switch_texture("current", textures["on"]);
		                std::cout<<number_data->num<<std::endl;
		            }
		        }
		    }

	}();