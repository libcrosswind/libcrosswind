
#pragma once

#include <Crosswind/logic/detail/logicModule.h>
#include <Crosswind/private/flagset.h>

#include <memory>

class pointXYZ;

namespace cw{

    class movementLogicModule: public logicModule{
    public:
        enum movementLogic
        {
            X   = 1 << 0, // binary 0001
            Y   = 1 << 1, // binary 0010
            Z   = 1 << 2, // binary 0100
        };


        movementLogicModule(int movementType): movement(movementType){

        }

        std::shared_ptr<pointXYZ> position;
        FlagSet<movementLogic> movement;
    };


}

