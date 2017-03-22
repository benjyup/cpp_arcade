//
// Created by puente_t on 13/03/17.
//

#ifndef ARCADE_VECTOR3D_HPP
#define ARCADE_VECTOR3D_HPP

#include <cstdint>

namespace arcade
{
  class Vector3d
  {
   private:
    int32_t _x;
    int32_t _y;
    int32_t _z;
   public:
    Vector3d(int32_t x, int32_t y, int32_t z = 0)
	    : _x(x), _y(y), _z(z)
    {};

    Vector3d(Vector3d const &other)
	    : _x(other.getX()), _y(other.getY()), _z(other.getZ())
    {};

    ~Vector3d(void)
    {};

    Vector3d &operator=(Vector3d const &other)
    {
      if (&other != this)
	{
	  this->_x = other.getX();
	  this->_y = other.getY();
	  this->_z = other.getZ();
	}
      return (*this);
    }

    int32_t getX(void) const
    { return (this->_x); };

    int32_t getY(void) const
    { return (this->_y); };

    int32_t getZ(void) const
    { return (this->_z); };

    void setX(int32_t x)
    { this->_x = x; };

    void setY(int32_t y)
    { this->_y = y; };

    void setZ(int32_t z)
    { this->_z = z; };

    bool operator==(Vector3d const &other)
    {
      return (this->getX() == other.getX() && this->getY() == other.getY());
    }

    Vector3d operator+(Vector3d const &other) const
    {
      return (Vector3d(this->getX() + other.getX(), this->getY() + other.getY()));
    };
  };
};

#endif //ARCADE_VECTOR3D_HPP
