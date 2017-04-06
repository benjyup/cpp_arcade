//
// Created by florian on 4/6/17.
//

#include "Label.hpp"

namespace arcade
{
    Label::Label(const std::string &name, const std::string &filename)
    {
        _isMoving = false;
        _name = name;
        _filename = filename + file_extension;
        setProperties(_filename);
        _string = "";
        _position = Vector3d(0, 0);
        _direction = Vector3d(0, 0);
        _speed = 0;
        setProperties(filename);
    }

    Label::~Label() {}

    bool Label::setProperties(const std::string &filename)
    {
        if (!(font = TTF_OpenFont((directory_name + filename + file_extension).c_str(), 1)))
            return (false);
        return (true);
        //set size;
    }

    Object::ObjectType Label::getType() const { return (ObjectType::Label); }
}