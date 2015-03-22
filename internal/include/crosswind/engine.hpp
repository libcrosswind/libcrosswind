#pragma once

#include <map>
#include <memory>
#include <string>

#include <glm/glm.hpp>

#include <crosswind/implementation/platform/application.hpp>
#include <crosswind/implementation/platform/filesystem.hpp>
#include <crosswind/implementation/platform/input.hpp>
#include <crosswind/implementation/graphical/video.hpp>
#include <crosswind/implementation/sound/mixer.hpp>
#include <crosswind/implementation/simulation/physics.hpp>

namespace cw{
    
    class engine;
    struct settings;

}// namespace cw

struct cw::settings{


    struct{

        int flags;

    } application;

    struct{

        int frequency;
        uint16_t format;
        int channels;
        int chunk_size;

    } audio;

    struct {

        std::string window_title;
        glm::i32vec2  window_position;
        glm::i32vec2  default_resolution;
        glm::i32vec2  window_resolution;

        int image_flags;
        int window_flags;
        float fps;

    } video;

    struct{

        glm::vec3 gravity;
        glm::vec3 scale;
        glm::vec3 unit_value;

    } physics;

    glm::i32vec4  audio_settings;

    settings(){
        application.flags        = SDL_INIT_VIDEO | SDL_INIT_AUDIO;

        audio.frequency          = 44100;
        audio.format             = MIX_DEFAULT_FORMAT;
        audio.channels           = 2;
        audio.chunk_size         = 2048;

        video.window_title       = "Main";
        video.window_position    = glm::i32vec2(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        video.default_resolution = glm::i32vec2(320, 224);
        video.window_resolution  = glm::i32vec2(640, 480);
        video.image_flags        = IMG_INIT_PNG;
        video.window_flags       = SDL_WINDOW_OPENGL;
        video.fps                = 60.0f;

        auto world_scale =
                glm::vec3(video.window_resolution[0] / video.default_resolution[0],
                          video.window_resolution[1] / video.default_resolution[1], 1.0);

        physics.gravity         = glm::vec3(0.0f, -10.0f, 0.0f);
        physics.scale           = glm::vec3(0.01f, 0.01f, 0.01f);
        physics.unit_value      = glm::vec3(1.0f * world_scale[0], 1.0f * world_scale[1], 1.0f * world_scale[2]);

    }

};// struct settings


class cw::engine{
public:
	engine(settings engine_settings = settings()){
        application = std::make_shared<implementation::platform::application>(engine_settings.application.flags);
        filesystem  = std::make_shared<implementation::platform::filesystem>();

        input       = std::make_shared<implementation::platform::input>();
        video       = std::make_shared<implementation::graphical::video>(engine_settings.video.window_title,
                                                                         engine_settings.video.window_position,
                                                                         engine_settings.video.window_resolution,
                                                                         engine_settings.video.fps,
                                                                         engine_settings.video.image_flags,
                                                                         engine_settings.video.window_flags);

        mixer       = std::make_shared<implementation::sound::mixer>(engine_settings.audio.frequency,
                                                                     engine_settings.audio.format,
                                                                     engine_settings.audio.channels,
                                                                     engine_settings.audio.chunk_size);

        physics     = std::make_shared<implementation::simulation::physics>(engine_settings.physics.gravity,
                                                                            engine_settings.physics.scale,
                                                                            engine_settings.physics.unit_value);

/*
            //We wil treat centimeters as pixels where 1 millimeter = 3.78 pixels

            std::vector<glm::vec3> physics_settings{
                    glm::vec3(0.0f, -10.0f, 0.0f),// gravity
                    glm::vec3(0.01f, 0.01f, 0.01f),// scale
                    glm::vec3(1.0f * world_scale[0], 1.0f * world_scale[1], 1.0f * world_scale[2])    // unit value
            };// 1 pixel represents 0.00026458 meters. We set this property to ensure correct graphical calculations.

*/
	}

	void run(){

   		application->start();

        while (application->alive()) {

            video->window->begin_frame();

            update();
            render();

            float fps = video->window->end_frame();


        }

//        stages["current"]->deinit(engine);
	}

private:
    void add_stage(auto stage){
/*        stage->setup(engine);
        stage->init(engine);
        engine->physics->init_debug_drawer(stage->get_camera("main_camera"));
        stages[stage->name] = stage;*/
    }

    void swap_stage(const std::string& previous_stage, const std::string& new_stage){
//        stages[previous_stage] = stages[new_stage];
    }


private:
    void update(){
        application->update();
        input->update();
//        stages["current"]->update();
    	physics->update(1/60.0);
//        stages["current"]->update(1/60.0/*video->window->fps_limiter->get_delta()*/);
    }

    void render(){
        video->window->clear();
//        stages["current"]->render();
        physics->debug_draw_world();
        video->window->present();
    }

public:
    std::shared_ptr< interface::platform::application > application;
    std::shared_ptr< interface::platform::filesystem  > filesystem;
    std::shared_ptr< interface::platform::input       >	input;
    std::shared_ptr< interface::graphical::video 	  >	video;
    std::shared_ptr< interface::sound::mixer          > mixer;
    std::shared_ptr< interface::simulation::physics   >	physics;


//    std::shared_ptr<  backend::interface::simulation::loader 	>	loader;

    

private:
//    std::map<std::string, std::shared_ptr<simulation::stage> > stages;


};// class engine