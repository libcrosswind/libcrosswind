#pragma once

#include "glm/glm.hpp"

#include "crosswind/graphical/object/mesh.hpp"

namespace cw {
    namespace geometry {

        class rectangle {
        public:
            rectangle(const glm::ivec2& location, const glm::ivec2& size) {
                X = location.x;
                Y = location.y;
                Width = size.x;
                Height = size.y;
            }

            rectangle() {
                X = 0;
                Y = 0;
                Width = 0;
                Height = 0;
            }


            int left() {
                return X;
            }

            int right() {
                return X + Width;
            }

            int top() {
                return Y;
            }

            int bottom() {
                return Y + Height;
            }

            glm::ivec2 centre() {
                return glm::ivec2(left() + (Width / 2), top() + (Height / 2));
            }

            bool contains(rectangle rect)
            {
                return (rect.X >= X && rect.Y >= Y && rect.right() <= right() && rect.bottom() <= bottom());
            }

            bool intersects(rectangle rect)
            {
                return !(rect.X > right() || rect.right()< X || rect.Y > bottom() || rect.bottom() < Y);
            }

            void set_origin(const glm::ivec2& origin) {
                X = origin.x;
                Y = origin.y;
            }


        public:
            int X;
            int Y;
            int Width;
            int Height;

        };// class sprite

    }// namespace graphical
}// namespace cw