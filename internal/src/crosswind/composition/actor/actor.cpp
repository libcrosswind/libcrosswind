#include <memory>
#include <string>
#include <stdexcept>

#include "glm/glm.hpp"

#include "crosswind/composition/actor/actor.hpp"
#include "crosswind/composition/core.hpp"
#include "crosswind/platform/filesystem.hpp"
#include "crosswind/graphical/video.hpp"
#include "crosswind/graphical/object/model.hpp"
#include "crosswind/graphical/object/text.hpp"
#include "crosswind/graphical/object/sprite.hpp"
#include "crosswind/graphical/object/sprite_animation.hpp"
#include "crosswind/simulation/physics.hpp"
#include "crosswind/simulation/detail/character.hpp"
#include "crosswind/simulation/detail/body.hpp"

cw::composition::actor::actor(const std::string& c_name): named_component(c_name){

}

cw::composition::actor::~actor(){

}