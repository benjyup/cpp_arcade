//
// Created by florian on 4/5/17.
//

#include "OpenGltools.hpp"

arcade::OpenGltools::OpenGltools() {
    _initKeys();
}

arcade::OpenGltools::~OpenGltools() { }

arcade::IEvenement::KeyCode arcade::OpenGltools::getKey(SDL_Keycode key) const
{
    arcade::IEvenement::KeyCode key_u= arcade::IEvenement::KeyCode::Key_Undefined;

    for (auto it : _Keys)
        if (key == it.first)
            return (it.second);
    return (key_u);
}

void 				arcade::OpenGltools::_initKeys(void)
{
    _Keys.push_back(std::make_pair(SDLK_UP, arcade::IEvenement::KeyCode::Key_UP));
    _Keys.push_back(std::make_pair(SDLK_LEFT, arcade::IEvenement::KeyCode::Key_LEFT));
    _Keys.push_back(std::make_pair(SDLK_RIGHT, arcade::IEvenement::KeyCode::Key_RIGHT));
    _Keys.push_back(std::make_pair(SDLK_DOWN, arcade::IEvenement::KeyCode::Key_DOWN));
    _Keys.push_back(std::make_pair(SDLK_a, arcade::IEvenement::KeyCode::Key_A));
    _Keys.push_back(std::make_pair(SDLK_d, arcade::IEvenement::KeyCode::Key_D));
    _Keys.push_back(std::make_pair(SDLK_q, arcade::IEvenement::KeyCode::Key_Q));
    _Keys.push_back(std::make_pair(SDLK_s, arcade::IEvenement::KeyCode::Key_S));
    _Keys.push_back(std::make_pair(SDLK_z, arcade::IEvenement::KeyCode::Key_Z));
    for (auto it : _Keys)
        if (it.first == 0 || it.first == -1)
            throw std::runtime_error("Not able to init the keypad.");
}