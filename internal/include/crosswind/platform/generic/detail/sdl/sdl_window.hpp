#pragma once

#include <string>
#include <SDL2/SDL_video.h>

#include <crosswind/core/concurrent/hollow_property.hpp>
#include <crosswind/core/concurrent/resource_property.hpp>
#include <crosswind/standard/geometry/point.hpp>
#include <crosswind/platform/generic/detail/sdl/sdl_exception.hpp>
namespace cw{
namespace platform{
namespace generic{
namespace detail{
namespace sdl{

	class sdl_window;

}// namespace sdl
}// namespace detail
}// namespace generic
}// namespace platform
}// namespace cw

class cw::platform::generic::detail::sdl::sdl_window{
public:
	core::concurrent::hollow_property<std::string> title;
	core::concurrent::hollow_property<float> brightness;
	core::concurrent::hollow_property<standard::geometry::point<int> > size;
	core::concurrent::hollow_property<standard::geometry::point<int> > position;

	template<typename... Args>
	sdl_window(Args... args): window_(SDL_CreateWindow, SDL_DestroyWindow, args...){
		//const std::string& title, int x, int y, int w, int h, Uint32 flags) {

		title.set = [this](const std::string& text){
			auto window_ptr = this->window_.acquire();
			SDL_SetWindowTitle(window_ptr, title.get().c_str());
			window_.release();
		};

		title.get = [this](){
			std::string text;

			auto window_ptr = window_.acquire();
			text = SDL_GetWindowTitle(window_ptr);
			window_.release();

			return text;
		};

		brightness.set = [this](const float& bright){
			auto window_ptr = this->window_.acquire();

			if (SDL_SetWindowBrightness(window_ptr, brightness) != 0)
				throw sdl_exception("SDL_SetWindowBrightness");

			window_.release();
		};

		brightness.get = [this](){
			float bright;

			auto window_ptr = this->window_.acquire();
			bright = SDL_GetWindowBrightness(window_ptr);
			window_.release();

			return bright;
		};

		size.set = [this](const standard::geometry::point<int>& new_size){
			auto window_ptr = this->window_.acquire();
			SDL_SetWindowSize(window_ptr, new_size.x, new_size.y);
			window_.release();
		};

		size.get = [this](){
			int w, h;

			auto window_ptr = this->window_.acquire();
			SDL_GetWindowSize(window_ptr, &w, &h);
			window_.release();

			return standard::geometry::point<int>(w, h);
		};

		position.set = [this](const standard::geometry::point<int>& new_size){
			auto window_ptr = this->window_.acquire();
			SDL_SetWindowPosition(window_ptr, new_size.x, new_size.y);
			window_.release();
		};

		position.get = [this](){
			int w, h;

			auto window_ptr = this->window_.acquire();
			SDL_GetWindowPosition(window_ptr, &w, &h);
			window_.release();

			return standard::geometry::point<int>(w, h);
		};

	}

	void maximize() {
		auto window_ptr = window_.acquire();
		SDL_MaximizeWindow(window_ptr);
		window_.release();
	}

	void minimize() {
		auto window_ptr = window_.acquire();
		SDL_MinimizeWindow(window_ptr);
		window_.release();
	}

	void show() {
		auto window_ptr = window_.acquire();
		SDL_ShowWindow(window_ptr);
		window_.release();
	}

	void hide() {
		auto window_ptr = window_.acquire();
		SDL_HideWindow(window_ptr);
		window_.release();
	}

	void restore() {
		auto window_ptr = window_.acquire();
		SDL_RestoreWindow(window_ptr);
		window_.release();
	}

	void raise() {
		auto window_ptr = window_.acquire();
		SDL_RaiseWindow(window_ptr);
		window_.release();
	}

private:
	core::concurrent::resource_property<SDL_Window> window_;
};