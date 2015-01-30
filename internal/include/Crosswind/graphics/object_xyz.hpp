#pragma once 

#include <memory>
#include <map>
#include <string>

#include <Crosswind/graphics/point_xyz.hpp>
#include <Crosswind/graphics/dimension_xyz.hpp>

namespace cw {

    class object_xyz{

    public:

        object_xyz(){

            absolute_position  = std::shared_ptr<point_xyz> (new  point_xyz(0.0, 0.0, 0.0));
            real_position  = std::shared_ptr<point_xyz> (new  point_xyz(0.0, 0.0, 0.0));
            dimension = std::shared_ptr<dimension_xyz>(new dimension_xyz(0.0, 0.0, 0.0));
            set_visible(false);
        }

    public:
        void set_width  (double w) {
            dimension->width.store(w);
            on_dimension_set();
        }

        void set_height (double h) {
            dimension->height.store(h);
            on_dimension_set();
        }

        void set_depth  (double d) {
            dimension->depth.store(d);
            on_dimension_set();
        }

        double get_width   ()  { return dimension->width.load();   }
        double get_height  ()  { return dimension->height.load();  }
        double get_depth   ()  { return dimension->depth.load();   }

        void set_x(double x) {
            absolute_position->x.store(x);
        }

        void set_y(double y) {
            absolute_position->y.store(y);
        }

        void set_z(double z) {
            absolute_position->z.store(z);
        }

        double get_x() { return absolute_position->x.load(); }
        double get_y() { return absolute_position->y.load(); }
        double get_z() { return absolute_position->z.load(); }

        void set_real_x(double x) {
            real_position->x.store(x);
        }

        void set_real_y(double y) {
            real_position->y.store(y);
        }

        void set_real_z(double z) {
            real_position->z.store(z);
        }

        double get_real_x() { return real_position->x.load(); }
        double get_real_y() { return real_position->y.load(); }
        double get_real_z() { return real_position->z.load(); }


        bool contains_x(double x)            { return x >= get_x()    && x <= get_width()  + get_x();        }
        bool contains_y(double y)            { return y >= get_y()    && y <= get_height() + get_y();   }

        bool collides_x(double x)            { return x == get_x() || x == get_x() + get_width(); }
        bool collides_y(double y)            { return y == get_y() || y == get_y() + get_height(); }

        bool intersects_x(double x){ return contains_x(x) || collides_x(x); }
        bool intersects_y(double y){ return contains_y(y) || collides_y(y); }

        bool contains_xy(double x, double y)     { return contains_x(x)       && contains_y(y);        }
        bool collides_xy(double x, double y)     { return collides_x(x)       && collides_y(y);        }
        bool intersects_xy(double x, double y)   { return contains_xy(x, y)   || collides_xy(x, y);    }

        void    set_visible(bool visible)   { is_visible.store(visible); }
        bool   get_visible()                { return is_visible.load();  }


    protected:
        std::atomic<bool> is_visible;
        std::shared_ptr<point_xyz> absolute_position;
        std::shared_ptr<point_xyz> real_position;

        std::shared_ptr<dimension_xyz> dimension;

        delegate<> on_dimension_set;

    };

}
