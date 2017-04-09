//
// Created by peixot_b on 05/04/17.
//

#ifndef CPP_ARCADE_LABEL_HPP
#define CPP_ARCADE_LABEL_HPP

#include <vector>
#include "Object.hpp"

namespace arcade
{
    class Label : public Object
    {
    public:
        Label(const std::string &name, std::string const &,
              std::shared_ptr<sf::Font> &);
        virtual ~Label();
        void        setVisual(std::shared_ptr<sf::Font>&);

        virtual void                        updateVisual(uint32_t);
        virtual bool                        isTextureOk(void) const;
        virtual bool                        isMoving(void) const;
        virtual sf::Drawable                &getDrawable(void);
        sf::Text                            &getText(void);

        virtual void                        setString(std::string const &);
        virtual void                        setPosition(Vector3d const &);

    protected:
        sf::Text                            _text;
        std::shared_ptr<sf::Font>           _font;
        void                                setTextPosition(arcade::Vector3d const &);
        void                                setTextPosition(int32_t, int32_t);
    };
}

#endif //CPP_ARCADE_LABEL_HPP
