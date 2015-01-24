#pragma once 

#include <CImg/CImg.h>

#include <functional>
#include <memory>
#include <algorithm>
#include <vector>
#include <map>
#include <string>

#include <Crosswind/logic/detail/logicModule.h>
#include <Crosswind/graphics/pointXYZ.h>
#include <Crosswind/textures/Texture.hpp>
#include <Crosswind/events/delegate.h>

#include <Crosswind/system/settings.h>
namespace cw {

    class widget{


public:
        virtual void load(std::string filename, int w, int h, int x, int y, int z) = 0;
        virtual void setupActions() = 0;

        //TODO replicate TOP, LEFT, RIGHT, BOTTOM
        template<typename T>
        std::shared_ptr<widget> replicate(int x = 0, int y = 0, int z = 0, bool default_position = true){
            //TODO make positions relative, 0.0 to 1.0, same for offsets
            if(default_position){
                int offset = 2;
                x = this->getX(), y = this->getY()+ offset + this->getHeight(), z = this->getZ();
            }


            std::shared_ptr<T> replica(new T());

            replica->setX(x);
            replica->setY(y);
            replica->setZ(z);
            replica->width = this->width;
            replica->height = this->height;
            //TODO implement replication identifiers for internal and external callbacks.
/*          replica->on_mouse_down = this->on_mouse_down;
            replica->on_mouse_move = this->on_mouse_move;
            replica->on_mouse_up   = this->on_mouse_up;
            replica->on_key_down   = this->on_key_down;
            replica->on_key_up     = this->on_key_up; */
            replica->logicModules  = this->logicModules;
            replica->textures = this->textures;

            return replica;
        }


public:
        widget(){
        }
        
        bool& pressed(){ return ispressed; }
        bool& draggable(){ return isdraggable; }

        int& getWidth() { return width; }
        int& getHeight() { return height; }

        int& getX() { return position->x; }
        int& getY() { return position->y; }
        int& getZ() { return position->z; }

        void setX(int x) { position->x = x; }
        void setY(int y) { position->y = y; }
        void setZ(int z) { position->z = z; }

        bool containsX(int x) { return x >= position->x && x <= width + position->x; }
        bool containsY(int y) { return y >= position->y && y <= height + position->y; }
    //  bool containsZ(int z) { return position->z; } //TODO

        bool containsXY(int x, int y){ return containsX(x) && containsY(y); }
    //  bool containsXYZ(int x, int y, int z){ return containsX(x) && containsY(y) && containsZ(z); } //TODO

        bool collidesX(int x){ return x == position->x || x == position->x + width; }
        bool collidesY(int y){ return y == position->y || y == position->y + width; }
    //    bool collidesZ(int y){ return position->z; } //TODO

        bool collidesXY(int x, int y){ return collidesX(x) && collidesY(y); }
    //  bool collidesXY(int x, int y, int z){ return containsX(x) && containsY(y) && containsZ(z); } //TODO

        bool intersectsX(int x){ return containsX(x) || collidesX(x); }
        bool intersectsY(int y){ return containsY(y) || collidesY(y); }
        bool intersectsXY(int x, int y){ return containsXY(x, y) || collidesXY(x, y); }
//      bool intersectsXYZ(int x, int y, int z){ return containsXYZ(x, y, z) || collidesXYZ(x, y, z); }

        std::shared_ptr<texture> getTexture(const std::string& texture_name){ return textures[texture_name]; }

        //TODO make shared_ptr, create identifiers for internal and external callbacks, for replication.
        delegate<int>       on_mouse_down;
        delegate<>          on_mouse_up;
        delegate<int, int>  on_mouse_move;

        delegate<int> on_key_down;
        delegate<int> on_key_up;

        std::shared_ptr<pointXYZ> getPosition() { return position; }

        void updateLogic(){
            std::for_each(logicModules.begin(), logicModules.end(), [this](std::shared_ptr<logicModule> logic){
                logic->update();
            });
        }

        void attachLogic(std::shared_ptr<logicModule> logic){
            logicModules.push_back(logic);
        }

    protected:
        std::shared_ptr<pointXYZ> position;
        int width, height;

        //TODO make shared_ptr for replication.
        //TODO change to forward_list for performance.
        std::vector<std::shared_ptr<logicModule> > logicModules;

        //TODO create actionElement interface implementing states (Pressed, Released, Dragged, etc).
        //TODO make atomic for multithreading.
        bool ispressed;
        bool isdraggable;
        std::map<std::string, std::shared_ptr<texture> > textures; //TODO make multitexture.

    };
}
