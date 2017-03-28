//
// Created by vincy on 28/03/17.
//

#include "Label.hpp"

namespace arcade
{
  Label::Label(const std::string &name, const std::string &filename)
  {
    _name = name;
    _filename = filename;
    _string = "";
    _position = Vector3d(0, 0);
    _direction = Vector3d(0, 0);
    _speed = 0;
    setProperties(filename);
  }

  Label::~Label() {}

  bool Label::setProperties(const std::string &filename)
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
	    if (i != 0)
	    	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	    if (!str.empty() && str != "none")
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