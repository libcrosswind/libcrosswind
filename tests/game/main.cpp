
#include <Crosswind/gui/window.h>
#include <Crosswind/gui/widget.h>

#include <Crosswind/logic/movementLogicModule.h>


int main(int argc, char **argv) {

    int width = 640, height = 480;

    std::shared_ptr<cw::window> win(new cw::window(width, height, "Game_test"));
    std::shared_ptr<cw::widget> ball(new cw::widget("ball.png", 10, 10, width/2, 2, 0));
    std::shared_ptr<cw::widget> paddle(new cw::widget("paddle.png", 100, 10, 0, 0, 0));

    paddle->setX(width/2 - paddle->getWidth()/2);
    paddle->setY(height - paddle->getHeight() - 10);

    std::shared_ptr<cw::movementLogicModule> ballMovement
            (new cw::movementLogicModule(cw::movementLogicModule::movementLogic::X | cw::movementLogicModule::movementLogic::Y));

    ballMovement->position = ball->getPosition();
    ballMovement->logic = [paddle, ball, win, ballMovement](){

        if(ball->collidesY(win->getHeight()))
            win->close(); //This is game over.

        if(ball->collidesX(win->getWidth()) || ball->collidesX(0))
            ballMovement->movement.flip(cw::movementLogicModule::movementLogic::X);

            if(ball->collidesY(0) || ball->collidesY(paddle->getY()))
                ballMovement->movement.flip(cw::movementLogicModule::movementLogic::Y);

            ballMovement->movement.test(cw::movementLogicModule::movementLogic::X) ?
                    ballMovement->position->x++ :
                    ballMovement->position->x--;

            ballMovement->movement.test(cw::movementLogicModule::movementLogic::Y) ?
                    ballMovement->position->y++ :
                    ballMovement->position->y-- ;
    };

    ball->attachLogic(ballMovement);

    paddle->on_mouse_move = [paddle, win](int x, int y){
        if(x!=-1 && !paddle->collidesX(win->getWidth())) paddle->setX(x); //TODO create with statement.
    };


    win->attach(ball);
    win->attach(paddle);

    win->on_closed = [&](){

    };

    win->show();

    return 0;

}