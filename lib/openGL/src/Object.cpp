//
// Created by florian on 4/5/17.
//

#include "Object.hpp"

namespace arcade {
    Object::Object() : _name(""), _filename(""), _string(""),
                       _position(Vector3d(0, 0)), _direction(Vector3d(0, 0)), _speed(0), _isMoving(false) {}

    Object::Object(const std::string &name, const std::string &filename) :
            _name(name), _filename(filename), _string(""),
            _position(Vector3d(0, 0)), _direction(Vector3d(0, 0)), _speed(0), _isMoving(false) {
    }

    Object::Object(const Object &other) :
            _name(other._name), _filename(other._filename), _string(other._string),
            _position(other._position), _direction(other._direction), _speed(other._speed),
            _color(other._color), _character(other._character) {
    }

    Object::~Object() {
    }

    void Object::setName(const std::string &name) { _name = name; }

    void Object::setString(const std::string &string) { _string = string; };

    void Object::setDirection(const Vector3d &direction) { _direction = direction; }

    void Object::setPosition(const Vector3d &position) { _position = position; }

    void Object::setSpeed(float speed) { _speed = speed; }

    void Object::setScale(float scale) { _scale = scale; }

    const arcade::Vector3d &Object::getDirection() const { return (_direction); }

    const std::string &Object::getName() const { return (_name); }

    const arcade::Vector3d &Object::getPosition() const { return (_position); }

    float Object::getSpeed() const { return (_speed); }

    const std::string &Object::getString() const { return (_string); }

    std::string const &Object::getTextureFile(void) const { return (_filename); }
}