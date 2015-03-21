#pragma once

#include <string>

#include <glm/glm.hpp>

#include <crosswind/functional/hollow_property.hpp>
#include <crosswind/platform/backend/interface/core/detail/fps_limiter.hpp>

namespace cw{
namespace platform{
namespace backend{
namespace interface{
namespace core{

	class window;

}// namespace video
}// namespace interface
}// namespace backend
}// namespace platform
}// namespace cw

class cw::platform::backend::interface::core::window{
protected:
    window(float fps): fps_limiter(new detail::fps_limiter(fps)){

    }

public:

    virtual void maximize() = 0;
    virtual void minimize() = 0;
    virtual void show() = 0;
    virtual void hide() = 0;
    virtual void restore() = 0;
    virtual void raise() = 0;
    virtual void set_clear_color(const glm::vec4& color) = 0;
    virtual void clear() = 0;
    virtual void present() = 0;

    std::shared_ptr<detail::fps_limiter> fps_limiter;
    functional::hollow_property<std::string> title;
    functional::hollow_property<float> brightness;
    functional::hollow_property<glm::vec2> position;
    functional::hollow_property<glm::vec2> size;
};// class window
