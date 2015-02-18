#pragma once 

#include <string>
#include <utility>

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_blendmode.h>

#include <crosswind/platform/generic/sdl_exception.hpp>
#include <crosswind/standard/geometry/rectangle.hpp>



namespace cw{
namespace standard{
namespace drawing{

	class texture;

}// namespace drawing
}// namespace standard
}// namespace cw


class cw::standard::drawing::texture{
public: 
	class lock_handle;

public:
	texture(SDL_Texture* texture) : texture_(texture) {
	}

	texture(Renderer& renderer, Uint32 format, int access, int w, int h) {
		if ((texture_ = SDL_CreateTexture(renderer.Get(), format, access, w, h)) == nullptr)
			throw sdl_exception("SDL_CreateTexture");
	}

	texture(Renderer& renderer, const Surface& surface) {
		if ((texture_ = SDL_CreateTextureFromSurface(renderer.Get(), surface.Get())) == nullptr)
			throw sdl_exception("SDL_CreateTextureFromSurface");
	}

	~texture() {
		if (texture_ != nullptr)
			SDL_DestroyTexture(texture_);
	}

	texture(texture&& other) noexcept : texture_(other.texture_) {
		other.texture_ = nullptr;
	}

	texture& operator=(texture&& other) noexcept {
		if (&other == this)
			return *this;
		if (texture_ != nullptr)
			SDL_DestroyTexture(texture_);
		texture_ = other.texture_;
		other.texture_ = nullptr;
		return *this;
	}

	SDL_Texture* get() const {
		return texture_;
	}

	template<typename T>
	texture& update(const rectangle<T>& rect, const void* pixels, int pitch) {
		if (SDL_UpdateTexture(texture_, rect ? &*rect : nullptr, pixels, pitch) != 0)
			throw sdl_exception("SDL_UpdateTexture");
		return *this;
	}

	template<typename T>
	texture& update_yuv(const rectangle<T>& rect, const Uint8* yplane, int ypitch, const Uint8* uplane, int upitch, const Uint8* vplane, int vpitch) {
		if (SDL_UpdateYUVTexture(texture_, rect ? &*rect : nullptr, yplane, ypitch, uplane, upitch, vplane, vpitch) != 0)
			throw sdl_exception("SDL_UpdateYUVTexture");
		return *this;
	}

	texture& set_blend_mode(SDL_BlendMode blendMode) {
		if (SDL_SetTextureBlendMode(texture_, blendMode) != 0)
			throw sdl_exception("SDL_SetTextureBlendMode");
		return *this;
	}

	texture& Texture::SetAlphaMod(Uint8 alpha) {
		if (SDL_SetTextureAlphaMod(texture_, alpha) != 0)
			throw sdl_exception("SDL_SetTextureAlphaMod");
		return *this;
	}

	texture& set_color_mod(Uint8 r, Uint8 g, Uint8 b) {
		if (SDL_SetTextureColorMod(texture_, r, g, b) != 0)
			throw sdl_exception("SDL_SetTextureColorMod");
		return *this;
	}

	template<typename T>
	lock_handle lock(const rectangle<T>& rect) {
		return lock_handle(this, rect);
	}

	Uint32 get_format() const {
		Uint32 format;
		if (SDL_QueryTexture(texture_, &format, nullptr, nullptr, nullptr) != 0)
			throw sdl_exception("SDL_QueryTexture");
		return format;
	}

	int get_access() const {
		int access;
		if (SDL_QueryTexture(texture_, nullptr, &access, nullptr, nullptr) != 0)
			throw sdl_exception("SDL_QueryTexture");
		return access;
	}

	int get_width() const {
		int w;
		if (SDL_QueryTexture(texture_, nullptr, nullptr, &w, nullptr) != 0)
			throw sdl_exception("SDL_QueryTexture");
		return w;
	}

	int get_height() const {
		int h;
		if (SDL_QueryTexture(texture_, nullptr, nullptr, nullptr, &h) != 0)
			throw sdl_exception("SDL_QueryTexture");
		return h;
	}

	point get_size() const {
		int w, h;
		if (SDL_QueryTexture(texture_, nullptr, nullptr, &w, &h) != 0)
			throw sdl_exception("SDL_QueryTexture");
		return point(w, h);
	}

	Uint8 get_alpha_mod() const {
		Uint8 alpha;
		if (SDL_GetTextureAlphaMod(texture_, &alpha) != 0)
			throw sdl_exception("SDL_GetTextureAlphaMod");
		return alpha;
	}

	SDL_BlendMode get_blend_mode() const {
		SDL_BlendMode mode;
		if (SDL_GetTextureBlendMode(texture_, &mode) != 0)
			throw sdl_exception("SDL_GetTextureBlendMode");
		return mode;
	}

	void get_color_mod(Uint8& r, Uint8& g, Uint8& b) const {
		if (SDL_GetTextureColorMod(texture_, &r, &g, &b) != 0)
			throw sdl_exception("SDL_GetTextureColorMod");
	}

private:
	SDL_Texture* texture_; 

};


class cw::standard::drawing::texture::lock_handle {
		friend class texture;
private:
		Texture* texture_; 
		void* pixels_;   
		int pitch_;      

private:
	template<typename T>
	lock_handle(texture* texture, const rectangle<T>& rect) : texture_(texture) {
		if (SDL_LockTexture(texture_->Get(), rect ? &*rect : nullptr, &pixels_, &pitch_) != 0)
			throw sdl_exception("SDL_LockTexture");
	}


public:
	lock_handle() : texture_(nullptr), pixels_(nullptr), pitch_(0) {
	}

	lock_handle(lock_handle&& other) noexcept : texture_(other.texture_), pixels_(other.pixels_), pitch_(other.pitch_) {
		other.texture_ = nullptr;
		other.pixels_ = nullptr;
		other.pitch_ = 0;
	}

	lock_handle& operator=(lock_handle&& other) noexcept {
		if (&other == this)
			return *this;

		if (texture_ != nullptr)
			SDL_UnlockTexture(texture_->Get());

		texture_ = other.texture_;
		pixels_ = other.pixels_;
		pitch_ = other.pitch_;

		other.texture_ = nullptr;
		other.pixels_ = nullptr;
		other.pitch_ = 0;

		return *this;
	}

	~lock_handle() {
		if (texture_ != nullptr)
			SDL_UnlockTexture(texture_->Get());
	}

	void* get_pixels() const {
		return pixels_;
	}

	int get_pitch() const {
		return pitch_;
	}
};