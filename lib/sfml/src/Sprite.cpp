//
// Created by peixot_b on 06/04/17.
//

#include <string>
#include <iostream>
#include "Window.hpp"
#include "Sprite.hpp"

namespace arcade
{
    Sprite::Sprite(std::string const &name, std::shared_ptr<sf::Texture> &texture) : Object(name)
    {
        this->setVisual(texture);
    }

    Sprite::~Sprite()
    {
    }

    void    Sprite::setSpritePosition(int32_t x, int32_t y)
    {
        _sprite.setPosition(x * Window::TILESIZE,
                            y *  Window::TILESIZE);
    }

    void    Sprite::setSpritePosition(arcade::Vector3d const & pos)
    {
        setSpritePosition(pos.getX(), pos.getY());
    }

    void    Sprite::setPosition(arcade::Vector3d const & pos)
    {
        setSpritePosition(_position);
        _position = pos;
    }

    void    Sprite::setVisual(std::shared_ptr<sf::Texture> const &texture)
    {
        _texture = texture;
        _sprite = sf::Sprite(*this->_texture);
        setSpritePosition(this->getPosition());
        updateVisual(0);
    }

    sf::Sprite          &Sprite::getSprite(void)
    {
        return (_sprite);
    }

    sf::Drawable        &Sprite::getDrawable(void)
    {
        return (getSprite());
    }

    bool                    arcade::Sprite::isTextureOk(void) const
    {
        return (_texture != NULL);
    }

    bool arcade::Sprite::isMoving(void) const
    {
        return (!(_sprite.getPosition().x == (getPosition().getX() * Window::TILESIZE) &&
                  _sprite.getPosition().y == (getPosition().getY() * Window::TILESIZE)));
    }

    void                                Sprite::moveSprite(void)
    {
        float                         x = (this->_position.getX() * Window::TILESIZE) - this->_sprite.getPosition().x;
        float                         y = (this->_position.getY() * Window::TILESIZE) - this->_sprite.getPosition().y;
        float                         add;

        if (x == 0 && y == 0)
            return;
        if (x != 0)
        {
            add = this->_speed * (NEG_OR(x) * Window::TILESIZE / 60);
            if (NEG_OR(add) * add > NEG_OR(x) * x)
                x = this->_position.getX() * Window::TILESIZE;
            else
                x = this->_sprite.getPosition().x + add;
        }
        else
            x = this->_sprite.getPosition().x;
        if (y != 0)
        {
            add = this->_speed * (NEG_OR(y) * Window::TILESIZE / 60);
            if (NEG_OR(add) * add > NEG_OR(y) * y)
                y = this->_position.getY() * Window::TILESIZE;
            else
                y = this->_sprite.getPosition().y + add;
        }
        else
            y = this->_sprite.getPosition().y;
        this->_sprite.setPosition(x, y);
    }

    void                    Sprite::updateVisual(uint32_t state)
    {
        uint32_t orientation = 0;

        this->moveSprite();
        if (this->getDirection().getX() > 0)
            orientation = 3;
        else
        if (this->getDirection().getX() < 0)
            orientation = 2;
        else
        if (this->getDirection().getY() < 0)
            orientation = 0;
        else
        if (this->getDirection().getY() > 0)
            orientation = 1;

        state = (state % (this->_texture->getSize().x / 100));
        this->_sprite.setTextureRect(sf::IntRect(state * 100, orientation * 100, 100, 100));
        this->_sprite.setScale(static_cast<float>(Window::TILESIZE / 100.0 * this->getScale()),
                               static_cast<float>(Window::TILESIZE / 100.0 * this->getScale()));
    }
}
