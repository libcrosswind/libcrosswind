#pragma once

#include <crosswind/platform/generic/sdl_exception.hpp>

namespace cw{
namespace standard{
namespace drawing{

  class image;

}// namespace drawing
}// namespace standard
}// namespace cw


class cw::standard::drawing::image{
public:
  image(int flags) {
    if ((IMG_Init(flags) & flags) != flags)
      throw platform::generic::detail::sdl::sdl_exception("IMG_Init");
  }

  // non-copyable
  image(const image& other) = delete;
  image& operator=(const image& other) = delete;

  // non-movable
  image(image&& other) = delete;
  image& operator=(image&& other) = delete;


  image() {
    IMG_Quit();
  }

  int init_more(int flags) {
    int ret;
    if (((ret = IMG_Init(flags)) & flags) != flags)
      throw platform::generic::detail::sdl::sdl_exception("IMG_Init");
    return ret;
  }

  int init_flags() {
    return IMG_Init(0);
  }



};
 