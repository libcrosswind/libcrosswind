#pragma once

#include <string>

namespace cw{
	class settings{
	public:
        class ui{
        public:
            /*static std::string themePath(std::string theme){
                return path + "/" + theme;
            }

            static std::string elementPath( std::string theme,
                                            std::string element,
                                            bool is_actionable  = true){

                return is_actionable ?
                        themePath(theme)+ "/" + element + "/" + theme + "_" + element :
                        themePath(theme)+ "/" + element + "/" + theme + "_" + element + "." + graphics::textureFormat ;

            }

            static std::string getActionString( std::string theme, //TODO create action inteface for hover and such.
                                                std::string element,
                                                bool actionated = true ){

                return actionated ?
                        elementPath(theme, element, true) + "_" + "on"  + "." + graphics::textureFormat:
                        elementPath(theme, element, true) + "_" + "off" + "." + graphics::textureFormat;
            }
            */
        };

	};	
}
