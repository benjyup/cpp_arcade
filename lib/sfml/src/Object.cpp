/*
** Object.cpp for cpp_arcade in /home/peixot_b/delivery/cpp_arcade/Object.cpp
**
** Made by benjamin.peixoto
** Login   <benjamin.peixoto@epitech.eu>
**
** Started on  Mon Apr 03 14:18:52 2017 benjamin.peixoto
** Last update Mon Apr 03 14:18:52 2017 benjamin.peixoto
*/

#include <vector>
#include <cstdint>
#include "Object.hpp"

namespace arcade
{
	const std::string		Object::directory_name = "./ressources/";
	const std::string		Object::file_extension = ".sfml";

	Object::Object() : _name(""), _filename(""), _string(""),
		     _position(Vector3d(0, 0)), _direction(Vector3d(0, 0)), _speed(0)
	{}

	Object::Object(const std::string &name, const std::string &filename) :
			_name(name), _filename(filename), _string(""),
			_position(Vector3d(0, 0)), _direction(Vector3d(0, 0)), _speed(0)
	{
		_filename = _filename + file_extension;
	}

	Object::Object(const Object &other) :
			_name(other._name), _filename(other._filename), _string(other._string),
			_position(other._position), _direction(other._direction), _speed(other._speed),
			_color(other._color), _background(other._background), _character(other._character)

	{  }

	Object::~Object() {}

	void 				Object::setName(const std::string &name) {_name = name;}
	void 				Object::setString(const std::string &string) {_string = string;};
	void 				Object::setDirection(const Vector3d &direction) {_direction = direction;}
	void 				Object::setPosition(const Vector3d &position) {_position = position;}
	void 				Object::setSpeed(float speed) {_speed = speed;}


	const arcade::Vector3d 	&Object::getDirection() const { return (_direction);}
	const std::string 		&Object::getName() const {return (_name);}
	const arcade::Vector3d 	&Object::getPosition() const {return (_position);}
	float					Object::getSpeed() const {return (_speed);}
	const std::string 		&Object::getString() const {return (_string);}
	const std::string 		&Object::getFilename() const {return (_filename);}
	Object::ObjectType		Object::getType() const { return (ObjectType::Object); }

	bool 				Object::isTextureOk(void) const {return (true);}
	void 				Object::updateVisual(uint32_t obj) {}

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

    bool Object::isMoving(void) const
    {return (_isMoving);}

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