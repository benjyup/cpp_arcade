/*
** Object.cpp for cpp_arcade in /home/peixot_b/delivery/cpp_arcade/Object.cpp
**
** Made by benjamin.peixoto
** Login   <benjamin.peixoto@epitech.eu>
**
** Started on  Mon Apr 03 14:18:52 2017 benjamin.peixoto
// Last update Fri Apr  7 15:33:24 2017 Benjamin
*/

#include <vector>
#include <cstdint>
#include "Object.hpp"

namespace arcade
{
	const std::string		Object::directory_name = "./ressources/";
	const std::string		Object::file_extension = ".sfml";

    Object::Object(std::string const &name) :
      _color(sf::Color(255, 0, 0)), _colorTurn(0),
      _name(name), _str(""), _filename(""), _position({0, 0}), _direction({0, 0}), _speed(0), _scale(1)
    {
    }

  Object::~Object() {}

    void 				Object::setName(const std::string &name) {_name = name;}
    void 				Object::setString(const std::string &string) {_string = string;};
    void 				Object::setDirection(const Vector3d &direction) {_direction = direction;}
    void 				Object::setPosition(const Vector3d &position)
    {
        _position = position;
        _position.setX(_position.getX() * _scale);
        _position.setY(_position.getY() * _scale);
    }
    void 				Object::setSpeed(float speed) {_speed = speed;}
    void                Object::setScale(float scale) {_scale = scale;}
    void                Object::setTextureFile(std::string const &file) {_filename = file;}

  const arcade::Vector3d 	&Object::getDirection() const { return (_direction);}
  const std::string 		&Object::getName() const {return (_name);}
  const arcade::Vector3d 	&Object::getPosition() const {return (_position);}
  float					Object::getSpeed() const {return (_speed);}
  float					Object::getScale() const {return (_scale);}
  const std::string 		&Object::getString() const {return (_string);}
  const std::string 		&Object::getFilename() const {return (_filename);}
  Object::ObjectType		Object::getType() const {return (ObjectType::Object); }
  const std::string       &Object::getTextureFile() const {return (_filename);}
  
    bool 				Object::operator==(const Object &other) const
  {
	  return this == &other &&
			 _name == other._name &&
			 _filename == other._filename &&
			 _string == other._string &&
			 _position == other._position &&
			 _direction == other._direction &&
			 _speed == other._speed &&
			 _color == other._color &&
			 _background == other._background &&
			 _character == other._character;
  }

	bool 				Object::operator!=(const Object &other) const
	{
		return !(other == *this);
	}

	std::ostream 			&operator<<(std::ostream &os, const Object &object)
	{
		os << " _name: " << object.getName() << " _filename: " << object.getFilename()
		   << " _string: " << object.getString() << " _position: " << object.getPosition() << " _direction: " << object.getDirection()
		   << " _speed: " << object.getSpeed();
		return os;
	}

    Object 			&Object::operator=(const Object &other)
	{
		if (this != &other)
		{
			_name = other._name;
			_filename = other._filename;
			_string = other._string;
			_position = other._position;
			_direction = other._direction;
			_speed = other._speed;
			_color = other._color;
			_background = other._background;
		}
		return (*this);
	}
}
