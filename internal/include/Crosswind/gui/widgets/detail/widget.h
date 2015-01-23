#pragma once 

#include <CImg/CImg.h>

#include <functional>
#include <memory>
#include <algorithm>
#include <vector>
#include <string>

#include <Crosswind/logic/detail/logicModule.h>
#include <Crosswind/graphics/pointXYZ.h>
#include <Crosswind/events/delegate.h>

#include <Crosswind/system/settings.h>
namespace cw {

    class widget{


public:
        virtual void load(std::string filename, int w, int h, int x, int y, int z) = 0;

public:
        widget(){
        }
        

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

        cimg_library::CImg<unsigned char>& getSprite(){ return data; }

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
        cimg_library::CImg<unsigned char> data;
        std::shared_ptr<pointXYZ> position;
        int width, height;

        std::vector<std::shared_ptr<logicModule> > logicModules;

    };

}
