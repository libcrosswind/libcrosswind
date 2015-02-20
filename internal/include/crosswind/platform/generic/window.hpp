#pragma once

#include <string>
#include <SDL2/SDL_video.h>

#include <crosswind/core/concurrent/hollow_property.hpp>
#include <crosswind/core/concurrent/resource_property.hpp>
#include <crosswind/standard/geometry/point.hpp>

namespace cw{
namespace platform{
namespace generic{

	class window;

}// namespace generic
}// namespace platform
}// namespace cw

class cw::platform::generic::window{
public:
	core::concurrent::hollow_property<std::string> title;
	core::concurrent::hollow_property<float> brightness;
	core::concurrent::hollow_property<standard::geometry::point> size;
	core::concurrent::hollow_property<standard::geometry::point> position;

	template<typename... Args>
	window(Args args): window_(SDL_CreateWindow, SDL_DestroyWindow, args...){
		//const std::string& title, int x, int y, int w, int h, Uint32 flags) {

		title.set = [&window_](const std::string& text){
			auto& window_ptr = window_.acquire();
			SDL_SetWindowTitle(window_, title.c_str());
			window_.release();
		};

		title.get = [&window_](){
			std::string text;

			auto& window_ptr = window_.acquire();
			text = SDL_GetWindowTitle(window_);
			window_.release();

			return text;
		};

		brightness.set = [&window_](const float& bright){
			auto& window_ptr = window_.acquire();

			if (SDL_SetWindowBrightness(window_ptr, brightness) != 0)
				throw sdl_exception("SDL_SetWindowBrightness");

			window_.release();
		};

		brightness.get = [&window_](){
			float bright;

			auto& window_ptr = window_.acquire();
			bright = SDL_GetWindowBrightness(window_ptr);
			window_.release();

			return bright;
		};

		size.set = [&window_](const standard::geometry::point& new_size){
			auto& window_ptr = window_.acquire();
			SDL_SetWindowSize(window_, new_size.x, new_size.y);
			window_.release();
		};

		size.get = [&window_](){
			int w, h;

			auto& window_ptr = window_.acquire();
			SDL_GetWindowSize(window_ptr, &w, &h);
			window_.release();

			return standard::geometry::point(w, h);
		};

		position.set = [&window_](const standard::geometry::point& new_size){
			auto& window_ptr = window_.acquire();
			SDL_SetWindowPosition(window_, new_size.x, new_size.y);
			window_.release();
		};

		position.get = [&window_](){
			int w, h;

			auto& window_ptr = window_.acquire();
			SDL_GetWindowPosition(window_ptr, &w, &h);
			window_.release();

			return standard::geometry::point(w, h);
		};

	}

	void maximize() {
		auto& window_ptr = window_.acquire();
		SDL_MaximizeWindow(window_ptr);
		window_.release();
	}

	void minimize() {
		auto& window_ptr = window_.acquire();
		SDL_MinimizeWindow(window_ptr);
		window_.release();
	}

	void show() {
		auto& window_ptr = window_.acquire();		
		SDL_ShowWindow(window_ptr);
		window_.release();
	}

	void hide() {
		auto& window_ptr = window_.acquire();
		SDL_HideWindow(window_ptr);
		window_.release();
	}

	void restore() {
		auto& window_ptr = window_.acquire();
		SDL_RestoreWindow(window_ptr);
		window_.release();
	}

	void raise() {
		auto& window_ptr = window_.acquire();
		SDL_RaiseWindow(window_ptr);
		window_.release();
	}

private:
	core::concurrent::resource_property<SDL_Window> window_;
};