#include <vector>

#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_blendmode.h>

namespace cw{
namespace platform{
namespace sdl{

	class surface;

}// namespace sdl
}// namespace platform
}// namespace cw

class cw::platform::sdl::surface {
public:
	class lock_handle;

public:
	surface(SDL_Surface* surface_ptr) : surface_(surface_ptr) {
	}

	surface(Uint32 flags, int width, int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) {
		if ((surface_ = SDL_CreateRGBSurface(flags, width, height, depth, Rmask, Gmask, Bmask, Amask)) == nullptr)
			throw sdl_exception("SDL_CreateRGBSurface");
	}

	surface(void* pixels, int width, int height, int depth, int pitch, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) {
		if ((surface_ = SDL_CreateRGBSurfaceFrom(pixels, width, height, depth, pitch, Rmask, Gmask, Bmask, Amask)) == nullptr)
			throw sdl_exception("SDL_CreateRGBSurfaceFrom");
	}

	
	~surface() {
		if (surface_ != nullptr)
			SDL_FreeSurface(surface_);
	}

	surface(surface&& other) noexcept : surface_(other.surface_) {
		other.surface_ = nullptr;
	}

	surface& operator=(surface&& other) noexcept {
		if (&other == this)
			return *this;
		if (surface_ != nullptr)
			SDL_FreeSurface(surface_);
		surface_ = other.surface_;
		other.surface_ = nullptr;
		return *this;
	}

	SDL_Surface* get() const {
		return surface_;
	}

	surface convert(const SDL_PixelFormat& format) {
		SDL_Surface* surface = SDL_ConvertSurface(surface_, &format, 0);
		if (surface == nullptr)
			throw sdl_exception("SDL_ConvertSurface");
		return surface;
	}

	surface convert(Uint32 pixel_format) {
		SDL_Surface* surface = SDL_ConvertSurfaceFormat(surface_, pixel_format, 0);
		if (surface == nullptr)
			throw sdl_exception("SDL_ConvertSurfaceFormat");
		return surface;
	}

	template<typename T>
	void blit(const rectangle<T>& srcrect, surface& dst, const rectangle<T>& dstrect) {
		SDL_Rect tmpdstrect = dstrect; // 4th argument is non-const; does it modify rect?
		if (SDL_BlitSurface(surface_, srcrect ? &*srcrect : nullptr, dst.get(), &tmpdstrect) != 0)
			throw sdl_exception("SDL_BlitSurface");
	}

	template<typename T>
	void blit_scaled(const rectangle<T>& srcrect, surface& dst, const rectangle<T>& dstrect) {
		SDL_Rect tmpdstrect; // 4th argument is non-const; does it modify rect?
		if (dstrect)
			tmpdstrect = *dstrect;
		if (SDL_BlitScaled(surface_, srcrect ? &*srcrect : nullptr, dst.get(), dstrect ? &tmpdstrect : nullptr) != 0)
			throw sdl_exception("SDL_BlitScaled");
	}

	lock_handle lock() {
		return lock_handle(this);
	}

	template<typename T>
	rectangle<T> get_clip_rectangle() const {
		SDL_Rect rect;
		SDL_GetClipRect(surface_, &rect);
		return rectangle<T>(rect);
	}

	Uint32 get_color_key() const {
		Uint32 key;
		if (SDL_GetColorKey(surface_, &key) != 0)
			throw sdl_exception("SDL_GetColorKey");
		return key;
	}

	Uint8 get_alpha_mod() const {
		Uint8 alpha;
		if (SDL_GetSurfaceAlphaMod(surface_, &alpha) != 0)
			throw sdl_exception("SDL_GetSurfaceAlphaMod");
		return alpha;
	}

	SDL_BlendMode get_blend_mode() const {
		SDL_BlendMode blendMode;
		if (SDL_GetSurfaceBlendMode(surface_, &blendMode) != 0)
			throw sdl_exception("SDL_GetSurfaceBlendMode");
		return blendMode;
	}

	void get_color_mod(Uint8& r, Uint8& g, Uint8& b) const {
		if (SDL_GetSurfaceColorMod(surface_, &r, &g, &b) != 0)
			throw sdl_exception("SDL_GetSurfaceColorMod");
	}

	surface& set_clip_rectangle(const Optional<Rect>& rect) {
		if (SDL_SetClipRect(surface_, rect ? &*rect : nullptr) != 0)
			throw sdl_exception("SDL_SetClipRect");
		return *this;
	}

	surface& set_color_key(bool flag, Uint32 key) {
		if (SDL_SetColorKey(surface_, flag, key) != 0)
			throw sdl_exception("SDL_SetColorKey");
		return *this;
	}

	surface& set_alpha_mod(Uint8 alpha) {
		if (SDL_SetSurfaceAlphaMod(surface_, alpha) != 0)
			throw sdl_exception("SDL_SetSurfaceAlphaMod");
		return *this;
	}

	surface& set_blend_mode(SDL_BlendMode blendMode) {
		if (SDL_SetSurfaceBlendMode(surface_, blendMode) != 0)
			throw sdl_exception("SDL_SetSurfaceBlendMode");
		return *this;
	}

	surface& set_color_mod(Uint8 r, Uint8 g, Uint8 b) {
		if (SDL_SetSurfaceColorMod(surface_, r, g, b) != 0)
			throw sdl_exception("SDL_SetSurfaceColorMod");
		return *this;
	}

	surface& set_rle(bool flag) {
		if (SDL_SetSurfaceRLE(surface_, flag ? 1 : 0) != 0)
			throw sdl_exception("SDL_SetSurfaceRLE");
		return *this;
	}

	template<typename T>
	surface& fill_rect(const rectangle<T>& rect, Uint32 color) {
		if (SDL_FillRect(surface_, rect ? &*rect : nullptr, color) != 0)
			throw sdl_exception("SDL_FillRect");
		return *this;
	}

	surface& fill_rects(const Rect* rects, int count, Uint32 color) {
		std::vector<SDL_Rect> sdl_rects;
		sdl_rects.reserve(count);
		for (const Rect* r = rects; r != rects + count; ++r)
			sdl_rects.emplace_back(*r);

		if (SDL_FillRects(surface_, sdl_rects.data(), sdl_rects.size(), color) != 0)
			throw sdl_exception("SDL_FillRects");
		return *this;
	}

	int get_width() const {
		return surface_->w;
	}

	int get_height() const {
		return surface_->h;
	}

	template<typename T>
	point<T> get_size() const {
		return point<T>(surface_->w, surface_->h);
	}


private:
	SDL_Surface* surface_;

};



class cw::drawing::surface::lock_handle{
		friend class surface;
private:
	surface* surface_;  

public:


	lock_handle() : surface_(nullptr) {
	}

	lock_handle(surface* surface_ptr) : surface_(surface_ptr) {
		if (SDL_MUSTLOCK(surface_->Get())) {
			if (SDL_LockSurface(surface_->Get()))
				throw sdl_exception("SDL_LockSurface");
		}
	}

	lock_handle(lock_handle&& other) noexcept : surface_(other.surface_) {
		other.surface_ = nullptr;
	}

	lock_handle& operator=(lock_handle&& other) noexcept {
		if (&other == this)
			return *this;

		if (surface_ != nullptr) {
			if (SDL_MUSTLOCK(surface_->Get()))
				SDL_UnlockSurface(surface_->Get());
		}

		surface_ = other.surface_;

		other.surface_ = nullptr;

		return *this;
	}

	~lock_handle() {
		if (surface_ != nullptr) {
			if (SDL_MUSTLOCK(surface_->Get()))
				SDL_UnlockSurface(surface_->Get());
		}
	}

	void* get_pixels() const {
		return surface_->Get()->pixels;
	}

	int get_pitch() const {
		return surface_->Get()->pitch;
	}

	const SDL_PixelFormat& get_format() const {
		return *surface_->Get()->format;
	}

};

