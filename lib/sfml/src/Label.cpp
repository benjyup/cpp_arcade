//
// Created by peixot_b on 05/04/17.
//

#include <memory>
#include <SFML/Graphics.hpp>
#include "Label.hpp"
#include "Window.hpp"

namespace arcade
{
    Label::Label(const std::string &name, const std::string &filename,
                 std::shared_ptr<sf::Font> &font) : Object(name, filename)
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
        _font = font;
        _text.setFont(*_font);
        setTextPosition(getPosition());
        updateVisual(0);
    }

    void                    Label::setTextPosition(int32_t x, int32_t y)
    {
        _text.setPosition(x * Window::SIZECELL,
                                y * Window::SIZECELL);
    }

    void                    Label::setTextPosition(arcade::Vector3d const & pos)
    {
        setTextPosition(pos.getX(), pos.getY());
    }

    bool                    Label::isTextureOk(void) const
    {
        return (_font != NULL);
    }

    void 				    Label::setString(const std::string &string) {
        _string = string;
        _text.setString(_string);
    };

    void 				    Label::setPosition(const Vector3d &position)
    {
        setTextPosition(_position);
        _position = position;
    }

    bool                    Label::isMoving(void) const { return (false); }

    sf::Text                &Label::getText(void) { return (_text); }

    sf::Drawable            &Label::getDrawable(void) { return (getText()); }

    void                    Label::updateVisual(uint32_t)
    {
        _text.setCharacterSize((unsigned int) ((Window::SIZECELL) * getScale()));
    }

}