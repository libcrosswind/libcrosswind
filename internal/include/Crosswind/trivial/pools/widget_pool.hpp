#pragma once

#include <Crosswind/gui/widgets/detail/widget.hpp>
//#include <Crosswind/gui/widgets/window.hpp>
//#include <Crosswind/gui/widgets/textbox.hpp>
//#include <Crosswind/gui/widgets/label.hpp>
//#include <Crosswind/gui/widgets/panel.hpp>
/* TODO
    std::shared_ptr<cw::widget> window(new cw::window([](){
        std::shared_ptr<cw::util::flag_container> flags(new cw::util::flag_container());
        //  flags->set<cw::window::window_flags>(cw::window::window_flags::MULTITHREADED);
        return flags;
    }()));

    */ 

namespace cw{
	class widget_pool{
	public:
	    static auto create(double x, double y, double w, double h, std::string layout){

            cw::datatypes::json widget_layout;
            widget_layout.from_file("themes/blue/button.json");
            std::shared_ptr<widget> ptr(new widget());

            ptr->set_draggable(widget_layout.data()["draggable"]);


            for(auto& texture : widget_layout.data()["textures"]){

            }

/*
	        ptr->set_x(x);
	        ptr->set_y(y);
	        ptr->set_width(w);
	        ptr->set_height(h);
	        ptr->set_theme(theme);
*/
	        return ptr;
	    }
	};
}