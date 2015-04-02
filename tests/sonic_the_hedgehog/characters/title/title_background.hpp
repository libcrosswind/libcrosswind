#pragma once

#include <glm/glm.hpp>

#include <crosswind/interface/core.hpp>
#include <crosswind/interface/composition/actor.hpp>

namespace game {
namespace characters {
namespace title{

	class title_background;

}// namespace title
}// namespace characters
}// namespace game

class game::characters::title::title_background: public cw::interface::composition::actor{
public:

	title_background(){

	}

	virtual void init(){

		auto window_size = core->video->window->get_size();

		this->add_model("gh_background_1",
		                glm::vec3(0.0f, 0.0f, 0.0f),
		                glm::vec3(-100.0f * 640.0f/320.0f, -100.0f*480.0f/224.0f, 0.0f),
		                "gh_background.json");

		this->add_model("gh_background_water_1",
		                glm::vec3(0.0f, 0.0f, 0.0f),
		                glm::vec3(-100.0f * 640.0f/320.0f, -100.0f*480.0f/224.0f, 0.0f),
		                "gh_background_water.json");

		this->add_model("gh_background_2",
		                glm::vec3(0.0f, 0.0f, 0.0f),
		                glm::vec3(-100.0f * 640.0f/320.0f, -100.0f*480.0f/224.0f, 0.0f),
		                "gh_background.json");

		this->add_model("gh_background_water_2",
		                glm::vec3(0.0f, 0.0f, 0.0f),
		                glm::vec3(-100.0f * 640.0f/320.0f, -100.0f*480.0f/224.0f, 0.0f),
		                "gh_background_water.json");

		this->add_model("gh_background_3",
		                glm::vec3(0.0f, 0.0f, 0.0f),
		                glm::vec3(-100.0f * 640.0f/320.0f, -100.0f*480.0f/224.0f, 0.0f),
		                "gh_background.json");

		this->add_model("gh_background_water_3",
		                glm::vec3(0.0f, 0.0f, 0.0f),
		                glm::vec3(-100.0f * 640.0f/320.0f, -100.0f*480.0f/224.0f, 0.0f),
		                "gh_background_water.json");

		float a_origin = window_size.x / 2.0f - get_model("gh_background_1")->get_size().x / 2.0f;

		get_model("gh_background_1")->set_origin(glm::vec3(-a_origin, 0.0f, 0.0f));
		get_model("gh_background_water_1")->set_origin(glm::vec3(-a_origin, 0.0f, 0.0f));

		float b_origin = get_model("gh_background_1")->get_origin().x +
				         get_model("gh_background_1")->get_size().x / 2.0f +
				         get_model("gh_background_2")->get_size().x / 2.0f;

		get_model("gh_background_2")->set_origin(glm::vec3(b_origin, 0.0f, 0.0f));
		get_model("gh_background_water_2")->set_origin(glm::vec3(b_origin, 0.0f, 0.0f));
		get_model("gh_background_2")->change_animation("waterfal_b");

		float c_origin = get_model("gh_background_2")->get_origin().x +
		                 get_model("gh_background_2")->get_size().x / 2.0f +
		                 get_model("gh_background_3")->get_size().x / 2.0f;

		get_model("gh_background_3")->set_origin(glm::vec3(c_origin, 0.0f, 0.0f));
		get_model("gh_background_water_3")->set_origin(glm::vec3(c_origin, 0.0f, 0.0f));
		get_model("gh_background_3")->change_animation("waterfal_c");


		this->add_model("title_logo_a",
		                glm::vec3(0.0f, 0.0f, 0.0f),
		                glm::vec3(-100.0f * 640.0f/320.0f, -100.0f*480.0f/224.0f, 0.0f),
		                "title_logo_a.json");

		this->add_model("title_sonic",
		                glm::vec3(0.0f, 0.0f, 0.0f),
		                glm::vec3(-100.0f * 640.0f/320.0f, -100.0f*480.0f/224.0f, 0.0f),
		                "title_sonic.json");

		this->add_model("title_logo_b",
		                glm::vec3(0.0f, 0.0f, 0.0f),
		                glm::vec3(-100.0f * 640.0f/320.0f, -100.0f*480.0f/224.0f, 0.0f),
		                "title_logo_b.json");

	}


	virtual void deinit(){

	}

	virtual void logic(const float& delta){

	}

};