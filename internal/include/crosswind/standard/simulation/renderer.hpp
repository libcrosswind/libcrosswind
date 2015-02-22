#pragma once

#include <vector>

#include <SDL2/SDL.h>


namespace cw{
namespace standard{
namespace simulation{

	class renderer;
	
}// namespace simulation
}// namespace standard
}// namespace cw


class cw::standard::simulation::renderer{
public:


	renderer(SDL_Renderer* renderer) : renderer_(renderer) {
	}

	renderer(Window& window, int index, Uint32 flags) {
		if ((renderer_ = SDL_CreateRenderer(window.Get(), index, flags)) == nullptr)
			throw cw::platform::generic::detail::sdl_exception("SDL_CreateRenderer");
	}

	~renderer() {
		if (renderer_ != nullptr)
			SDL_DestroyRenderer(renderer_);
	}


	void present() {
		SDL_RenderPresent(renderer_);
	}

	clear() {
		if (SDL_RenderClear(renderer_) != 0)
			throw cw::platform::generic::detail::sdl_exception("SDL_RenderClear");
	}

	void get_info(SDL_RendererInfo* info) {
		if (SDL_GetRendererInfo(renderer_, info) != 0)
			throw cw::platform::generic::detail::sdl_exception("SDL_GetRendererInfo");
	}

	void Renderer::GetInfo(SDL_RendererInfo& info) {
		if (SDL_GetRendererInfo(renderer_, &info) != 0)
			throw cw::platform::generic::detail::sdl_exception("SDL_GetRendererInfo");
	}

	void copy(texture& texture, const Optional<Rect>& srcrect, const Optional<Rect>& dstrect) {
		if (SDL_RenderCopy(renderer_, texture.Get(), srcrect ? &*srcrect : nullptr, dstrect ? &*dstrect : nullptr) != 0)
			throw cw::platform::generic::detail::sdl_exception("SDL_RenderCopy");
	}

    void copy(Texture& texture, const Optional<Rect>& srcrect, const Optional<Rect>& dstrect, double angle, const Optional<Point>& center, int flip) {
		if (SDL_RenderCopyEx(renderer_, texture.Get(), srcrect ? &*srcrect : nullptr, dstrect ? &*dstrect : nullptr, angle, center ? &*center : nullptr, static_cast<SDL_RendererFlip>(flip)) != 0)
			throw cw::platform::generic::detail::sdl_exception("SDL_RenderCopyEx");
	}

 	void set_draw_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
		if (SDL_SetRenderDrawColor(renderer_, r, g, b, a) != 0)
			throw cw::platform::generic::detail::sdl_exception("SDL_SetRenderDrawColor");
	}

	void set_target() {
		if (SDL_SetRenderTarget(renderer_, nullptr) != 0)
			throw cw::platform::generic::detail::sdl_exception("SDL_SetRenderTarget");

	}

	void set_target(texture& texture) {
		if (SDL_SetRenderTarget(renderer_, texture.Get()) != 0)
			throw cw::platform::generic::detail::sdl_exception("SDL_SetRenderTarget");
	}

	void set_draw_blend_mode(SDL_BlendMode blendMode) {
		if (SDL_SetRenderDrawBlendMode(renderer_, blendMode) != 0)
			throw cw::platform::generic::detail::sdl_exception("SDL_SetRenderDrawBlendMode");
	}

	void draw_point(int x, int y) {
		if (SDL_RenderDrawPoint(renderer_, x, y) != 0)
			throw cw::platform::generic::detail::sdl_exception("SDL_RenderDrawPoint");
	}

	void draw_point(const point<int>& p) {
		draw_point(p.x, p.y);
	}

	void draw_points(const point<int>* points, int count) {
		std::vector<SDL_Point> sdl_points;
		sdl_points.reserve(count);
		for (const Point* p = points; p != points + count; ++p)
			sdl_points.emplace_back(*p);

		if (SDL_RenderDrawPoints(renderer_, sdl_points.data(), sdl_points.size()) != 0)
			throw cw::platform::generic::detail::sdl_exception("SDL_RenderDrawPoints");
	}


	void draw_line(const point<int>& p1, const point<int>& p2) {
		DrawLine(p1.x, p1.y, p2.x, p2.y);
	}

	void draw_lines(const point<int>* points, int count) {
		std::vector<SDL_Point> sdl_points;
		sdl_points.reserve(count);
		for (const Point* p = points; p != points + count; ++p)
			sdl_points.emplace_back(*p);

		if (SDL_RenderDrawLines(renderer_, sdl_points.data(), sdl_points.size()) != 0)
			throw cw::platform::generic::detail::sdl_exception("SDL_RenderDrawLines");
	}

	void draw_rectangle(const rectangle<int>& r) {
		if (SDL_RenderDrawRect(renderer_, &r) != 0)
			throw cw::platform::generic::detail::sdl_exception("SDL_RenderDrawRect");
	}

	void draw_rectangles(const rectangle<int>* rects, int count) {
		std::vector<SDL_Rect> sdl_rects;
		sdl_rects.reserve(count);
		for (const Rect* r = rects; r != rects + count; ++r)
			sdl_rects.emplace_back(*r);

		if (SDL_RenderDrawRects(renderer_, sdl_rects.data(), sdl_rects.size()) != 0)
			throw cw::platform::generic::detail::sdl_exception("SDL_RenderDrawRects");
	}

	void fill_rectangle(const rectangle<int>& r) {
		if (SDL_RenderFillRect(renderer_, &r) != 0)
			throw cw::platform::generic::detail::sdl_exception("SDL_RenderFillRect");
	}

	void fill_rectangles(const rectangle<int>* rects, int count) {
		std::vector<SDL_Rect> sdl_rects;
		sdl_rects.reserve(count);
		for (const Rect* r = rects; r != rects + count; ++r)
			sdl_rects.emplace_back(*r);

		if (SDL_RenderFillRects(renderer_, sdl_rects.data(), sdl_rects.size()) != 0)
			throw cw::platform::generic::detail::sdl_exception("SDL_RenderFillRects");
	}

	void read_pixels(const rectangle<int>& rect, Uint32 format, void* pixels, int pitch) {
		if (SDL_RenderReadPixels(renderer_, rect ? &*rect : nullptr, format, pixels, pitch) != 0)
			throw Exception("SDL_RenderReadPixels");
	}

	void set_clip_rectangle(const rectangle<int>& rect) {
		if (SDL_RenderSetClipRect(renderer_, rect ? &*rect : nullptr) != 0)
			throw cw::platform::generic::detail::sdl_exception("SDL_RenderSetClipRect");
	}

	Renderer& Renderer::SetLogicalSize(int w, int h) {
		if (SDL_RenderSetLogicalSize(renderer_, w, h) != 0)
			throw cw::platform::generic::detail::sdl_exception("SDL_RenderSetLogicalSize");
		return *this;
	}

	void set_scale(float scaleX, float scaleY) {
		if (SDL_RenderSetScale(renderer_, scaleX, scaleY) != 0)
			throw cw::platform::generic::detail::sdl_exception("SDL_RenderSetScale");
	}

	void set_viewport(const rectangle<int>& rect) {
		if (SDL_RenderSetViewport(renderer_, rect ? &*rect : nullptr) != 0)
			throw cw::platform::generic::detail::sdl_exception("SDL_RenderSetViewport");
	}

	bool target_supported() const {
		return SDL_RenderTargetSupported(renderer_) == SDL_TRUE;
	}

	rectangle<int> get_clip_rect() const {
		SDL_Rect rect;
		SDL_RenderGetClipRect(renderer_, &rect);
		return rect;
	}

	point<int> get_logical_size() const {
		int w, h;
		SDL_RenderGetLogicalSize(renderer_, &w, &h);
		return Point(w, h);
	}

	int get_logical_width() const {
		int w;
		SDL_RenderGetLogicalSize(renderer_, &w, nullptr);
		return w;
	}

	int get_logical_height() const {
		int h;
		SDL_RenderGetLogicalSize(renderer_, nullptr, &h);
		return h;
	}

	void get_scale(float& scalex, float& scaley) const {
		SDL_RenderGetScale(renderer_, &scalex, &scaley);
	}

	float get_x_scale() const {
		float scalex;
		SDL_RenderGetScale(renderer_, &scalex, nullptr);
		return scalex;
	}

	float get_y_scale() const {
		float scaley;
		SDL_RenderGetScale(renderer_, nullptr, &scaley);
		return scaley;
	}

	rectangle<int> get_viewport() const {
		SDL_Rect rect;
		SDL_RenderGetViewport(renderer_, &rect);
		return rect;
	}

	SDL_BlendMode get_draw_blend_mode() const {
		SDL_BlendMode mode;
		if (SDL_GetRenderDrawBlendMode(renderer_, &mode) != 0)
			throw cw::platform::generic::detail::sdl_exception("SDL_GetRenderDrawBlendMode");
		return mode;
	}

};// class renderer
