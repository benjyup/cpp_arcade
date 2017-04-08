//
// Created by florian on 4/5/17.
//

#ifndef CPP_ARCADE_OBJECT_HPP
#define CPP_ARCADE_OBJECT_HPP

#include "Window.hpp"
#include "Vector3d.hpp"
#include "IObject.hpp"

# define        NEG_OR(c)               ((c < 0) ? (-1) : (1))

namespace arcade
{
    class Window;

    class Object : public IObject
    {
    public:

        enum class ObjectType : char
        {
            Object = 0,
            Label = 1
        };

        static const std::string		file_extension;
        static const std::string		directory_name;

        Object();
        Object(const std::string &name, const std::string &filename);
        Object(const Object& other);
        virtual ~Object();

/*        bool operator==(const Object &rhs) const;
          bool operator!=(const Object &rhs) const;
          Object				&operator=(const Object &other);
*/

        /* virtual functions of IObject */

        virtual void			setName(std::string const &);
        virtual void			setString(std::string const &);
        virtual void			setPosition(Vector3d const &);
        virtual void			setDirection(Vector3d const &);
        virtual void			setSpeed(float);
        virtual void			setScale(float);

        virtual std::string const &		getName(void) const;
        virtual std::string const &		getString(void) const;
        virtual arcade::Vector3d const &	getPosition (void) const;
        virtual arcade::Vector3d const &	getDirection(void) const;
        virtual float			getSpeed(void) const;
        virtual float			getScale(void) const { return (0.0);};
        virtual std::string const &		getTextureFile(void) const;

        virtual SDL_Rect &                          getSprite(void) = 0;
        virtual SDL_Surface      *getSurface(void) = 0;
        virtual SDL_Rect      &getSpritePos(void) = 0;
        virtual Object::ObjectType 		getType(void) const = 0;

        /* !(virtual functions of IObject) */

    protected:
        std::string		_name;
        std::string		_filename;
        std::string		_string;
        Vector3d		_position;
        Vector3d		_direction;
        float		    _speed;
        std::string		_color;
        std::string		_background;
        std::string		_character;
        bool 		    _isMoving;
        static int 	    _color_int;
        float           _scale;
        int             _mWidth;
        int             _mHeight;

    };
}

#endif //CPP_ARCADE_OBJECT_HPP
