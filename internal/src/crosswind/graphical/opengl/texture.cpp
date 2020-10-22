#include "GL/glew.h"
#include "glm/glm.hpp"

#include "crosswind/graphical/opengl/texture.hpp"

cw::graphical::opengl::texture::texture(const glm::vec2& size, unsigned char bpp, void* pixels): id(0){

    this->size = size;
    glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

    int mode = GL_RGB;

    if(bpp == 4) {
        mode = GL_RGBA;
    }


    glTexImage2D(GL_TEXTURE_2D, 0, mode, size.x, size.y, 0, mode, GL_UNSIGNED_BYTE, pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //This causes texture bleeding for some reason
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 7);

    glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
    
}

cw::graphical::opengl::texture::~texture(){
    glDeleteTextures(1, &id);
}
