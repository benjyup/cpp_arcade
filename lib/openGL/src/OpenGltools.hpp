//
// Created by florian on 4/5/17.
//

#ifndef CPP_ARCADE_OPENGLTOOLS_HPP
#define CPP_ARCADE_OPENGLTOOLS_HPP


#include <IObserve.hpp>
#include <SDL2/SDL.h>

namespace arcade {

    class OpenGltools {
    public:
        OpenGltools(void);
        ~OpenGltools(void);

        arcade::IEvenement::KeyCode getKey(SDL_Keycode) const;
        void                        _initKeys(void);

    private:
        std::vector <std::pair<SDL_Keycode, arcade::IEvenement::KeyCode>> _Keys;
    };
}

#endif //CPP_ARCADE_OPENGLTOOLS_HPP
