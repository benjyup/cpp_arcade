//
// Created by vincent on 28/03/17.
//

#include "Vector3d.hpp"

namespace arcade
{
  Vector3d::Vector3d(int32_t x, int32_t y, int32_t z)
	  : _x(x), _y(y), _z(z)
  {}

  Vector3d::Vector3d(Vector3d const &other)
	  : _x(other.getX()), _y(other.getY()), _z(other.getZ())
  {}

  Vector3d::~Vector3d(void)
  {};

  Vector3d &Vector3d::operator=(Vector3d const &other)
  {
    if (&other != this)
      {
	this->_x = other.getX();
	this->_y = other.getY();
	this->_z = other.getZ();
      }
    return (*this);
  }

  int32_t Vector3d::getX(void) const
  { return (this->_x); };

  int32_t Vector3d::getY(void) const
  { return (this->_y); };

  int32_t Vector3d::getZ(void) const
  { return (this->_z); };

  void Vector3d::setX(int32_t x)
  { this->_x = x; };

  void Vector3d::setY(int32_t y)
  { this->_y = y; };

  void Vector3d::setZ(int32_t z)
  { this->_z = z; };

  bool Vector3d::operator==(Vector3d const &other) const
  {
    return (this->getX() == other.getX() && this->getY() == other.getY());
  }

  Vector3d Vector3d::operator+(Vector3d const &other) const
  {
    return (Vector3d(this->getX() + other.getX(), this->getY() + other.getY()));
  };

  std::ostream		&operator<<(std::ostream &os, const Vector3d &vector)
  {
    os << "x = " << vector.getX() << " y = " << vector.getY();
    return (os);
  }
}