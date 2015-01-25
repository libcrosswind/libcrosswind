#pragma once

#include <string> 
#include <thread> 
#include <atomic> 

#include <Crosswind/input/input_listener.hpp>
#include <Crosswind/graphics/object_xyz.hpp>
#include <Crosswind/graphics/texture.hpp>
#include <Crosswind/private/flagset.hpp>

namespace cw{
	


	class widget: public input_listener, public object_xyz{
        
    public:
        enum InitFlags{
            IN_NEW_THREAD = 1 << 0
        };

        virtual void init(FlagSet<InitFlags> flags = FlagSet<InitFlags>()) = 0;
        virtual void show() = 0;
        virtual void hide() = 0;

        virtual void update(double delta) = 0;
        virtual void render(std::shared_ptr<texture> render_texture) = 0;
        virtual void loop() = 0;

public:
        void set_text(std::string text){

            std::lock_guard<std::mutex> lock(text_mutex);
        	text_string = text;

        }

        std::string get_text(){
        	std::string text = "";

        	text_mutex.lock();
        	text = text_string;
        	text_mutex.unlock();

        	return text;
        }


        void set_theme(std::string theme){

            std::lock_guard<std::mutex> lock(theme_mutex);
        	theme_string = theme;

        }

        std::string get_theme(){
        	std::string theme = "";

        	theme_mutex.lock();
        	theme = theme_string;
        	theme_mutex.unlock();

        	return theme;
        }

        void set_draggable(bool drag){
            draggable.store(drag);
        }

        bool get_draggable(){
            return draggable.load();
        }

        void switch_texture(std::string name, std::shared_ptr<texture> new_texture){
            std::lock_guard<std::mutex> lock(texture_mutex);
            textures[name] = new_texture;
        }

    protected:
        FlagSet<InitFlags> init_flags;
        std::thread widget_thread;

        std::mutex texture_mutex;
        std::map<std::string, std::shared_ptr<texture> > textures;
    
    private:    
        std::mutex text_mutex;
        std::string text_string;

        std::mutex theme_mutex;
        std::string theme_string;

        std::atomic<bool> draggable;


    };

}