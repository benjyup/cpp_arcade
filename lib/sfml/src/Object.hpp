/*
** Object.hpp for cpp_arcade in /home/peixot_b/delivery/cpp_arcade/Object.hpp
**
** Made by benjamin.peixoto
** Login   <benjamin.peixoto@epitech.eu>
**
** Started on  Mon Apr 03 14:18:52 2017 benjamin.peixoto
// Last update Fri Apr  7 15:36:07 2017 Benjamin
*/

#ifndef Object_HPP_
#define Object_HPP_

#include <fstream>
#include <algorithm>
#include <ostream>
#include <cstdint>
#include <SFML/Graphics.hpp>
#include "IObject.hpp"

namespace arcade
{
    class Window;
    class SfmlLib;

    class Object : public IObject
    {
    public:

        enum class	ObjectType : char
        {
            Object = 0,
            Label = 1
        };
        static const std::string		directory_name;
        static const std::string		file_extension;

        Object();
        Object(const std::string &name, const std::string &filename);
        Object(const std::string &name);
        Object(const Object& other);

        bool operator==(const Object &rhs) const;
        bool operator!=(const Object &rhs) const;

        virtual ~Object();
        Object				&operator=(const Object &other);

        virtual void			setName(std::string const &);
        virtual void			setString(std::string const &);
        virtual void			setPosition(Vector3d const &);
        virtual void			setDirection(Vector3d const &);
        virtual void			setSpeed(float);
        virtual void			setScale(float);
        virtual void            setTextureFile(std::string const &);


        virtual std::string const &		    getName(void) const;
        virtual std::string const &	    	getString(void) const;
        virtual std::string const &		    getFilename(void) const;
        virtual arcade::Vector3d const &	getPosition (void) const;
        virtual arcade::Vector3d const &	getDirection(void) const;
        virtual float                       getSpeed(void) const;
        virtual float			            getScale(void) const;
        virtual Object::ObjectType 		    getType(void) const;
        virtual sf::Drawable    &getDrawable(void) = 0;
        virtual std::string const &  getTextureFile(void) const;


    protected:
      
      sf::Color			_color;
      char		_colorTurn;
        std::string		_name;
            std::string	_str;
      std::string		_filename;
        std::string		_string;
        Vector3d		_position;
        Vector3d		_direction;
        float		    _speed;
        float           _scale;
      std::string		_background;
        std::string		_character;
        bool 		_isMoving;

    };
    std::ostream &operator<<(std::ostream &os, const Object &object);
}

#endif //Object_HPP_
