//
// Created by florian on 4/6/17.
//

#ifndef CPP_ARCADE_LABEL_HPP
#define CPP_ARCADE_LABEL_HPP

#include "Object.hpp"

namespace arcade {

    class Label : public Object {
    public:
        Label(const std::string &name, const std::string &filename);

        virtual ~Label();

        virtual SDL_Rect &getSprite(void);

        virtual SDL_Surface *getSurface(void);

        virtual SDL_Rect &getSpritePos(void);

        virtual Object::ObjectType getType(void) const;

        virtual void setString(std::string const &);

        virtual void setTextureFile(std::string const &);

        virtual void updateVisual(uint32_t);

        virtual bool isTextureOk(void) const;

        virtual bool isMoving(void) const;

    protected:
        TTF_Font *font;
        SDL_Surface *_texture;
        SDL_Rect _pos;
    };
}

#endif //CPP_ARCADE_LABEL_HPP
