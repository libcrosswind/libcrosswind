#pragma once
#include <memory>
#include "glm/glm.hpp"
#include "crosswind/composition/core.hpp"
#include "crosswind/composition/scene.hpp"
#include "crosswind/composition/camera.hpp"

#include "characters/title/sega_logo.hpp"
#include "characters/title/team_logo.hpp"
#include "characters/title/title_background.hpp"

namespace game{
    namespace scenes{
        class title;
    }// namespace zones
}// namespace game

class game::scenes::title : public cw::composition::scene{
public:
    title(): scene("title"){
    }
    virtual void init(){
 
        /*add_actor("title_background", title_background);
        for(auto& actor: actors){
            actor.second->init();
        }*/
        //reset();
    }
    virtual void deinit(){
    }
    
    
    void draw_title(){
       
    }
    virtual void logic(const float& delta){
        time_count += delta;
        switch(phase){
            case scene_phase::sega_logo:
//draw_sega_logo();
// break;
            case scene_phase::team_logo:
//draw_team_logo();
// break;
            case scene_phase::title_logo:
                draw_title();
                break;
        }
    }
private:
    float time_count;
    bool sega_sound_ongoing;
    bool title_sound_ongoing;
    float sega_logo_duration;
    float team_logo_duration;
    float intro_duration;
    int phase;
    enum scene_phase{
        sega_logo = 0,
        team_logo,
        title_logo
    };
};// class title