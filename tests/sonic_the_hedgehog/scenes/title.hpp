#pragma once
#include <memory>
#include <glm/glm.hpp>
#include <crosswind/interface/core.hpp>
#include <crosswind/interface/composition/scene.hpp>
#include <crosswind/implementation/composition/camera.hpp>
#include <characters/title/sega_logo.hpp>
#include <characters/title/team_logo.hpp>
#include <characters/title/title_background.hpp>
namespace game{
    namespace scenes{
        class title;
    }// namespace zones
}// namespace game
class game::scenes::title : public cw::interface::composition::scene{
public:
    title(){
    }
    virtual void init(){
 
        add_actor("title_background", title_background);
        for(auto& actor: actors){
            actor.second->init();
        }
        reset();
    }
    virtual void deinit(){
    }
    
    
    void draw_title(){
        if(time_count <= 1.0f) {
            this->get_actor("title_background")->get_model("title_sonic")->change_animation("title_sonic_a");
            this->get_actor("title_background")->get_model("title_logo_a")->set_origin(glm::vec3(0.0f, 0.0f, 0.0f));
            this->get_actor("title_background")->get_model("title_sonic")->set_origin(glm::vec3(-2000.0f, -41.0f, 0.0f));
            this->get_actor("title_background")->get_model("title_logo_b")->set_origin(glm::vec3(0.0f, 0.0f, 0.0f));
            float alpha_blending = glm::sin(glm::radians(time_count / 1.0f * 90.0f));
            this->get_actor("title_background")->set_alpha(alpha_blending);
        } else if(time_count >= 1.0f && time_count <= 2.0f){
        } else if(time_count >= 2.0f && time_count <= 2.5f ) {
            const float sonic_y = this->get_actor("title_background")->get_model("title_sonic")->get_origin().y;
            const float movement_time = 4.05f; //3.0f - (4.0f - time_count);
            const float movement = glm::clamp(sonic_y + movement_time, -41.0f, 82.0f);
            this->get_actor("title_background")->get_model("title_sonic")->set_origin(glm::vec3(0.0f, movement, 0.0f));
        } else if(time_count >= 2.5f && time_count <= 9.0f) {
            if(time_count - 3.0f < 0.9f){
                this->get_actor("title_background")->get_model("title_sonic")->change_animation("title_sonic_b");
            } else {
                this->get_actor("title_background")->get_model("title_sonic")->change_animation("title_sonic_c");
            }
            const float sonic_x = this->get_actor("title_background")->get_model("title_sonic")->get_origin().x +
                                  2.2;
            this->get_actor("title_background")->get_model("title_logo_a")->set_origin(glm::vec3(sonic_x, 0.0f, 0.0f));
            this->get_actor("title_background")->get_model("title_sonic")->set_origin(glm::vec3(sonic_x, 82.0f, 0.0f));
            this->get_actor("title_background")->get_model("title_logo_b")->set_origin(glm::vec3(sonic_x, 0.0f, 0.0f));
        } else if(time_count >= 9.0f && time_count <= 10.0f){
            this->get_actor("title_background")->get_model("title_sonic")->change_animation("title_sonic_d");
            const float time_range = 2.0f - (10.0f - time_count);
            float alpha_blending = glm::sin(glm::radians((time_range/2 * 90.0f) + 90.0f));
            get_actor("title_background")->set_alpha(alpha_blending);
            core->video->window->set_clear_color(glm::vec4(alpha_blending, alpha_blending, alpha_blending, 1.0f));
        } else if(time_count >= 10.0f && time_count <= 12.0f){
        } else{
            time_count = 0.0f;
            reset();
        }
        if(!title_sound_ongoing && time_count >= 1.0f) {
            title_sound_ongoing = true;
            core->mixer->play_music("title_bgm", 0);
        }
        if(time_count >= 3.0f){
            const float sonic_x = this->get_actor("title_background")->get_model("title_sonic")->get_origin().x;
            get_camera("main_camera")->set_position(glm::vec3(sonic_x, 0.0f, 0.0f));
        }
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