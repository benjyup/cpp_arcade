//
// Created by vincy on 24/03/17.
//

#include <vector>
#include "Object.hpp"

namespace arcade
{
  Object::Object(const std::string &name, const std::string &filename) :
	  _name(name), _filename(filename), _string(""), _position(Vector3d(0, 0)), _direction(Vector3d(0, 0)), _speed(0)
  {
    getProperties(filename);
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

  /* Not virtual */

  std::string Object::getColor() const { return _color; }
  std::string Object::getBackground() const { return _background;  }
  std::string Object::getCharacter() const { return _character; }

  bool Object::getProperties(const std::string &filename)
  {
    std::ifstream 		fs;
    std::vector<std::string>	properties = {"$", "black", "white"};
    std::string			str;
    unsigned int		i = 0;

    fs.open(filename);
    if (fs.is_open())
      {
	while (!fs.eof() && i < properties.size())
	  {
	    getline(fs, str);
	    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	    if (!str.empty() && str 	!= "none")
	      properties[i] = str;
	    i += 1;
	  }
	(void)fs.close();
      }
    _character = properties[0];
    _color = properties[1];
    _background = properties[2];
    return (true);
  }
}

