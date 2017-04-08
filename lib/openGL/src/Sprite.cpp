//
// Created by florian on 4/7/17.
//

#include "Sprite.hpp"

arcade::Sprite::Sprite(const std::string &name,
                               const std::string & filename)
        : Object(name, filename)
{
    this->setTextureFile(filename);
    _pos.x = this->_position.getX();
    _pos.y = this->_position.getY();
    _pos.w = 20;
    _pos.h = 20;
    this->updateVisual(0);
}

arcade::Sprite::~Sprite()
{}

void                            arcade::Sprite::moveSprite(void)
{
    float                         x = (this->_position.getX() * arcade::Window::SQUARE) - this->_pos.x;
    float                         y = (this->_position.getY() * arcade::Window::SQUARE) - this->_pos.y;
    float                         add;

    if (x == 0 && y == 0)
        return;
    if (x != 0)
    {
        add = this->_speed * (NEG_OR(x) * arcade::Window::SQUARE / 60);
        if (NEG_OR(add) * add > NEG_OR(x) * x)
            x = this->_position.getX() * arcade::Window::SQUARE;
        else
            x = this->_pos.x + add;
    }
    else
        x = this->_pos.x;
    if (y != 0)
    {
        add = this->_speed * (NEG_OR(y) * arcade::Window::SQUARE / 60);
        if (NEG_OR(add) * add > NEG_OR(y) * y)
            y = this->_position.getY() * arcade::Window::SQUARE;
        else
            y = this->_pos.y + add;
    }
    else
        y = this->_pos.y;
    this->_pos.x = x;
    this->_pos.y = y;
}

void                            arcade::Sprite::updateVisual(uint32_t state)
{
    uint32_t orientation = 0;

    this->moveSprite();
    if (this->getDirection().getX() > 0)
        orientation = 3;
    else
    if (this->getDirection().getX() < 0)
        orientation = 2;
    else
    if (this->getDirection().getY() < 0)
        orientation = 0;
    else
    if (this->getDirection().getY() > 0)
        orientation = 1;
    state = (state % (_mWidth / 100));
    this->_sprite.x = state * 100;
    this->_sprite.y = orientation * 100;
    this->_sprite.h = 100;
    this->_sprite.w = 100;
/*
    this->_sprite.setScale(static_cast<float>(arcade::WindowSFML::SQUARE / 100.0 * this->getScale()),
                           static_cast<float>(arcade::WindowSFML::SQUARE / 100.0 * this->getScale()));
*/
}

bool                    arcade::Sprite::isTextureOk(void) const
{
    return (this->_texture != NULL);
}

bool            arcade::Sprite::isMoving(void) const {
         return (!(this->_pos.x == (this->getPosition().getX() * arcade::Window::SQUARE) &&
                  this->_pos.y == (this->getPosition().getY() * arcade::Window::SQUARE)));
}

bool        arcade::Sprite::loadTexture(const std::string &path){
    SDL_Surface *loadedSurface = IMG_Load((path + ".png").c_str());

    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    } else {
//Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
//Create texture from surface pixels
            _mWidth = loadedSurface->w;
            _mHeight = loadedSurface->h;
    }
    _texture = loadedSurface;
    //Return success(
    return (_texture != NULL);
}

void                                arcade::Sprite::setTextureFile(std::string const &filename) {
       loadTexture(filename);
}

SDL_Rect &                          arcade::Sprite::getSprite(void)  {
    return (_sprite);
}

SDL_Surface        *arcade::Sprite::getSurface(void) {
    return (_texture);
}

SDL_Rect &arcade::Sprite::getSpritePos(void) {
    return (_pos);
}

arcade::Object::ObjectType arcade::Sprite::getType() const { return (ObjectType::Object); }