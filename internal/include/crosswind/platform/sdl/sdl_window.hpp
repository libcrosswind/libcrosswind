#pragma once

#include <string>
#include <SDL2/SDL_video.h>

#include <crosswind/concurrent/hollow_property.hpp>
#include <crosswind/concurrent/resource_property.hpp>
#include <crosswind/platform/sdl/sdl_exception.hpp>
#include <crosswind/geometry/point.hpp>

namespace cw{
namespace platform{
namespace sdl{

	class sdl_window;

}// namespace sdl
}// namespace platform
}// namespace cw

class cw::platform::sdl::sdl_window{
public:
	concurrent::hollow_property<std::string> title;
	concurrent::hollow_property<float> brightness;
	concurrent::hollow_property<geometry::point<int> > size;
	concurrent::hollow_property<geometry::point<int> > position;
	concurrent::resource_property<SDL_Window> window;

	template<typename... Args>
	sdl_window(Args... args): window(SDL_CreateWindow, SDL_DestroyWindow, args...){
		//const std::string& title, int x, int y, int w, int h, Uint32 flags) {

		title.set = [this](const std::string& text){
			auto window_ptr = this->window.acquire();
			SDL_SetWindowTitle(window_ptr, title.get().c_str());
			window.release();
		};

		title.get = [this](){
			std::string text;

			auto window_ptr = window.acquire();
			text = SDL_GetWindowTitle(window_ptr);
			window.release();

			return text;
		};

		brightness.set = [this](const float& bright){
			auto window_ptr = this->window.acquire();

			if (SDL_SetWindowBrightness(window_ptr, brightness) != 0)
				throw sdl_exception("SDL_SetWindowBrightness");

			window.release();
		};

		brightness.get = [this](){
			float bright;

			auto window_ptr = this->window.acquire();
			bright = SDL_GetWindowBrightness(window_ptr);
			window.release();

			return bright;
		};

		size.set = [this](const geometry::point<int>& new_size){
			auto window_ptr = this->window.acquire();
			SDL_SetWindowSize(window_ptr, new_size.x, new_size.y);
			window.release();
		};

		size.get = [this](){
			int w, h;

			auto window_ptr = this->window.acquire();
			SDL_GetWindowSize(window_ptr, &w, &h);
			window.release();

			return geometry::point<int>(w, h);
		};

		position.set = [this](const geometry::point<int>& new_size){
			auto window_ptr = this->window.acquire();
			SDL_SetWindowPosition(window_ptr, new_size.x, new_size.y);
			window.release();
		};

		position.get = [this](){
			int w, h;

			auto window_ptr = this->window.acquire();
			SDL_GetWindowPosition(window_ptr, &w, &h);
			window.release();

			return geometry::point<int>(w, h);
		};

	}

	void maximize() {
		auto window_ptr = window.acquire();
		SDL_MaximizeWindow(window_ptr);
		window.release();
	}

	void minimize() {
		auto window_ptr = window.acquire();
		SDL_MinimizeWindow(window_ptr);
		window.release();
	}

	void show() {
		auto window_ptr = window.acquire();
		SDL_ShowWindow(window_ptr);
		window.release();
	}

	void hide() {
		auto window_ptr = window.acquire();
		SDL_HideWindow(window_ptr);
		window.release();
	}

	void restore() {
		auto window_ptr = window.acquire();
		SDL_RestoreWindow(window_ptr);
		window.release();
	}

	void raise() {
		auto window_ptr = window.acquire();
		SDL_RaiseWindow(window_ptr);
		window.release();
	}

};// class sdl_window