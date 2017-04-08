//
// Created by florian on 4/6/17.
//

#include "Label.hpp"

namespace arcade {
    Label::Label(const std::string &name, const std::string &filename)
            : Object(name, filename) {
        this->setTextureFile(filename);
        _pos.x = this->_position.getX();
        _pos.y = this->_position.getY();
        this->updateVisual(0);
    }

    Label::~Label() {}

    void                            arcade::Label::updateVisual(uint32_t state) {
        //todo
    }

    void arcade::Label::setTextureFile(std::string const &filename) {
        if ((font = TTF_OpenFont((filename + ".ttf").c_str(), 20)) == NULL)
            std::cout << "Fail to open font file " << filename << "\n";
        //(int) arcade::Window::SQUARE);
    }

    bool                    arcade::Label::isTextureOk(void) const {
        return (this->_texture != NULL);
    }

    bool            arcade::Label::isMoving(void) const {
        return (!(this->_pos.x == (this->getPosition().getX() * arcade::Window::SQUARE) &&
                  this->_pos.y == (this->getPosition().getY() * arcade::Window::SQUARE)));
    }

    void arcade::Label::setString(std::string const &str) {
        this->_string = str;
        SDL_Color   white = {255, 255, 255, 0};
        _texture = TTF_RenderText_Blended(font, str.c_str(), white);
        _mWidth = _texture->w;
        _mHeight = _texture->h;
    }

    SDL_Rect &arcade::Label::getSprite(void) {
        SDL_Rect *Rect = NULL;
        return (*Rect);
    }

    SDL_Surface *arcade::Label::getSurface(void) {
        return (_texture);
    }

    SDL_Rect &arcade::Label::getSpritePos(void) {
        return (_pos);
    }

          Object::ObjectType Label::getType() const { return (ObjectType::Label); }
}
