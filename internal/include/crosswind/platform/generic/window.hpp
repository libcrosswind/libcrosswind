#pragma once

#include <string>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
//#include <SDL2/SDL.h>


#include <crosswind/standard/drawing/surface.hpp>
#include <crosswind/standard/geometry/point.hpp>

namespace cw{
namespace platform{
namespace generic{

	class window;

}
}
}

class cw::platform::generic::window{
public:
	window(SDL_Window* window) : window_(window) {
	}

	window(const std::string& title, int x, int y, int w, int h, Uint32 flags) {
		if ((window_ = SDL_CreateWindow(title.c_str(), x, y, w, h, flags)) == nullptr)
			throw sdl_exception("SDL_CreateWindow");
	}

	~window() {
		if (window_ != nullptr)
			SDL_DestroyWindow(window_);
	}

	window(window&& other) noexcept : window_(other.window_) {
		other.window_ = nullptr;
	}

	window& window::operator=(window&& other) noexcept {
		if (&other == this)
			return *this;
		if (window_ != nullptr)
			SDL_DestroyWindow(window_);
		window_ = other.window_;
		other.window_ = nullptr;
		return *this;
	}

	SDL_Window* get() const {
		return window_;
	}

	point get_size() const {
		int w, h;
		SDL_GetWindowSize(window_, &w, &h);
		return point(w, h);
	}

	int get_width() const {
		int w, h;
		SDL_GetWindowSize(window_, &w, &h);
		return w;
	}

	int get_height() const {
		int w, h;
		SDL_GetWindowSize(window_, &w, &h);
		return h;
	}

	window& set_title(const std::string& title) {
		SDL_SetWindowTitle(window_, title.c_str());
		return *this;
	}

	std::string get_title() const {
		return SDL_GetWindowTitle(window_);
	}

	window& maximize() {
		SDL_MaximizeWindow(window_);
		return *this;
	}

	window& minimize() {
		SDL_MinimizeWindow(window_);
		return *this;
	}

	window& hide() {
		SDL_HideWindow(window_);
		return *this;
	}

	window& restore() {
		SDL_RestoreWindow(window_);
		return *this;
	}

	window& raise() {
		SDL_RaiseWindow(window_);
		return *this;
	}

	window& show() {
		SDL_ShowWindow(window_);
		return *this;
	}

	window& set_fullscreen(int flags) {
		if (SDL_SetWindowFullscreen(window_, flags) != 0)
			throw Exception("SDL_SetWindowFullscreen");
		return *this;
	}

	window& set_size(int w, int h) {
		SDL_SetWindowSize(window_, w, h);
		return *this;
	}

	window& set_size(const point& size) {
		SDL_SetWindowSize(window_, size.x, size.y);
		return *this;
	}

	float get_brightness() const {
		return SDL_GetWindowBrightness(window_);
	}

	window& set_brightness(float brightness) {
		if (SDL_SetWindowBrightness(window_, brightness) != 0)
			throw sdl_exception("SDL_SetWindowBrightness");
		return *this;
	}

	point get_position() const {
		int x, y;
		SDL_GetWindowPosition(window_, &x, &y);
		return point(x, y);
	}

	window& set_position(int x, int y) {
		SDL_SetWindowPosition(window_, x, y);
		return *this;
	}

	window& set_position(const point& pos) {
		SDL_SetWindowPosition(window_, pos.x, pos.y);
		return *this;
	}

	point get_minimum_size() const {
		int w, h;
		SDL_GetWindowMinimumSize(window_, &w, &h);
		return point(w, h);
	}

	window& set_minimum_size(int w, int h) {
		SDL_SetWindowMinimumSize(window_, w, h);
		return *this;
	}

	window& set_minimum_size(const point& size) {
		SDL_SetWindowMinimumSize(window_, size.x, size.y);
		return *this;
	}

	point get_maximum_size() const {
		int w, h;
		SDL_GetWindowMaximumSize(window_, &w, &h);
		return point(w, h);
	}

	window& set_maximum_size(int w, int h) {
		SDL_SetWindowMaximumSize(window_, w, h);
		return *this;
	}

	window& set_maximum_size(const point& size) {
		SDL_SetWindowMaximumSize(window_, size.x, size.y);
		return *this;
	}

	bool get_grab() const {
		return SDL_GetWindowGrab(window_) == SDL_TRUE;
	}

	window& set_grab(bool grabbed) {
		SDL_SetWindowGrab(window_, grabbed ? SDL_TRUE : SDL_FALSE);
		return *this;
	}

	int get_display_index() const {
		int index = SDL_GetWindowDisplayIndex(window_);
		if (index < 0)
			throw sdl_exception("SDL_GetWindowDisplayIndex");
		return index;
	}

	void get_display_mode(SDL_DisplayMode& mode) const {
		if (SDL_GetWindowDisplayMode(window_, &mode) != 0)
			throw sdl_exception("SDL_GetWindowDisplayMode");
	}

	Uint32 get_flags() const {
		return SDL_GetWindowFlags(window_);
	}

	window& set_icon(const Surface& icon) {
		SDL_SetWindowIcon(window_, icon.Get());
		return *this;
	}

	window& set_bordered(bool bordered) {
		SDL_SetWindowBordered(window_, bordered ? SDL_TRUE : SDL_FALSE);
		return *this;
	}

private:
	SDL_Window* window_;
};