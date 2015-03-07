#pragma once

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SDL2/SDL_image.h>

namespace cw{
namespace simulation{
namespace gl{

	class gl_texture;

}// namespace gl
}// namespace simulation
}// namespace cw

class cw::simulation::gl::gl_texture{
public:
	gl_texture(const glm::vec2& size, unsigned char bpp, void* pixels): id(0){

        glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

        int mode = GL_RGB;

        if(bpp == 4) {
            mode = GL_RGBA;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, mode, size.x, size.y, 0, mode, GL_UNSIGNED_BYTE, pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
    }

	uint32_t id;
};