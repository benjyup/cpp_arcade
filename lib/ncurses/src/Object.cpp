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

  void Object::setName(const std::string &)
  {}
}

