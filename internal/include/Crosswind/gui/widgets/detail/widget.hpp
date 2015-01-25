#pragma once

#include <Crosswind/graphics/object_xyz.hpp>


namespace cw{
	
	class widget: public object_xyz{

			virtual void init(FlagSet<InitFlags> flags = FlagSet<InitFlags>()) = 0;
            virtual void show() = 0;
            virtual void hide() = 0;
            virtual void update(double delta) = 0;
            virtual void render(std::shared_ptr<texture> render_texture) = 0;
            virtual void loop() = 0;

            void set_text(std::string text){

        		text_mutex.lock();
        		text_string = text;
        		text_mutex.unlock();

            }

            std::string get_text(){
            	std::string text = "";

            	text_mutex.lock();
            	text = text_string;
            	text_mutex.unlock();

            	return text;
            }


            void set_theme(std::string theme){

        		theme_mutex.lock();
        		theme_string = theme;
        		theme_mutex.unlock();

            }

            std::string get_theme(){
            	std::string theme = "";

            	theme_mutex.lock();
            	theme = theme_string;
            	theme_mutex.unlock();

            	return theme;
            }


        private:
        	std::mutex text_mutex;
        	std::string text_string;

        	std::mutex theme_mutex;
        	std::string theme_string;


    };

}