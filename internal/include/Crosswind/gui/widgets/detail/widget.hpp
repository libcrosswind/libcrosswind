#pragma once

#include <string> 
#include <thread> 
#include <atomic> 

#include <Crosswind/input/input_listener.hpp>
#include <Crosswind/graphics/object_xyz.hpp>
#include <Crosswind/graphics/texture.hpp>
#include <Crosswind/private/flag_set.hpp>

namespace cw{




	class widget: public input_listener, public virtual object_xyz{
        
    public:
        class init_flags{
        public:
            init_flags(){

                method = [](){
                    return [](int test_flags){
                        return false;
                    };

                }();

            }

            template<typename T>
            void set(T flag_pack){

                method = [&flag_pack](){
                    std::shared_ptr<flag_set<T> > flags(new flag_set<T>(flag_pack));

                    return [flags](int test_flags){
                        return flags->test((T)test_flags);
                    };

                }();
            }

            bool has(int flag_pack){
                return method(flag_pack);
            }

        protected:
            std::function<bool(int)> method;
        };

        widget(){
            set_depth(1.0);
            switch_texture("blank", std::shared_ptr<texture>(new texture(get_width(), get_height(), get_depth(), 4)));
            on_dimension_set += [this]{
                std::lock_guard<std::mutex> lock(texture_mutex);
                for(auto& texture : textures){
                    texture.second->resize(this->get_width(), this->get_height());
                }

            };
        }

        virtual void init(std::shared_ptr<init_flags> flags = nullptr) = 0;
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

        std::shared_ptr<texture> get_texture(std::string name){
            std::shared_ptr<texture> texture;

            texture_mutex.lock();
            texture = textures[name];
            texture_mutex.unlock();

            return texture;
        }

    protected:
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