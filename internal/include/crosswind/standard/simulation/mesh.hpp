#pragma once

#include <Crosswind/events/delegate.hpp>


namespace cw{
	namespace graphics{

			    class mesh{

			    public:
			        mesh(): position (new vector3<double>(0.0, 0.0, 0.0), 
			        		dimension(new vector3<double>(1.0, 1.0, 1.0){
			            visible = true;
			        }

			    public:
			        //////////////////Position///////////////////////
			        void x(auto x) {position->x = x; }
			        auto x(){ return position->x; }

			        void y(auto y) { position->y = y; }
			        auto y(){ return position->y; }

			        void z(auto z) { position->z = z; }
			        auto z(){ return position->z; }

			        //////////////////Dimension///////////////////////
			        void width  (auto w) { dimension->x = w; }
			        auto width(){ return dimension->x; }

			        void height (auto h) { dimension->y = h; }
			        auto height(auto h) { return dimension->y; }

			        void depth(auto d){ dimension->z = d; }
			        auto depth(){ return dimension->z; }

			        //Positioning
			        auto contains_x(auto x) { return x >= this->x() && x <= this->width()  + this->x(); }
			        auto contains_y(auto y) { return y >= this->y() && y <= this->height() + this->y(); }

			        auto collides_x(auto x) { return x == this->get_x() || x == this->get_x() + this->get_width();  }
			        auto collides_y(auto y) { return y == this->get_y() || y == this->get_y() + this->get_height(); }

			        bool intersects_x(auto x){ return contains_x(x) || collides_x(x); }
			        bool intersects_y(auto y){ return contains_y(y) || collides_y(y); }

			        auto contains_xy(auto x, auto y)     { return contains_x(x)       && contains_y(y);        }
			        auto collides_xy(auto x, auto y)     { return collides_x(x)       && collides_y(y);        }
			        auto intersects_xy(auto x, auto y)   { return contains_xy(x, y)   || collides_xy(x, y);    }

			        atomical_property<bool> visible;

			    protected:
			        std::unique_ptr<vector3<double> > position;
			        std::unique_ptr<vector3<double> > dimension;

			        delegate<void> on_dimension_set;
			    };

		}
	}
}