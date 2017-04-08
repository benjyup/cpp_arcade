//
// Window.cpp for Project-Master in /home/peixot_b/Epitech/Tek2/CPP/Arcade/cpp_arcade/lib/sfml/src
// 
// Made by peixot_b
// Login   <benjamin.peixoto@epitech.eu>
// 
// Started on  Wed Mar 22 17:34:04 2017 peixot_b
// Last update Fri Apr  7 15:23:53 2017 Benjamin
//

#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Window.hpp"
#include "Object.hpp"
#include "Evenement.hpp"

uint32_t                        arcade::Window::MAPSIZE = 40;
float                           arcade::Window::SIZECELL = 1000 / 40;

namespace arcade
{
    arcade::Window::Window(std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>>> &objects,
						   uint64_t height,
                           uint64_t width) : _size(height, width), _isopen(true), _window(sf::VideoMode(1000, 1000),
                                                                                        "Arcade - LibSFML",
                                                                                        sf::Style::Close |
                                                                                        sf::Style::Titlebar),
                                             _objects(objects), _height(height), _width(width), _min_size(0, 0, 0),
                                             _calc(0)
    {
      _window.pollEvent(_event);
      std::cout << "init" << std::endl;
    }

    arcade::Window::~Window() {
		std::cout << "Window supprimée" << std::endl;
        _objects.reset();
        if(_window.isOpen())
            _window.close();
		_isopen = false;
	}

	bool arcade::Window::isOpen() const { return (_isopen); }

	int32_t arcade::Window::getHeight() const { return (_height); }

	int32_t arcade::Window::getLenght() const { return (_width); }

	const sf::RenderWindow &arcade::Window::get_Window() const { return (_window); }

	const arcade::Vector3d &arcade::Window::getSize() const { return (_size); }

	void arcade::Window::setMapSize(uint32_t size)
	{
        Window::MAPSIZE = size;
        Window::SIZECELL = Window::WINSIZE / Window::MAPSIZE;
	}

    bool arcade::Window::event()
    {
        if (_window.pollEvent(_event))
        {
            if ((_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Escape)
                || _event.type == sf::Event::Closed)
                return (false);
            notify(arcade::Evenement(_event));
        }
        return (true);
	}

	arcade::FrameType arcade::Window::refresh()
    {
        sf::Int32                       t;
        arcade::FrameType               frame;
        std::shared_ptr<arcade::Object> obj_s;

        t = _clock.getElapsedTime().asMilliseconds();
        frame = arcade::FrameType::UpdateFrame;
        if (t >= 83 * 60)
        {
            t = 0;
            _calc = t;
            _clock.restart();
        }
        if (t >= _calc + 16)
        {
            frame = arcade::FrameType::GameFrame;
            _calc = t;
        }
        _window.clear();
        for(auto & obj : *_objects) {
            try {
                obj_s = std::dynamic_pointer_cast<arcade::Object>(obj);
                if (obj_s->isTextureOk())
                {
                    obj_s->updateVisual((uint32_t)(_clock.getElapsedTime().asMilliseconds() / 100));
                    _window.draw(obj_s->getDrawable());
                }
            }
            catch (std::bad_cast const &) {
                throw ("Another type of Object");
            }
        }
        _window.display();
        return (frame);
    }

	void arcade::Window::addObject(std::shared_ptr<arcade::IObject> &obj) {
	  destroyObject(obj);
	  _objects->push_back(std::shared_ptr<arcade::IObject>(obj));
	}

	void arcade::Window::addObject(std::shared_ptr<arcade::IObject> &obj, const Vector3d &pos) {
		obj->setPosition(pos);
		addObject(obj);
	}

	void arcade::Window::moveObject(std::shared_ptr<arcade::IObject> &obj, const Vector3d &pos)
	{
        for (auto &it : *_objects)
        {
            if (it == obj)
                it->setPosition(pos);
        }
    }

	void arcade::Window::moveObject(std::string name, const Vector3d &pos) {
		for (auto &it : *_objects)
			if (name == it->getName()) {
                it->setPosition(pos);
			}
	}

    void arcade::Window::destroyObject(std::shared_ptr<arcade::IObject> &obj) {
        std::vector<std::shared_ptr<arcade::IObject> >::iterator it;

        for (it = _objects->begin(); it != _objects->end(); it++)
        {
            if (*it == obj)
            {
		  _objects->erase(it);
                return;
            }
        }

    }

	void arcade::Window::notify(const IEvenement &evenement) {
        for (auto &it : _observers)
            it->getNotified(evenement);
    }

	std::shared_ptr<arcade::IEvenement> arcade::Window::getEvent() {
		return (std::make_shared<arcade::Evenement>(_event));
	}

	void arcade::Window::removeObserver(IObserver *observer) {
        auto it = std::find(_observers.begin(), _observers.end(), observer);
        if (it != _observers.end())
            _observers.erase(it);
    }

	void arcade::Window::registerObserver(IObserver *observer) {
        if (std::find(this->_observers.begin(), this->_observers.end(), observer) == this->_observers.end())
            this->_observers.push_back(observer);
    }
}
