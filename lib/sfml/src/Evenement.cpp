//
// Created by peixot_b on 05/04/17.
//

#include <string>
#include "Evenement.hpp"
#include "SFML/Graphics.hpp"

namespace arcade {
    Evenement::Evenement() : _keyCode(IEvenement::KeyCode::Key_Undefined),
                                     _action(IEvenement::Action::Nothing) {}

    Evenement::Evenement(IEvenement::KeyCode keycode) : _keyCode(keycode),
                                                                _action(IEvenement::Action::Nothing) {}

    Evenement::Evenement(sf::Event const &event) {
        switch (event.type) {
            case sf::Event::KeyReleased: // CHECK WHEN A KEY IS RELEASE
                _action = IEvenement::Action::KeyRelease;
                break;
            case sf::Event::KeyPressed: // CHECK WHEN A KEY IS PRESSED
                _action = IEvenement::Action::KeyPressDown;
                break;
            default:
                _action = IEvenement::Action::Nothing;
                break;
        }
        switch (event.key.code) {
            case sf::Keyboard::A:
                _keyCode = IEvenement::KeyCode::Key_A;
                break;
            case sf::Keyboard::Q:
                _keyCode = IEvenement::KeyCode::Key_Q;
                break;
            case sf::Keyboard::Z:
                _keyCode = IEvenement::KeyCode::Key_Z;
                break;
            case sf::Keyboard::D:
                _keyCode = IEvenement::KeyCode::Key_D;
                break;
            case sf::Keyboard::S:
                _keyCode = IEvenement::KeyCode::Key_S;
                break;
            case sf::Keyboard::Num2:
                _keyCode = IEvenement::KeyCode::Key_2;
                break;
            case sf::Keyboard::Num3:
                _keyCode = IEvenement::KeyCode::Key_3;
                break;
            case sf::Keyboard::Num4:
                _keyCode = IEvenement::KeyCode::Key_4;
                break;
            case sf::Keyboard::Num5:
                _keyCode = IEvenement::KeyCode::Key_5;
                break;
            case sf::Keyboard::Num6:
                _keyCode = IEvenement::KeyCode::Key_6;
                break;
            case sf::Keyboard::Num7:
                _keyCode = IEvenement::KeyCode::Key_7;
                break;
            case sf::Keyboard::Num8:
                _keyCode = IEvenement::KeyCode::Key_8;
                break;
            case sf::Keyboard::Num9:
                _keyCode = IEvenement::KeyCode::Key_9;
                break;
            default:
                _keyCode = IEvenement::KeyCode::Key_Undefined;
                break;
        }
    }

    Evenement::~Evenement() {}

    IEvenement::Action Evenement::getAction() const {
        return (_action);
    }

    IEvenement::KeyCode Evenement::getKeyCode() const {
        return (_keyCode);
    }

    uint64_t Evenement::getScore() const {
        return (_score);
    }

    void Evenement::setAction(const IEvenement::Action action) {
        _action = action;
    }

    void Evenement::setKeyCode(const IEvenement::KeyCode keyCode) {
        _keyCode = keyCode;
    }

    void Evenement::setScore(const uint64_t score) {
        _score = score;
    }

    int32_t Evenement::getData(void) const {
        return (0);
    }
}