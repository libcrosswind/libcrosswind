#pragma once

#include <functional>


class logicModule{

public:

    void update(){
        if(logic)
            logic();
    };

    std::function<void(void)> logic;
};
