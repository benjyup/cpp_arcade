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
    //todo
}

void                            arcade::Sprite::updateVisual(uint32_t state)
{
    //todo
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