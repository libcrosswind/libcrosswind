#pragma once

#include <memory>

#include <glm/glm.hpp>

#include <crosswind/interface/core.hpp>
#include <crosswind/interface/composition/actor.hpp>

namespace game{
namespace characters{
	
	class sonic;

}// namespace characters
}// namespace game

class game::characters::sonic: public cw::interface::composition::actor{
public:
	sonic(){

	}

	virtual void init(){

		this->add_model("sonic", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(40.0f, 42.0f, 0.0f), "sonic.json");
		this->add_character("sonic", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(26, 24), 0.35f);

		this->conditions["moving"] = false;
		this->conditions["braking"] = false;
		this->conditions["rolling"] = false;
		this->conditions["jumping"] = false;
		this->set_facing(true);

	}

	virtual void deinit(){

	}

	void set_facing(const bool& f_facing){
		facing = f_facing;
	}

	bool get_facing(){
		return facing;
	}

	void calculate_jumping(){

	    if(core->input->is_key_down("k")){
		    if(this->get_character("sonic")->on_ground()) {
			    this->get_character("sonic")->jump();
			    this->conditions["rolling"] = false;

			    this->get_model("sonic")->change_animation("roll_1", get_facing());
			    core->mixer->play_effect("jump");
		    }
	    }

	}

	void calculate_ground_animations(){
		if(this->get_character("sonic")->on_ground()) {

			    if(this->get_character("sonic")->get_speed().x > 0){
				    this->set_facing(true);
			    } else if(this->get_character("sonic")->get_speed().x < 0){
				    this->set_facing(false);
			    }

			    if(core->input->is_key_down("Down")){
				    if(glm::abs(this->get_character("sonic")->get_speed().x) >= 0.53125f){
					    if(!this->conditions["rolling"]){
						    this->get_model("sonic")->change_animation("roll_1", this->get_facing());
						    core->mixer->play_effect("spin");
						    this->conditions["rolling"] = true;
						    this->conditions["braking"] = false;
					    }
				    }
			    }

			    if(core->input->is_key_down("Left") != core->input->is_key_down("Right")){

				    if(glm::abs(this->get_character("sonic")->get_speed().x) >= 6.0f){

					    if(!this->conditions["rolling"] &&
							    !this->conditions["braking"]){

						    this->get_model("sonic")->change_animation("run", this->get_facing());

					    }

				    } else {
					    if(!this->conditions["rolling"] &&
							    !this->conditions["braking"]){
						    this->get_model("sonic")->change_animation("walk", this->get_facing());
					    }
				    }

				    if(glm::abs(this->get_character("sonic")->get_speed().x) >= 4.5f){
					    bool should_brake = false;

					    if(this->get_facing() && core->input->is_key_down("Left")){
						    should_brake = true;
					    } else if(!this->get_facing() && core->input->is_key_down("Right")){
						    should_brake = true;
					    }

					    if(should_brake && !this->conditions["braking"] && !this->conditions["rolling"]){
						    this->get_model("sonic")->change_animation("stop", this->get_facing());
						    core->mixer->play_effect("stop");
						    this->conditions["braking"] = true;
					    }

				    }

				    if(this->conditions["braking"]){
					    if(core->input->is_key_down("Left") && this->get_character("sonic")->get_speed().x <= 0.0f){
						    this->conditions["braking"] = false;
					    } else if(core->input->is_key_down("Right") && this->get_character("sonic")->get_speed().x >= 0.0f){
						    this->conditions["braking"] = false;
					    }
				    }

				    if(this->conditions["rolling"]){
					    if(this->get_facing() && this->get_character("sonic")->get_speed().x <= 0.0f){
						    this->conditions["rolling"] = false;
					    } else if(!this->get_facing() && this->get_character("sonic")->get_speed().x >= 0.0f){
						    this->conditions["rolling"] = false;
					    }
				    }
			    }
			    if(this->get_character("sonic")->get_speed().x == 0) {
				    this->conditions["rolling"] = false;
				    this->conditions["braking"] = false;

				    if(core->input->is_key_down("Up")) {
					    this->get_model("sonic")->change_animation("look_up", this->get_facing());
				    } else if(core->input->is_key_down("Down")){
					    this->get_model("sonic")->change_animation("duck", this->get_facing());
				    } else {
					    this->get_model("sonic")->change_animation("stand", this->get_facing());
				    }

			    }

			    float frame_duration = glm::max(8.0f - glm::abs(this->get_character("sonic")->get_speed().x), 3.0f);
			    frame_duration *= 1.0f / 60.0f; // 1 second / 60 frames;

				this->get_model("sonic")->get_animations()["walk"]->duration =
					    frame_duration * this->get_model("sonic")->get_animations()["walk"]->frames.size();

				this->get_model("sonic")->get_animations()["run"]->duration =
					    frame_duration * this->get_model("sonic")->get_animations()["run"]->frames.size();

			    frame_duration = glm::max(8.0f - glm::abs(this->get_character("sonic")->get_speed().x), 1.0f);
			    frame_duration *= 1.0f / 60.0f;

				this->get_model("sonic")->get_animations()["roll_1"]->duration =
					    frame_duration * this->get_model("sonic")->get_animations()["roll_1"]->frames.size();
		    }
	}

	void calculate_movement() {

	    if (core->input->is_key_down("Right") != core->input->is_key_down("Left")) {
		    float acc = 0.046875;
		    float dec = 0.0f;

		    if (this->conditions["rolling"]) {
			    dec = 0.125;
		    } else {
			    dec = 0.5f;
		    }

		    auto spd = this->get_character("sonic")->get_speed();
		    if (core->input->is_key_down("Left")) {
			    acc *= -1.0f;
			    dec *= -1.0f;
		    }
		    if (this->conditions["braking"]) {
			    spd.x += dec;
		    } else if (this->conditions["rolling"]) {
			    if (this->get_facing() && core->input->is_key_down("Left") ||
					    !this->get_facing() && core->input->is_key_down("Right")) {
				    spd.x += dec;
			    }
			    if (glm::abs(spd.x) > 16.0f) {
				    spd.x = 16.0f * glm::sign(spd.x);
			    }
		    } else {
			    if (this->get_facing() && core->input->is_key_down("Left") ||
					    !this->get_facing() && core->input->is_key_down("Right")) {
				    spd.x += dec;
			    } else {
				    spd.x += acc;
			    }
			    if (glm::abs(spd.x) > 6.0f) {
				    spd.x = 6.0f * glm::sign(spd.x);
			    }
		    }
		    this->get_character("sonic")->set_speed(spd);
	    }
	}

	void calculate_friction(){

		if(core->input->is_key_down("Left") == core->input->is_key_down("Right") ||	this->conditions["rolling"]){

			    auto spd = this->get_character("sonic")->get_speed();
			    float frc = 0.046875f;

			    if(this->conditions["rolling"]){
				    frc = 0.0234375f;
			    }
			    if(spd.x > 0.0f){
				    spd.x += frc * -1.0f;
				    if(spd.x < 0.0f ){
					    spd.x = 0.0f;
				    }
			    } else {
				    spd.x += frc;
				    if(spd.x > 0.0f ){
					    spd.x = 0.0f;
				    }
			    }
			    this->get_character("sonic")->set_speed(spd);
	    }

	}

	void map_positions(){

			glm::vec3 b_origin(this->get_character("sonic")->get_origin().x,
					this->get_character("sonic")->get_origin().y,
					this->get_character("sonic")->get_origin().z);

			this->get_model("sonic")->get_render_sprite_list()["current"]->set_origin(b_origin);

	}

	virtual void logic(const float& dt){
		calculate_movement();
		calculate_friction();
		calculate_jumping();
		map_positions();
		calculate_ground_animations();

	}

private:
	bool facing;

//	model_map models;
//	std::shared_ptr<core> core;

};