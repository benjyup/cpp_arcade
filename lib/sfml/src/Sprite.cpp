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
        setVisual(texture);
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
        _sprite = sf::Sprite(*_texture);
        setSpritePosition(getPosition());
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
        float                         ret;
        float                         x = (_position.getX() * Window::TILESIZE) - _sprite.getPosition().x;
        float                         y = (_position.getY() * Window::TILESIZE) - _sprite.getPosition().y;


        if (x == 0 && y == 0)
            return;
        if (x != 0)
        {
            ret = _speed * (((x < 0) ? (-1) : (1)) * Window::TILESIZE / 60);
            if (((ret < 0) ? (-1) : (1)) * ret > ((y < 0) ? (-1) : (1)) * x)
                x = _position.getX() * Window::TILESIZE;
            else
                x = _sprite.getPosition().x + ret;
        }
        else
            x = _sprite.getPosition().x;
        if (y != 0)
        {
            ret = _speed * (((y < 0) ? (-1) : (1))  * Window::TILESIZE / 60);
            if (((ret < 0) ? (-1) : (1)) * ret > ((y < 0) ? (-1) : (1)) * y)
                y = _position.getY() * Window::TILESIZE;
            else
                y = _sprite.getPosition().y + ret;
        }
        else
            y = _sprite.getPosition().y;
        _sprite.setPosition(x, y);
    }

    void                    Sprite::updateVisual(uint32_t state)
    {
        uint32_t orientation = 0;

        moveSprite();
        if (getDirection().getX() > 0)
            orientation = 3;
        else if (getDirection().getX() < 0)
            orientation = 2;
        else if (getDirection().getY() < 0)
            orientation = 0;
        else if (getDirection().getY() > 0)
            orientation = 1;
        state = (state % (_texture->getSize().x / 100));
        _sprite.setTextureRect(sf::IntRect(state * 100, orientation * 100, 100, 100));
        _sprite.setScale(static_cast<float>(Window::TILESIZE / 100.0 * getScale()),
                               static_cast<float>(Window::TILESIZE / 100.0 * getScale()));
    }
}
