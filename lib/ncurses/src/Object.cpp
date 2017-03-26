//
// Created by vincy on 24/03/17.
//

#include "Object.hpp"

namespace arcade
{
  Object::Object(std::string name, Vector3d position, uint32_t speed) :
	  _name(name), _string(""), _position(position), _direction(Vector3d(0, 0)), _speed(speed)
  {

  }

  Object::~Object() {}

  void Object::setName(const std::string &name) {_name = name;}
  void Object::setString(const std::string &string) {_string = string;};
  void Object::setDirection(const Vector3d &direction) {_direction = direction;}
  void Object::setPosition(const Vector3d &position) {_position = position;}
  void Object::setSpeed(uint32_t speed) {_speed = speed;}

  const arcade::Vector3d & Object::getDirection() const { return (_direction);}
  const std::string & Object::getName() const {return (_name);}
  const arcade::Vector3d & Object::getPosition() const {return (_position);}
  uint32_t Object::getSpeed() const {return (_speed);}
  const std::string & Object::getString() const {return (_string);}

  bool Object::isTextureOk(void) const {return (false);}
  void Object::updateVisual(uint32_t) {}
}

