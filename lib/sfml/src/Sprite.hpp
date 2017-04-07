//
// Created by peixot_b on 06/04/17.
//

#ifndef CPP_ARCADE_SPRITE_HPP
#define CPP_ARCADE_SPRITE_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "Object.hpp"

namespace arcade
{
    class Sprite : public Object
    {
    public:
        Sprite(std::string const &name, std::shared_ptr<sf::Texture> &);
        ~Sprite();

        void                            setVisual(std::shared_ptr<sf::Texture> const &);
        virtual sf::Drawable            &getDrawable();
        sf::Sprite                      &getSprite();

        virtual void                    moveSprite(void);
        virtual void                    setPosition(arcade::Vector3d const &pos);
        virtual void                    updateVisual(uint32_t);
        virtual bool                    isTextureOk(void) const;
        virtual bool                    isMoving(void) const;

    protected:
        sf::Sprite                      _sprite;
        std::shared_ptr<sf::Texture>    _texture;
        void                            setSpritePosition(int32_t, int32_t);
        void                            setSpritePosition(arcade::Vector3d const &pos);
    };
}

#endif //CPP_ARCADE_SPRITE_HPP
