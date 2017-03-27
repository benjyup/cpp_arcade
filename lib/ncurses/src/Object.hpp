//
// Created by vincy on 24/03/17.
//

#ifndef CPP_ARCADE_OBJECT_HPP
#define CPP_ARCADE_OBJECT_HPP

#include <fstream>
#include <algorithm>
#include "IObject.hpp"

namespace arcade
{
  class Object : public IObject
  {
   public:
    Object(const std::string &name, const std::string &filename);
    virtual ~Object();

    virtual void			setName(std::string const &);
    virtual void			setString(std::string const &);
    virtual void			setPosition(Vector3d const &);
    virtual void			setDirection(Vector3d const &);
    virtual void			setSpeed(uint32_t);

    virtual std::string const &		getName(void) const;
    virtual std::string const &		getString(void) const;
    virtual arcade::Vector3d const &	getPosition (void) const;
    virtual arcade::Vector3d const &	getDirection(void) const;
    virtual uint32_t			getSpeed(void) const;

    virtual bool 			isTextureOk(void) const;
    virtual void			updateVisual(uint32_t);

    std::string getColor() const;
    std::string getBackground() const;
    std::string getCharacter() const;

    bool 	getProperties(const std::string &pahtname);

   private:
    std::string		_name;
    std::string		_filename;
    std::string		_string;
    Vector3d		_position;
    Vector3d		_direction;
    uint32_t		_speed;
    std::string		_color;
    std::string		_background;
    std::string		_character;

  };
}

#endif //CPP_ARCADE_OBJECT_HPP
