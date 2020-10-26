#include "crosswind/graphical/object/sprite.hpp"
#include "crosswind/graphical/object/vertex.hpp"

cw::graphical::object::sprite::sprite(const glm::vec3& c_origin,
                                      const glm::vec3& c_size,
                                      const glm::vec4& c_color,
                                      const glm::vec4& c_uv,
                                      const uint32_t& c_id): 
mesh(c_origin, c_size),
texture_id(c_id){

    this->color = c_color;
    this->uv = c_uv;

    auto px = c_origin.x - c_size.x/2.0f;
    auto py = c_origin.y - c_size.y/2.0f;
    auto pz = c_origin.z - c_size.z/2.0f;
    auto pw = 1.0f;

    auto dx = c_size.x;
    auto dy = c_size.y;
    auto dz = c_size.z;

    vertex top_right(glm::vec4(px + dx, py + dy, pz, pw), c_color, glm::vec2(0.0f, 0.0f));
    vertex top_left(glm::vec4(px, py + dy, pz, pw), c_color, glm::vec2(0.0f));
    vertex bottom_right(glm::vec4(px + dx, py, pz, pw), c_color, glm::vec2(0.0f));
    vertex bottom_left(glm::vec4(px, py, pz, pw), c_color, glm::vec2(0.0f));

    vertices = {
        // First triangle
        top_right,
        top_left,
        bottom_left,
        //Second triangle
        bottom_left,
        bottom_right,
        top_right
    };

    // first triangle
    vertices[0].set_uv(c_uv.z, c_uv.w); // top right
    vertices[1].set_uv(c_uv.x, c_uv.w); // top left
    vertices[2].set_uv(c_uv.x, c_uv.y); // bottom left

    // second triangle
    vertices[3].set_uv(c_uv.x, c_uv.y); // bottom left
    vertices[4].set_uv(c_uv.z, c_uv.y); // bottom right
    vertices[5].set_uv(c_uv.z, c_uv.w); // top right

    set_origin(origin);

    xFlipped = false;
}

glm::vec4 cw::graphical::object::sprite::get_color() {
    return this->color;
}

glm::vec4 cw::graphical::object::sprite::get_uv() {
    return this->uv;
}
void cw::graphical::object::sprite::set_origin(const glm::vec3& new_origin){
    origin = new_origin;

    auto px = new_origin.x - size.x/2.0f;
    auto py = new_origin.y - size.y/2.0f;
    auto pz = new_origin.z - size.z/2.0f;
    auto pw = 1.0f;

    auto dx = size.x;
    auto dy = size.y;
    auto dz = size.z;

    glm::vec4 top_right (px + dx, py + dy, pz, pw);
    glm::vec4 top_left(px, py + dy, pz, pw);
    glm::vec4 bottom_right(px + dx, py, pz, pw);
    glm::vec4 bottom_left(px, py, pz, pw);

    vertices[0].set_position(top_right);
    vertices[1].set_position(top_left);
    vertices[2].set_position(bottom_left);

    vertices[3].set_position(bottom_left);
    vertices[4].set_position(bottom_right);
    vertices[5].set_position(top_right);


    /*vertices[0].set_position(bottom_left);
    vertices[1].set_position(bottom_right);
    vertices[2].set_position(top_right);

    vertices[3].set_position(top_right);
    vertices[4].set_position(top_left);
    vertices[5].set_position(bottom_left);*/
}

void cw::graphical::object::sprite::set_size(const glm::vec3& new_size){

    size = new_size;

    set_origin(get_origin());

}


void cw::graphical::object::sprite::h_flip() {

    xFlipped = !xFlipped;
    auto tr = vertices[0];  // top right
    auto tl = vertices[1];  // top left

    auto br = vertices[4];  // bottom right
    auto bl = vertices[3];  // bottom left


    vertices[0] = tl;       // flip
    vertices[1] = tr;       // flip
    vertices[5] = tl;       // flip


    vertices[2] = br;       // flip
    vertices[3] = br;       // flip
    vertices[4] = bl;       // flip
}

bool cw::graphical::object::sprite::get_h_flip() {
    return xFlipped;
}

void cw::graphical::object::sprite::v_flip() {
    vFlipped = !vFlipped;

    /*auto px = origin.x - size.x / 2.0f;
    auto py = origin.y - size.y / 2.0f;
    auto pz = origin.z - size.z / 2.0f;
    auto pw = 1.0f;

    auto dx = size.x;
    auto dy = size.y;
    auto dz = size.z;

    glm::vec4 top_right(px + dx, py + dy, pz, pw);
    glm::vec4 top_left(px, py + dy, pz, pw);
    glm::vec4 bottom_right(px + dx, py, pz, pw);
    glm::vec4 bottom_left(px, py, pz, pw);*/

    auto tr = vertices[0];  // top right
    auto tl = vertices[1];  // top left

    auto br = vertices[4];  // bottom right
    auto bl = vertices[3];  // bottom left


    vertices[0] = bl;
    vertices[1] = br;
    vertices[2] = tr;

    vertices[3] = tr;
    vertices[4] = tl;
    vertices[5] = bl;    
}

bool cw::graphical::object::sprite::get_v_flip() {
    return vFlipped;
}