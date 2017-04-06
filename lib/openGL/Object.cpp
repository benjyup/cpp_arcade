//
// Created by florian on 4/5/17.
//

#include "Object.hpp"

namespace arcade {
    const std::string        Object::directory_name = "./resources/";
    const std::string        Object::file_extension = ".openGl";

    Object::Object() : _name(""), _filename(""), _string(""),
                       _position(Vector3d(0, 0)), _direction(Vector3d(0, 0)), _speed(0), _isMoving(true) {}

    Object::Object(const std::string &name, const std::string &filename) :
            _name(name), _filename(filename), _string(""),
            _position(Vector3d(0, 0)), _direction(Vector3d(0, 0)), _speed(0), _isMoving(true) {
        _filename = _filename + file_extension;
    }

    Object::Object(const Object &other) :
            _name(other._name), _filename(other._filename), _string(other._string),
            _position(other._position), _direction(other._direction), _speed(other._speed),
            _color(other._color), _background(other._background), _character(other._character) {
    }

    Object::~Object() {
    }

    void Object::setName(const std::string &name) { _name = name; }

    void Object::setString(const std::string &string) { _string = string; };

    void Object::setDirection(const Vector3d &direction) { _direction = direction; }

    void Object::setPosition(const Vector3d &position) { _position = position; }

    void Object::setSpeed(float speed) { _speed = speed; }

    const arcade::Vector3d &Object::getDirection() const { return (_direction); }

    const std::string &Object::getName() const { return (_name); }

    const arcade::Vector3d &Object::getPosition() const { return (_position); }

    float Object::getSpeed() const { return (_speed); }

    const std::string &Object::getString() const { return (_string); }

    const std::string &Object::getFilename() const { return (_filename); }

    Object::ObjectType Object::getType() const { return (ObjectType::Object); }

    bool Object::isTextureOk(void) const { return (true); }

    void Object::updateVisual(uint32_t obj) {
    }

    virtual bool setProperties(const std::string &path) {
        if (!loadTexture(path))
            return (false);
        loadSprite();
    }

    void        loadSprite() {
        int     i = 0;
        int     j = 0;

        while (i < _mHeight / 100) {
            std::vector<SDL_Rect> sprite;
            while (j < _mWidth / 100) {
                SDL_Rect rect;
                rect.x = j;
                rect.y = i;
                rect.w = 100;
                rect.h = 100;
                sprite.push(rect);
                j += 100;
            }
            _sprite.push(sprite);
            i += 100;
        }
    }

    bool        loadTexture(const std::string &path){
        SDL_Surface *loadedSurface = IMG_Load(path.c_str());
        SDL_Texture* newTexture = NULL;

        if (loadedSurface == NULL) {
            printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        } else {
//Color key image
            SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
//Create texture from surface pixels
            newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
            if (newTexture == NULL) {
                printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
            } else {
//Get image dimensions
                mWidth = loadedSurface->w;
                mHeight = loadedSurface->h;
            }
        }
        SDL_FreeSurface(loadedSurface);
        //Return success
        mTexture = newTexture;
        return (mTexture != NULL);
    }
}