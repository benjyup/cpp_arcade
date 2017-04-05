//
// Created by vincy on 24/03/17.
//

#include <vector>
#include <ncurses/curses.h>
#include "Object.hpp"
#include "NcursesTools.hpp"

namespace arcade
{
  const std::string		Object::directory_name = "./resources/";
  const std::string		Object::file_extension = ".ncurses";
  int				Object::_color_int = 16;

  Object::Object() : _name(""), _filename(""), _string(""),
  _position(Vector3d(0, 0)), _direction(Vector3d(0, 0)), _speed(0), _isMoving(true)
  {}

  Object::Object(const std::string &name, const std::string &filename) :
	  _name(name), _filename(filename), _string(""),
	  _position(Vector3d(0, 0)), _direction(Vector3d(0, 0)), _speed(0), _isMoving(true)
  {
//    _filename = directory_name + _filename + file_extension;
    _filename = _filename + file_extension;
    setProperties(_filename);
  }

  Object::Object(const Object &other) :
	  _name(other._name), _filename(other._filename), _string(other._string),
	  _position(other._position), _direction(other._direction), _speed(other._speed),
	  _color(other._color), _background(other._background), _character(other._character)

  {  }

  Object::~Object() {}

  /* virtual functions of IObject */


  void 				Object::setName(const std::string &name) {_name = name;}
  void 				Object::setString(const std::string &string) {_string = string;};
  void 				Object::setDirection(const Vector3d &direction) {_direction = direction;}
  void 				Object::setPosition(const Vector3d &position) {_position = position;}
  void 				Object::setSpeed(float speed) {_speed = speed;}

  const arcade::Vector3d 	&Object::getDirection() const { return (_direction);}
  const std::string 		&Object::getName() const {return (_name);}
  const arcade::Vector3d 	&Object::getPosition() const {return (_position);}
  float 			Object::getSpeed() const {return (_speed);}
  const std::string 		&Object::getString() const {return (_string);}
  const std::string 		&Object::getFilename() const {return (_filename);}
  Object::ObjectType Object::getType() const { return (ObjectType::Object); }

  bool 				Object::isTextureOk(void) const {return (true);}
  void 				Object::updateVisual(uint32_t) {}

  /* !(virtual functions of IObject) */

  std::string 			Object::getColor() const { return _color; }
  std::string 			Object::getBackground() const { return _background;  }

  bool 				Object::setProperties(const std::string &filename)
  {
    std::ifstream 		fs;
    std::vector<std::string>	properties = NcursesTools::NT_DEFAULT_PROPERTIES;
    std::string			str;
    unsigned int		i = 0;

    fs.open(filename);
    if (fs.is_open())
      {
	while (!fs.eof() && i < properties.size())
	  {
	    getline(fs, str);
	    if (i == 0 && str.length() != 1)
	      throw std::runtime_error("The configuration file of " + str + " is invalid.");
	    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	    if (!str.empty() && str != NcursesTools::NT_NONE)
	      properties[i] = str;
	    i += 1;
	  }
	(void)fs.close();
      } // throw si il existe pas
    _string = properties[0];
    _color = properties[1];
    return (true);
  }

  bool 				Object::operator==(const Object &rhs) const
  {
    return this == &rhs &&
	   _name == rhs._name &&
	   _filename == rhs._filename &&
	   _string == rhs._string &&
	   _position == rhs._position &&
	   _direction == rhs._direction &&
	   _speed == rhs._speed &&
	   _color == rhs._color &&
	   _background == rhs._background &&
	   _character == rhs._character;
  }

  bool 				Object::operator!=(const Object &rhs) const
  {
    return !(rhs == *this);
  }

  std::ostream 			&operator<<(std::ostream &os, const Object &object)
  {
    os << " _name: " << object.getName() << " _filename: " << object.getFilename()
       << " _string: " << object.getString() << " _position: " << object.getPosition() << " _direction: " << object.getDirection()
       << " _speed: " << object.getSpeed() << " _color: " << object.getColor() << " _background: " << object.getBackground();
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

    bool Object::isMoving(void) const
    {return (_isMoving);}
}

