//
// Created by peixot_b on 05/04/17.
//

#include <memory>
#include <SFML/Graphics.hpp>
#include "Label.hpp"
#include "Window.hpp"

namespace arcade
{
    Label::Label(const std::string &name, std::shared_ptr<sf::Font> &font) : Object(name)
    {
        setVisual(font);
        _isMoving = false;
        _name = name;
        _string = "";
        _position = Vector3d(0, 0);
        _direction = Vector3d(0, 0);
        _speed = 0;
    }

    Label::~Label() {}

    void        Label::setVisual(std::shared_ptr<sf::Font>& font)
    {
        this->_font = font;
        this->_text.setFont(*this->_font);
        this->setTextPosition(this->getPosition());
        this->updateVisual(0);
    }

    void                    Label::setTextPosition(int32_t x, int32_t y)
    {
        this->_text.setPosition(x * Window::TILESIZE,
                                y * Window::TILESIZE);
    }

    void                    Label::setTextPosition(arcade::Vector3d const & pos)
    {
        this->setTextPosition(pos.getX(), pos.getY());
    }

    bool                    Label::isTextureOk(void) const
    {
        return (this->_font != NULL);
    }

    bool                    Label::isMoving(void) const { return (false); }

    sf::Text                &Label::getText(void) { return (this->_text); }

    sf::Drawable            &Label::getDrawable(void) { return (this->getText()); }

    void                    Label::updateVisual(uint32_t)
    {
        this->_text.setCharacterSize((unsigned int) ((Window::TILESIZE) * this->getScale()));
    }

}