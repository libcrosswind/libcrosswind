#pragma once

namespace cw{
namespace interface{
namespace platform{
 
    class application;

}// namespace platform
}// namespace interface
}// namespace cw


class cw::interface::platform::application{
public:
    application(): running(false){

    }
    
    virtual ~application(){
    }

public:
    virtual void start(){
        running = true;
    }

    virtual bool alive(){
        return running;
    }

    virtual void exit(){
        running = false;
    }

    virtual void update() = 0;

protected:
    bool running;
    
};// class application
