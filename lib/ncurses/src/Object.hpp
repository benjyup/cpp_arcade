//
// Created by vincy on 24/03/17.
//

#ifndef CPP_ARCADE_OBJECT_HPP
#define CPP_ARCADE_OBJECT_HPP

#include <fstream>
#include <algorithm>
#include <ostream>
#include "IObject.hpp"

namespace arcade
{
  class Object : public IObject
  {
   public:

    enum class ObjectType : char
    {
      Object = 0,
      Label = 1
    };

    static const std::string		directory_name;
    static const std::string		file_extension;
//    static const


    Object();
    Object(const std::string &name, const std::string &filename);
    Object(const Object& other);

    bool operator==(const Object &rhs) const;

    bool operator!=(const Object &rhs) const;

    virtual ~Object();

    Object				&operator=(const Object &other);

    /* virtual functions of IObject */

    virtual void			setName(std::string const &);
    virtual void			setString(std::string const &);
    virtual void			setPosition(Vector3d const &);
    virtual void			setDirection(Vector3d const &);
    virtual void			setSpeed(float);
    virtual void			setScale(float) {};
    virtual void			setTextureFile(std::string const &);
    virtual void			setVisual(std::string const &);

    virtual std::string const &		getName(void) const;
    virtual std::string const &		getString(void) const;
    virtual std::string const &		getFilename(void) const;
    virtual arcade::Vector3d const &	getPosition (void) const;
    virtual arcade::Vector3d const &	getDirection(void) const;
    virtual float			getSpeed(void) const;
    virtual float			getScale(void) const { return (0.0);};
    virtual Object::ObjectType 		getType(void) const;
    virtual std::string const &		getTextureFile(void) const;

    virtual bool 			isTextureOk(void) const;
    virtual void			updateVisual(uint32_t);
    virtual bool 			isMoving(void) const;

    /* !(virtual functions of IObject) */

    std::string getColor() const;
    std::string getBackground() const;

    virtual bool 			setProperties(const std::string &pahtname);

   protected:
    std::string		_name;
    std::string		_filename;
    std::string		_string;
    Vector3d		_position;
    Vector3d		_direction;
    float		_speed;
    std::string		_color;
    std::string		_background;
    std::string		_character;
    bool 		_isMoving;

    static int 	_color_int;
  };

  std::ostream &operator<<(std::ostream &os, const Object &object); //demander si on à le droit à friend
}

#endif //CPP_ARCADE_OBJECT_HPP
