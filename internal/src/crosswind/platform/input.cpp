#include <cstdint>

#include "SDL2/SDL_keyboard.h"
#include "SDL2/SDL_mouse.h"
#include "SDL2/SDL_events.h"

#include "crosswind/platform/input.hpp"

static const SDL_Keycode SDL_default_keymap[SDL_NUM_SCANCODES] = {
    0, 0, 0, 0,
    'a',
    'b',
    'c',
    'd',
    'e',
    'f',
    'g',
    'h',
    'i',
    'j',
    'k',
    'l',
    'm',
    'n',
    'o',
    'p',
    'q',
    'r',
    's',
    't',
    'u',
    'v',
    'w',
    'x',
    'y',
    'z',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    '0',
    SDLK_RETURN,
    SDLK_ESCAPE,
    SDLK_BACKSPACE,
    SDLK_TAB,
    SDLK_SPACE,
    '-',
    '=',
    '[',
    ']',
    '\\',
    '#',
    ';',
    '\'',
    '`',
    ',',
    '.',
    '/',
    SDLK_CAPSLOCK,
    SDLK_F1,
    SDLK_F2,
    SDLK_F3,
    SDLK_F4,
    SDLK_F5,
    SDLK_F6,
    SDLK_F7,
    SDLK_F8,
    SDLK_F9,
    SDLK_F10,
    SDLK_F11,
    SDLK_F12,
    SDLK_PRINTSCREEN,
    SDLK_SCROLLLOCK,
    SDLK_PAUSE,
    SDLK_INSERT,
    SDLK_HOME,
    SDLK_PAGEUP,
    SDLK_DELETE,
    SDLK_END,
    SDLK_PAGEDOWN,
    SDLK_RIGHT,
    SDLK_LEFT,
    SDLK_DOWN,
    SDLK_UP,
    SDLK_NUMLOCKCLEAR,
    SDLK_KP_DIVIDE,
    SDLK_KP_MULTIPLY,
    SDLK_KP_MINUS,
    SDLK_KP_PLUS,
    SDLK_KP_ENTER,
    SDLK_KP_1,
    SDLK_KP_2,
    SDLK_KP_3,
    SDLK_KP_4,
    SDLK_KP_5,
    SDLK_KP_6,
    SDLK_KP_7,
    SDLK_KP_8,
    SDLK_KP_9,
    SDLK_KP_0,
    SDLK_KP_PERIOD,
    0,
    SDLK_APPLICATION,
    SDLK_POWER,
    SDLK_KP_EQUALS,
    SDLK_F13,
    SDLK_F14,
    SDLK_F15,
    SDLK_F16,
    SDLK_F17,
    SDLK_F18,
    SDLK_F19,
    SDLK_F20,
    SDLK_F21,
    SDLK_F22,
    SDLK_F23,
    SDLK_F24,
    SDLK_EXECUTE,
    SDLK_HELP,
    SDLK_MENU,
    SDLK_SELECT,
    SDLK_STOP,
    SDLK_AGAIN,
    SDLK_UNDO,
    SDLK_CUT,
    SDLK_COPY,
    SDLK_PASTE,
    SDLK_FIND,
    SDLK_MUTE,
    SDLK_VOLUMEUP,
    SDLK_VOLUMEDOWN,
    0, 0, 0,
    SDLK_KP_COMMA,
    SDLK_KP_EQUALSAS400,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    SDLK_ALTERASE,
    SDLK_SYSREQ,
    SDLK_CANCEL,
    SDLK_CLEAR,
    SDLK_PRIOR,
    SDLK_RETURN2,
    SDLK_SEPARATOR,
    SDLK_OUT,
    SDLK_OPER,
    SDLK_CLEARAGAIN,
    SDLK_CRSEL,
    SDLK_EXSEL,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    SDLK_KP_00,
    SDLK_KP_000,
    SDLK_THOUSANDSSEPARATOR,
    SDLK_DECIMALSEPARATOR,
    SDLK_CURRENCYUNIT,
    SDLK_CURRENCYSUBUNIT,
    SDLK_KP_LEFTPAREN,
    SDLK_KP_RIGHTPAREN,
    SDLK_KP_LEFTBRACE,
    SDLK_KP_RIGHTBRACE,
    SDLK_KP_TAB,
    SDLK_KP_BACKSPACE,
    SDLK_KP_A,
    SDLK_KP_B,
    SDLK_KP_C,
    SDLK_KP_D,
    SDLK_KP_E,
    SDLK_KP_F,
    SDLK_KP_XOR,
    SDLK_KP_POWER,
    SDLK_KP_PERCENT,
    SDLK_KP_LESS,
    SDLK_KP_GREATER,
    SDLK_KP_AMPERSAND,
    SDLK_KP_DBLAMPERSAND,
    SDLK_KP_VERTICALBAR,
    SDLK_KP_DBLVERTICALBAR,
    SDLK_KP_COLON,
    SDLK_KP_HASH,
    SDLK_KP_SPACE,
    SDLK_KP_AT,
    SDLK_KP_EXCLAM,
    SDLK_KP_MEMSTORE,
    SDLK_KP_MEMRECALL,
    SDLK_KP_MEMCLEAR,
    SDLK_KP_MEMADD,
    SDLK_KP_MEMSUBTRACT,
    SDLK_KP_MEMMULTIPLY,
    SDLK_KP_MEMDIVIDE,
    SDLK_KP_PLUSMINUS,
    SDLK_KP_CLEAR,
    SDLK_KP_CLEARENTRY,
    SDLK_KP_BINARY,
    SDLK_KP_OCTAL,
    SDLK_KP_DECIMAL,
    SDLK_KP_HEXADECIMAL,
    0, 0,
    SDLK_LCTRL,
    SDLK_LSHIFT,
    SDLK_LALT,
    SDLK_LGUI,
    SDLK_RCTRL,
    SDLK_RSHIFT,
    SDLK_RALT,
    SDLK_RGUI,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    SDLK_MODE,
    SDLK_AUDIONEXT,
    SDLK_AUDIOPREV,
    SDLK_AUDIOSTOP,
    SDLK_AUDIOPLAY,
    SDLK_AUDIOMUTE,
    SDLK_MEDIASELECT,
    SDLK_WWW,
    SDLK_MAIL,
    SDLK_CALCULATOR,
    SDLK_COMPUTER,
    SDLK_AC_SEARCH,
    SDLK_AC_HOME,
    SDLK_AC_BACK,
    SDLK_AC_FORWARD,
    SDLK_AC_STOP,
    SDLK_AC_REFRESH,
    SDLK_AC_BOOKMARKS,
    SDLK_BRIGHTNESSDOWN,
    SDLK_BRIGHTNESSUP,
    SDLK_DISPLAYSWITCH,
    SDLK_KBDILLUMTOGGLE,
    SDLK_KBDILLUMDOWN,
    SDLK_KBDILLUMUP,
    SDLK_EJECT,
    SDLK_SLEEP,
    SDLK_APP1,
    SDLK_APP2,
    SDLK_AUDIOREWIND,
    SDLK_AUDIOFASTFORWARD,
};

/*
// extern declarations
namespace cw{
namespace platform{

#ifdef __cplusplus
extern "C" {
#endif
 
    extern DECLSPEC void SDL_GetDefaultKeymap(SDL_Keycode * keymap);

#ifdef __cplusplus
    }
#endif

}// namespace platform
}// namespace cw

*/
cw::platform::input::input(){

    int array_counter = 0;
    
    int32_t keymap[SDL_NUM_SCANCODES];

    SDL_memcpy(keymap, SDL_default_keymap, sizeof(SDL_default_keymap));

    //const Uint8* state = SDL_GetKeyboardState(NULL);
    while(array_counter < SDL_NUM_SCANCODES){

        std::string key_name = SDL_GetKeyName(keymap[array_counter]);
          if(!key_name.empty())
              key_map[key_name] = false;

        array_counter++;
    }

    key_map["mouse_left"] = false;
    key_map["mouse_middle"] = false;
    key_map["mouse_right"] = false;

    delta_count = 0.0f;
    buffering = false;
    last_key = "";
}

bool cw::platform::input::is_key_down(const std::string& key){

	return key_map[key];

}

glm::vec2 cw::platform::input::get_mouse_coordinates(){

    return mouse_coordinates;

}

void cw::platform::input::add_on_key_down_listener(const std::function<void(const std::string&)>& listener){
    ok_key_down_listeners += listener;
}

/*void cw::platform::input::remove_on_key_down_listener(const std::function<void(const std::string&)>& listener){
    ok_key_down_listeners -= listener;
}*/

void cw::platform::input::on_key_down(const std::string& key){

    if(delta_count <= 0.50f){
        if(!buffering){
            buffering = true;
            ok_key_down_listeners(key);
        }
    } else {
        buffering = false;
    }

    if(buffering){
        if(last_key != key){
            buffering = false;
            delta_count = 0.0f;
        }
    } else {
       ok_key_down_listeners(key);
    }
}

void cw::platform::input::update(const float& delta){

	const uint8_t* state = SDL_GetKeyboardState(NULL);

	for(auto& key : key_map){
		if((key_map[key.first] = state[SDL_GetScancodeFromName(key.first.c_str())]) == true){
            on_key_down(key.first);
        }
	}

    int x, y;

    auto mouse_flags = SDL_GetMouseState(&x, &y);

    key_map["mouse_left"] = mouse_flags & SDL_BUTTON(SDL_BUTTON_LEFT);
    key_map["mouse_middle"] = mouse_flags & SDL_BUTTON(SDL_BUTTON_MIDDLE);
    key_map["mouse_right"] = mouse_flags & SDL_BUTTON(SDL_BUTTON_RIGHT);

    mouse_coordinates.x = x;
    mouse_coordinates.y = y;
}
 