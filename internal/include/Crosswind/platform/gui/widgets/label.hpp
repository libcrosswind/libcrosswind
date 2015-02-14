#pragma once 


namespace cw{
    class label: public widget{

    public:
        label(){

            //TODO move mouse implementations to widget class and create textures for on, off, visible, hidden textures.
            //TODO add transparent mask to rendering texture.
            set_text_color(128, 128, 128);

        }


    };
}