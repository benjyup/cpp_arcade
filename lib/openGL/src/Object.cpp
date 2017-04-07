//
// Created by florian on 4/5/17.
//

#include "Object.hpp"

namespace arcade {
    Object::Object() : _name(""), _filename(""), _string(""),
                       _position(Vector3d(0, 0)), _direction(Vector3d(0, 0)), _speed(0), _isMoving(true) {}

    Object::Object(const std::string &name, const std::string &filename) :
            _name(name), _filename(filename), _string(""),
            _position(Vector3d(0, 0)), _direction(Vector3d(0, 0)), _speed(0), _isMoving(true) {
        setProperties();
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

    void Object::setScale(float scale) { _scale = scale; }

    void Object::setTextureFile(std::string const &newFile) { _filename = newFile; }


    const arcade::Vector3d &Object::getDirection() const { return (_direction); }

    const std::string &Object::getName() const { return (_name); }

    const arcade::Vector3d &Object::getPosition() const { return (_position); }

    float Object::getSpeed() const { return (_speed); }

    const std::string &Object::getString() const { return (_string); }

    Object::ObjectType Object::getType() const { return (ObjectType::Object); }

    std::string const &Object::getTextureFile(void) const { return (_filename); }

    bool Object::isTextureOk(void) const {
        if (mTexture)
            return (true);
        return (false);
    }

    void Object::setVisual(std::string const &file) {
        setTextureFile(file);
        setProperties();
    }

    void Object::updateVisual(uint32_t obj) {
        (void) obj;
        //todo
    }

    bool Object::isMoving() const {
        return (_isMoving);
    }

    void        Object::loadSprite() {
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
                sprite.push_back(rect);
                j += 100;
            }
            _sprite.push_back(sprite);
            i += 100;
        }
    }

    bool        Object::loadTexture(const std::string &path){
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
                _mWidth = loadedSurface->w;
                _mHeight = loadedSurface->h;
            }
        }
        SDL_FreeSurface(loadedSurface);
        //Return success
        mTexture = newTexture;
        return (mTexture != NULL);
    }

    bool    Object::setProperties() {
        if (!loadTexture(_filename))
            return (false);
        loadSprite();
        return (true);
    }
}