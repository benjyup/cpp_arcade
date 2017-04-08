//
// Created by florian on 4/7/17.
//

#ifndef CPP_ARCADE_SPRITE_HPP
#define CPP_ARCADE_SPRITE_HPP

#include "Object.hpp"

namespace arcade
{

    class Sprite : public Object {
    protected:
        SDL_Rect _sprite;
        SDL_Surface *_texture;
        SDL_Rect _pos;
    public:
        Sprite(std::string const &, std::string const &);

        virtual ~Sprite();

        virtual SDL_Rect &getSprite(void);

        virtual SDL_Surface *getSurface(void);

        virtual SDL_Rect      &getSpritePos(void);

        virtual void			setTextureFile(std::string const &);

        virtual Object::ObjectType 		getType(void) const;

        virtual void moveSprite(void);

        virtual void updateVisual(uint32_t);

        virtual bool isTextureOk(void) const;

        virtual bool isMoving(void) const;

    protected:
        bool loadTexture(const std::string &path);

    };
}

#endif //CPP_ARCADE_SPRITE_HPP
