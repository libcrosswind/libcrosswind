
#include <iostream>
/*
#include <crosswind/core/concurrent/atomical_property.hpp>
#include <crosswind/core/concurrent/mutexed_property.hpp>
#include <crosswind/core/concurrent/mutexed_container.hpp>
#include <crosswind/core/container/cacheable.hpp>
#include <crosswind/core/javascript/json.hpp>

#include <crosswind/core/crypto/base64.hpp>
#include <crosswind/core/crypto/sha1.hpp>

#include <crosswind/standard/geometry/rectangle.hpp>
#include <crosswind/platform/generic/application.hpp>

#include <crosswind/platform/generic/filesystem.hpp>
#include <crosswind/platform/gui/components/widget.hpp>*/

#include <crosswind/standard/simulation/actor.hpp>

#include <type_traits>
#include <SDL.h>

/*
 * Get the resource path for resources located in res/subDir
 * It's assumed the project directory is structured like:
 * bin/
 *  the executable
 * res/
 *  Lesson1/
 *  Lesson2/
 *
 * Paths returned will be Lessons/res/subDir
 */
std::string getResourcePath(const std::string &subDir = ""){
    //We need to choose the path separator properly based on which
    //platform we're running on, since Windows uses a different
    //separator than most systems
#ifdef _WIN32
    const char PATH_SEP = '\\';
#else
	const char PATH_SEP = '/';
#endif
    //This will hold the base resource path: Lessons/res/
    //We give it static lifetime so that we'll only need to call
    //SDL_GetBasePath once to get the executable path
    static std::string baseRes;
    if (baseRes.empty()){
        //SDL_GetBasePath will return NULL if something went wrong in retrieving the path
        char *basePath = SDL_GetBasePath();
        if (basePath){
            baseRes = basePath;
            SDL_free(basePath);
        }
        else {
            std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
            return "";
        }
        //We replace the last bin/ with res/ to get the the resource path
        size_t pos = baseRes.rfind("bin");
        baseRes = baseRes.substr(0, pos) + "res" + PATH_SEP;
    }
    //If we want a specific subdirectory path in the resource directory
    //append it to the base path. This would be something like Lessons/res/Lesson0
    return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
}

int main(int argc, char **argv) {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
        return 1;
    }
    std::cout << "Resource path is: " << getResourcePath() << std::endl;

    SDL_Quit();
    return 0;

    cw::standard::simulation::actor actor1;
    cw::standard::simulation::actor actor2;
    cw::standard::simulation::actor* actor3 = new cw::standard::simulation::renderable_actor();
    cw::standard::simulation::actor* actor4 = new cw::standard::simulation::logic_actor();

    // true
    dynamic_cast<cw::standard::simulation::renderable_actor*>(actor3) ?
            std::cout << "Cast ok " <<std::endl :
            std::cout << "Cast not ok " << std::endl;

    dynamic_cast<cw::standard::simulation::renderable_actor*>(actor4) ?
            std::cout << "Cast ok " <<std::endl :
            std::cout << "Cast not ok " <<std::endl;

/*
    cw::core::concurrent::atomical_property<bool> the_bool;
    cw::core::concurrent::mutexed_property<std::string> the_string;
    cw::core::concurrent::mutexed_container<std::map<std::string, std::string> > the_map;
    cw::core::container::cacheable<bool> cache;
    cw::core::javascript::json json;

    cw::standard::geometry::rectangle<double> rect1(0, 0, 10, 10);
    cw::standard::geometry::rectangle<double> rect2(0, 0, 5, 10);

    the_map("K", "R");


    the_bool = true;
    bool boolean;
    boolean = the_bool;

    std::string str;
    str = the_map("K");
    std::cout << str <<std::endl;

    cache.store("boolean", false);

    cache.add_manipulation("true_manipulation", [](auto& map){
        for(auto& item : map){
            item.second = true;
        }
    });

    cache.apply_manipulation("true_manipulation");

    std::cout<< cache.load("boolean") << std::endl;

    cache.add_manipulation("false_manipulation", [](auto& map){
        for(auto& item: map){
            item.second = false;
        }
    });

    cache.apply_manipulation("false_manipulation");

    std::cout<< cache.load("boolean") << std::endl;

    std::string encoded = cw::core::crypto::base64::encode("THE STRING");
    std::string decoded = cw::core::crypto::base64::decode(encoded);

    std::cout<< encoded << std::endl;
    std::cout<< decoded << std::endl;

    std::cout<< "SHA1:" << cw::core::crypto::sha1::compress(decoded) << std::endl;


    std::string json_string = "{\"value\":1}";

    json.from_string(json_string);

    {
        auto &raw_json = json.data.acquire();

        std::cout << raw_json["value"] << std::endl;

        json.data.release();
    }
    std::cout << rect1.contains_xy(2.0, 5.0) << std::endl;

    std::cout << rect1.contains(rect2) << std::endl;


    cw::platform::generic::application application;
    cw::platform::generic::filesystem::add_directory("assets", true);
    cw::platform::generic::filesystem::add_directory("tests/gui", true);

    if(cw::platform::generic::filesystem::exists("data.json")){
        json.from_file(cw::platform::generic::filesystem::get_file_path("data.json"));

        auto& raw_json = json.data.acquire();
        std::cout << raw_json["compact"] << std::endl;
        std::cout << raw_json["schema"] << std::endl;
        json.data.release();

    }



    application.title = std::string("The window");
    application.run();

*/

/*
    auto button      = cw::widget_pool::create(0.1, 0.2, 0.4, 0.3, "blue");
*/
    return 0;

}