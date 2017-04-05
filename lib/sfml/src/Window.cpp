//
// Window.cpp for Project-Master in /home/peixot_b/Epitech/Tek2/CPP/Arcade/cpp_arcade/lib/sfml/src
// 
// Made by peixot_b
// Login   <benjamin.peixoto@epitech.eu>
// 
// Started on  Wed Mar 22 17:34:04 2017 peixot_b
// Last update Wed Apr  5 15:18:29 2017 Benjamin
//

#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Window.hpp"
#include "Object.hpp"


namespace arcade
{
    arcade::Window::Window(std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>>> &objects,
						   uint64_t height,
                           uint64_t width) : _size(1024, 1024), _isopen(false), _window(sf::VideoMode(1024, 1024),
                                                                                        "SFML works!",
                                                                                        sf::Style::Close |
                                                                                        sf::Style::Resize |
                                                                                        sf::Style::Titlebar),
                                             _objects(objects), _height(height), _width(width), _min_size(0, 0, 0)
    {
		std::cout << "init" << std::endl;
		_isopen = true;
	}

	arcade::Window::~Window() {
		std::cout << "Window supprimée" << std::endl;
		_isopen = false;
	}

	bool arcade::Window::isOpen() const { return (_isopen); }

	int32_t arcade::Window::getHeight() const { return (_height); }

	int32_t arcade::Window::getLenght() const { return (_width); }

	const sf::RenderWindow &arcade::Window::get_Window() const { return (_window); }

	const arcade::Vector3d &arcade::Window::getSize() const { return (_size); }

	void arcade::Window::setMapSize(uint32_t size)
	{
		_min_size.setX(size);
		_min_size.setY(size);
		_min_size.setZ(size * size);
	}

	bool arcade::Window::event() {
		while (_window.pollEvent(_event)) {
			switch (_event.type) {
				case sf::Event::Closed: // CHECK IF THE WINDOW IS CLOSED
				{
					_window.close();
					break;
				}

				case sf::Event::Resized: // CHECK WHEN THE WINDOW IS RESIZED BY USER
				{
					std::cout << "new width: " << _event.size.width << std::endl;
					std::cout << "new height: " << _event.size.height << std::endl;
					break;
				}

				case sf::Event::KeyPressed: // CHECK WHEN A KEY IS PRESSED
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
						std::cout << "The character is moving to left" << std::endl;
						// character.move(1, 0)
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
						sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
						std::cout << "The character is moving to Right" << std::endl;
						// character.move(1, 0);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
						std::cout << "The character is moving to Up" << std::endl;
						// character.move(1, 0);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
						std::cout << "The character is moving to Down" << std::endl;
						// character.move(1, 0)
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
						std::cout << "Previous Library" << std::endl;
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
						std::cout << "Next Library" << std::endl;
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
						std::cout << "Previous Game" << std::endl;
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
						std::cout << "Next Game" << std::endl;
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
						std::cout << "Restart the game" << std::endl;
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
						std::cout << "Return to the Menu" << std::endl;
					break;
				}

				default:
					break;
			}
		}
		return (false);
	}

	arcade::FrameType arcade::Window::refresh() {
		_height = _event.size.height;
		_width = _event.size.width;
		_window.clear();

		//for (auto obj : *_objects) A VOIR AVEC TIMOTHEE
		//_window.draw();

		_window.display();
		return (arcade::FrameType::GameFrame);
	}

	void arcade::Window::addObject(std::shared_ptr<arcade::IObject> &obj) {
		_objects->push_back(obj);
	}

	void arcade::Window::addObject(std::shared_ptr<arcade::IObject> &obj, const Vector3d &pos) {
		obj->setPosition(pos);
		addObject(obj);
	}

	void arcade::Window::moveObject(std::shared_ptr<arcade::IObject> &obj, const Vector3d &pos)
	{
		obj->setPosition(pos);
	}

	void arcade::Window::moveObject(std::string name, const Vector3d &pos) {
		for (auto it : *_objects)
			if (name == it->getName()) {
				it->setPosition(pos);
				return;
			}
	}

	void arcade::Window::destroyObject(std::shared_ptr<arcade::IObject> &obj) {
		auto it = _objects->begin();

		while (it != _objects->end()) {
			if (*it == obj) {
				_objects->erase(it);
				return;
			}
			++it;
		}
	}

	void arcade::Window::notify(const IEvenement &evenement) {
		for (auto it : _observers)
			it->getNotified(evenement);
	}

	std::shared_ptr<arcade::IEvenement> arcade::Window::getEvent() {
		return (std::shared_ptr<arcade::IEvenement>(NULL));
	}

	void arcade::Window::removeObserver(IObserver *observer) {
		auto it = _observers.begin();

		while (it != _observers.end()) {
			if (*it == observer) {
				_observers.erase(it);
				return;
			}
			++it;
		}
	}

	void arcade::Window::registerObserver(IObserver *observer) {
		_observers.push_back(observer);
	}
}
