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


            glm::ivec2 top_left() {
                return glm::ivec2(left(), top());
            }

            glm::ivec2 top_right() {
                return glm::ivec2(right(), top());
            }
            glm::ivec2 bottom_left() {
                return glm::ivec2(left(), bottom());
            }
            glm::ivec2 bottom_right() {
                return glm::ivec2(right(), bottom());
            }

            static rectangle intersection(rectangle first, rectangle second)
            {
                rectangle result;

                auto firstMinimum = first.top_left();
                auto firstMaximum = first.bottom_right();
                auto secondMinimum = second.top_left();
                auto secondMaximum = second.bottom_right();

                auto point_minimum = maximum(firstMinimum, secondMinimum);
                auto point_maximum = minimum(firstMaximum, secondMaximum);
                
                if ((point_maximum.x < point_minimum.x) || (point_maximum.y < point_minimum.y))
                    result = rectangle();
                else
                    result = create_from(point_minimum, point_maximum);

                return result;
            }

            static glm::ivec2 maximum(glm::ivec2 first, glm::ivec2 second)
            {
                return glm::ivec2(first.x > second.x ? first.x : second.x,
                    first.y > second.y ? first.y : second.y);
            }


            static glm::ivec2 minimum(glm::ivec2 first, glm::ivec2 second)
            {
                return glm::ivec2(first.x < second.x ? first.x : second.x,
                    first.y < second.y ? first.y : second.y);
            }



            static rectangle create_from(const glm::ivec2& minimum, const glm::ivec2& maximum)
            {
                rectangle result;

                result.X = minimum.x;
                result.Y = minimum.y;
                result.Width = maximum.x - minimum.x;
                result.Height = maximum.y - minimum.y;

                return result;
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