//
// Created by vincy on 28/03/17.
//

#include "Label.hpp"
#include "NcursesTools.hpp"

namespace arcade
{
  Label::Label(const std::string &name, const std::string &filename)
  {
    _isMoving = false;
    _name = name;
    //_filename = Object::directory_name + _filename + Object::file_extension;
    _filename = filename + file_extension;
    setProperties(_filename);
    _string = "";
    _position = Vector3d(0, 0);
    _direction = Vector3d(0, 0);
    _speed = 0;
    //setProperties(filename);
  }

  Label::~Label() {}

  bool Label::setProperties(const std::string &filename)
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
	    if (i != 0)
	      std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	    if (!str.empty() && str != NcursesTools::NT_NONE)
	      properties[i] = str;
	    i += 1;
	  }
	(void)fs.close();
      }
    _string = properties[0];
    _color = properties[1];
    return (true);
  }

  Object::ObjectType Label::getType() const { return (ObjectType::Label); }

}