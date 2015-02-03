#pragma once 

#include <memory>
#include <map>
#include <string>

#include <Crosswind/graphics/point_xyz.hpp>
#include <Crosswind/graphics/dimension_xyz.hpp>
#include <Crosswind/util/math.hpp>

namespace cw {

    class object_xyz{

    public:

        object_xyz(){

            real_position  = std::shared_ptr<point_xyz> (new  point_xyz(0.0, 0.0, 0.0));
            absolute_position  = std::shared_ptr<point_xyz> (new  point_xyz(0.0, 0.0, 0.0));

            real_dimension = std::shared_ptr<dimension_xyz>(new dimension_xyz(0.0, 0.0, 0.0));
            absolute_dimension = std::shared_ptr<dimension_xyz>(new dimension_xyz(0.0, 0.0, 0.0));

            set_visible(false);
        }

    public:
        //////////////////Real dimension///////////////////////
        void set_width  (double w) {
            real_dimension->width.store(w);
            on_dimension_set();
        }

        void set_height (double h) {
            real_dimension->height.store(h);
            on_dimension_set();
        }

        void set_depth  (double d) {
            real_dimension->depth.store(d);
            on_dimension_set();
        }

        double get_width   ()  { return real_dimension->width.load();   }
        double get_height  ()  { return real_dimension->height.load();  }
        double get_depth   ()  { return real_dimension->depth.load();   }

        //////////////////Absolute dimension///////////////////////
        void set_absolute_width  (double w) {
            absolute_dimension->width.store(w);
            on_dimension_set();
        }

        void set_absolute_height (double h) {
            absolute_dimension->height.store(h);
            on_dimension_set();
        }

        void set_absolute_depth  (double d) {
            absolute_dimension->depth.store(d);
            on_dimension_set();
        }

        double get_absolute_width   ()  { return absolute_dimension->width.load();   }
        double get_absolute_height  ()  { return absolute_dimension->height.load();  }
        double get_absolute_depth   ()  { return absolute_dimension->depth.load();   }

        //////////////////Real position///////////////////////
        void set_x(double x) {
            real_position->x.store(math::clamp<double>(x, -1.0, 2.0));
        }

        void set_y(double y) {
            real_position->y.store(math::clamp<double>(y, -1.0, 2.0));
        }

        void set_z(double z) {
            real_position->z.store(math::clamp<double>(z, -1.0, 2.0));
        }

        double get_x() { return real_position->x.load(); }
        double get_y() { return real_position->y.load(); }
        double get_z() { return real_position->z.load(); }

        //////////////////Absolute position///////////////////////
        void set_absolute_x(double x) {
            absolute_position->x.store(x);
        }

        void set_absolute_y(double y) {
            absolute_position->y.store(y);
        }

        void set_absolute_z(double z) {
            absolute_position->z.store(z);
        }

        double get_absolute_x() { return absolute_position->x.load(); }
        double get_absolute_y() { return absolute_position->y.load(); }
        double get_absolute_z() { return absolute_position->z.load(); }


        bool contains_x(double x) { return x >= get_absolute_x() && x <= get_width()  + get_absolute_x(); }
        bool contains_y(double y) { return y >= get_absolute_y() && y <= get_height() + get_absolute_y(); }

        bool collides_x(double x) { return x == get_absolute_x() || x == get_absolute_x() + get_width();  }
        bool collides_y(double y) { return y == get_absolute_y() || y == get_absolute_y() + get_height(); }

        bool intersects_x(double x){ return contains_x(x) || collides_x(x); }
        bool intersects_y(double y){ return contains_y(y) || collides_y(y); }

        bool contains_xy(double x, double y)     { return contains_x(x)       && contains_y(y);        }
        bool collides_xy(double x, double y)     { return collides_x(x)       && collides_y(y);        }
        bool intersects_xy(double x, double y)   { return contains_xy(x, y)   || collides_xy(x, y);    }

        void   set_visible(bool visible)    { is_visible.store(visible); }
        bool   get_visible()                { return is_visible.load();  }

    protected:
        std::atomic<bool> is_visible;

        std::shared_ptr<point_xyz> real_position;
        std::shared_ptr<point_xyz> absolute_position;

        std::shared_ptr<dimension_xyz> real_dimension;
        std::shared_ptr<dimension_xyz> absolute_dimension;

        delegate<void> on_dimension_set;

    };

}
