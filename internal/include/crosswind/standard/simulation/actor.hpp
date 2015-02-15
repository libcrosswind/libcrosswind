#pragma once

#include <cassert>
#include <vector>

#include <crosswind/core/concurrent/atomical_property.hpp>
#include <crosswind/core/concurrent/mutexed_property.hpp>

#include <crosswind/core/functional/delegate.hpp>

namespace cw{
namespace standard{
namespace simulation{

    class actor;

}
}
}

class cw::standard::simulation::actor{

public:
    actor(){

    }


    //Adds child, if desired, at a given index.
    void add(actor& child, bool indexed = false, unsigned int index = 0)
    {

        assert(this != &child);// Cannot add actor to itself
        assert(!child.is_root);// Cannot add root actor

        bool proceed = true;
        if(!indexed)
            this != child.parent ? proceed = true : proceed = false;

        if(proceed)
            attach(child, indexed, index);
        
    }

    void attach(actor& child, bool insert = false, unsigned int index = 0){
        
        actor* const previous_parent(child.parent);

        // if this actor already have parent, unparent it first
        if(previous_parent){
            previous_parent->remove(child); // This causes on_child_remove callback
        }

        // Guard against add() during previous on_child_remove callback
        if (!child.parent){
            auto& container = children.acquire();
            // This first, since to callbacks from within set_parent() may remove child
            if (index < container.size() && insert){
                auto it = container.begin();
                std::advance(it, index);
                container.insert(it, &child);
            } else {
                container.push_back(&child);
            }

            children.release();

            // SetParent asserts that child can be added
            child.set_parent(this, index);

            // Notification for derived classes
            on_child_add(child);
        }

    }

    void remove(actor& child){
        assert(this != &child); // Cannot remove actor from itself

        if(child_count() == 0){
            // no children
            return;
        }

        actor* removed = NULL;

        // Find the child in children, and unparent it
        auto& container = children.acquire();

        for(auto iter = container.begin(); iter != container.end(); ++iter){
            if(*iter == &child){
              // Keep handle for OnChildRemove notification
              removed = *iter;

                // This first, since to callbacks from within set_parent() may remove child
              container.erase(iter);
              //std::assert( actor.get_parent() == this );
              child.set_parent( NULL );

              break;
            }
        }

        children.release();

        if (removed){
            // Notification for derived classes
            on_child_remove(child);
        }

    }


    unsigned int child_count() const{
        auto& container = children.acquire();
        unsigned int count = container.size();
        children.release();

        return count;
    }

    core::concurrent::mutexed_property<std::string> name;
    core::concurrent::atomical_property<unsigned int> id;
    core::concurrent::atomical_property<bool> is_root;
    core::concurrent::mutexed_property<std::vector<actor*> > children;

    core::functional::delegate<void, actor&> on_child_add;
    core::functional::delegate<void, actor&> on_child_remove;

private:
    void set_parent(actor* new_parent, int index = -1){
        if(new_parent){
            std::assert(!parent); //Actor cannot have 2 parents

            parent = new_parent;
/*
            if ( Stage::IsInstalled() && // Don't emit signals or send messages during Core destruction
                 parent->OnStage() )
            {
              // Instruct each actor to create a corresponding node in the scene graph
              ConnectToStage( index );
            }*/
        }   else    { // parent being set to NULL
                std::assert(parent != NULL);// Actor should have a parent

                parent = NULL;
                /*
                // Don't emit signals or send messages during Core destruction
                if ( Stage::IsInstalled() && 
                     on_stage() ){

                  std::assert(node != NULL);

                  if(node != NULL){
                    // Disconnect the Node & its children from the scene-graph.
                    DisconnectNodeMessage( mStage->GetUpdateManager(), *mNode );
                  }

                  // Instruct each actor to discard pointers to the scene-graph
                  DisconnectFromStage();
                }*/
            }
    }

    actor* parent;
};

    class renderable_actor: public actor{

    };

  /*  class renderable {

    public:
        virtual void render(std::shared_ptr<texture> render_texture){

            if(textures.load("current")){

                textures.load("current")->draw_text(get_absolute_width()/2 ,
                        get_absolute_height()/2,
                        get_text(),
                        get_text_color());

                textures.load("current")->render_to_target(get_absolute_x(), get_absolute_y(), render_texture);
            }
        }

    };

    class render_bin: public renderable{

        virtual void render(std::shared_ptr<texture> render_texture) override {
            for(auto& element : elements){
                element->render(render_texture);
            }
        }

        void attach(std::shared_ptr<renderable> element){
            elements.push_back(element);
        }

        void detach(std::shared_ptr<renderable> element){
        }

        std::vector<std::shared_ptr<rendereable> > elements; //Attached elements.
    };*/

/*
    class widget{

    public:
        widget(){

           sprite.textures.source += [this](std::string path){

                return texture_pool::loadTexture
                        (path, this->get_width(), this->get_height());

            };

            sprite.textures.store("current", std::shared_ptr<texture>(new texture(get_width(), get_height(), 1.0, 4)));

            on_mouse_down += [this](int x, int y, int button){

                if(!this->pressed()){
                    if(this->transform.contains_xy(x, y)){
                        this->pressed = true;
                        this->switch_texture("current", get_texture("on"));
                    }
                }

            };

            on_mouse_move += [this](int x, int y){

                if(this->pressed.load()){

                    if(this->get_draggable()){
                        this->set_x(x);
                        this->set_y(y);
                    }

                } else {
                    if (this->contains_xy(x, y)) {
                        //this->switch_texture("hover", textures["on"]); //TODO
                    }
                }

            };

            on_mouse_up += [this](int x, int y){

                if (pressed() && this->contains_xy(x, y)) {
                    on_clicked();
                }

                this->pressed = false;
                switch_texture("current", get_texture("off"));

            };

            on_dimension_set += [this](){
                std::lock_guard<std::mutex> lock(texture_mutex);

            };

            std::function<void(std::map<std::string, std::shared_ptr<texture> >)>
                    resize_manipulation = [this](std::map<std::string, std::shared_ptr<texture> > textures){
                                        for(auto& texture : textures){
                                            texture.second->resize(this->get_width(), this->get_height());
                                        }
            };


            on_mouse_down += [this](int x, int y, int button){

                if(!this->pressed()){
                    if(this->contains_xy(x, y)){
                        this->pressed = true;
                    }
                }

            };

            on_mouse_up += [this](int x, int y){

                if (this->pressed() && this->contains_xy(x, y)) {
                    on_clicked();
                }

                this->pressed = false;

            };

            on_mouse_move += [this](int x, int y){

                if(this->pressed.load()){

                    if(this->get_draggable()){
                        this->set_x(x);
                        this->set_y(y);
                    }

                } else {
                    if (this->contains_xy(x, y)) {
                        //this->switch_texture("hover", textures["on"]); //TODO
                    }
                }

            };

            on_mouse_down += [this](int x, int y, int button){

                for(auto& element : elements){
                    element->on_mouse_down(x, y, button);
                }

            };

            on_mouse_move += [this](int x, int y){

                for(auto& element : elements){
                    element->on_mouse_move(x, y);
                }

            };

            on_mouse_up += [this](int x, int y){

                for(auto& element : elements){
                    element->on_mouse_up(x, y);
                }

            };

            on_key_down += [this](int key){

                for(auto& element : elements){
                    element->on_key_down(key);
                }

            };

        }


        virtual void update(double delta){

            for(auto& element : elements){
                element->update(delta);
            }
        }

public:
        //Properties
        atomical_property<bool> draggable;
        atomical_property<bool> pressed;
        mutexed_property<std::string> name;

        detail::text text;
        graphics::sprite sprite;

        input_handler input;

        //Delegates
        delegate<void> on_clicked;

    };
*/

}