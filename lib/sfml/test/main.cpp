//
// main.cpp for Project-Master in /home/peixot_b/Epitech/Tek2/CPP/Arcade/arcade
// 
// Made by peixot_b
// Login   <benjamin.peixoto@epitech.eu>
// 
// Started on  Fri Mar 17 11:18:48 2017 peixot_b
// Last update Sun Mar 26 17:05:32 2017 peixot_b
//

#include <string>
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

int main()
{
  sf::RenderWindow window(sf::VideoMode(1024, 1024), "SFML works!", sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar);
  sf::Event event;

  sf::Texture	planche;
  sf::Texture	pac;
  sf::Sprite	pacman;
  sf::Sprite	sprite;
  sf::Font	font;
  sf::Text	text;


  std::ostringstream ss;
  std::string s;

  sf::Clock clock; // démarre le chrono
  sf::Time elapsed1 = clock.getElapsedTime();
  
  
  if (!font.loadFromFile("crackman.ttf"))
    std::cout << "cannot use the font" << std::endl;
  text.setFont(font);
  text.setCharacterSize(24);
  text.setFillColor(sf::Color::Black);
  
  
  if (!planche.loadFromFile("./pacman.minimap.jpg"))
    std::cout << "unable to upload the texture" << std::endl;
  if (!pac.loadFromFile("./pacman.png"))
    std::cout << "unable to upload the texture" << std::endl;
  planche.setSmooth(true);
  //planche.setRepeated(true);

  pac.setSmooth(true);
  //pac.setRepeated(true);


  pacman.setTexture(pac);
  //pacman.setTextureRect(sf::IntRect(25, 25, 100, 100));
  pacman.setOrigin(sf::Vector2f(25, 25));
  pacman.setPosition(sf::Vector2f(25, 25));

  sprite.setTexture(planche);
  //sprite.setTextureRect(sf::IntRect(10, 10, 10000, 10000));
  //sprite.scale(sf::Vector2f(0.1f, 0.1f)); // facters d'échelle relatifs à l'échelle actuelle


  while (window.isOpen())
    {

      elapsed1 = clock.getElapsedTime();
      ss.str("");
      ss << elapsed1.asSeconds();
      s = "";
      s = ss.str();
      text.setString(s);
      text.setPosition(sf::Vector2f(680, 0));
      
      while (window.pollEvent(event))
	{
	  
	  switch (event.type)
	    {
	      
	      // CHECK IF WINDOW IS CLOSED
	    case sf::Event::Closed:
	      window.close();
	      break;

	      // CHECK IF WINDOW IS RESIZED
	    case sf::Event::Resized:
	      std::cout << "new width: " << event.size.width << std::endl;
	      std::cout << "new height: " << event.size.height << std::endl;
	      break;
	      
	      // CHECK WHEN WINDOW NOT VISIBLE
	    case sf::Event::LostFocus:
	      // PAUSE MY GAME
	      std::cout << "PAUSE" << std::endl;
	      break;
	      
	      // CHECK WHEN WINDOW IS NOW VISIBLE
	    case sf::Event::GainedFocus:
	      // RESUME MY GAME
	      std::cout << "RESUME" << std::endl;
	      break;
	      
	      // CHECK WHEN A TEXT IS ENTERED
	    case sf::Event::TextEntered:
	      if (event.text.unicode < 128 && event.text.unicode >= 33)
		std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
	      break;

	      // CHECK WHEN A KEY IS PRESSED
	    case sf::Event::KeyPressed: // OR KeyReleased
	      if (event.key.code == sf::Keyboard::Escape)
		std::cout << "the escape key was pressed" << std::endl;
	      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
		  std::cout << "The character is moving to left" << std::endl;
		  // character.move(1, 0);
		  pacman.setRotation(180);
		  pacman.move(sf::Vector2f(-3, 0)); // décalage relatif à la position actuelle
		
		}
	      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
		  pacman.setRotation(0);
		  std::cout << "The character is moving to Right" << std::endl;
		  // character.move(1, 0);

		  pacman.move(sf::Vector2f(3, 0)); // décalage relatif à la position actuelle
		}
	      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
		  std::cout << "The character is moving to Up" << std::endl;
		  // character.move(1, 0);
		  pacman.setRotation(270);
		  pacman.move(sf::Vector2f(0, -3)); // décalage relatif à la position actuelle
		
		}
	      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
		  std::cout << "The character is moving to Down" << std::endl;
		  // character.move(1, 0);
		  pacman.setRotation(90);
		  pacman.move(sf::Vector2f(0, 3)); // décalage relatif à la position actuelle
		
		}

	      break;

	      // CHECK WHEN THE MOUSE WHEEL IS MOVING
	    case sf::Event::MouseWheelScrolled:
	      if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
		std::cout << "wheel type: vertical" << std::endl;
	      else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
		std::cout << "wheel type: horizontal" << std::endl;
	      else
		std::cout << "wheel type: unknown" << std::endl;
	      std::cout << "wheel movement: " << event.mouseWheelScroll.delta << std::endl;
	      std::cout << "mouse x: " << event.mouseWheelScroll.x << std::endl;
	      std::cout << "mouse y: " << event.mouseWheelScroll.y << std::endl;
	      break;

	      // CHECK THE BUTTON MOUSE IS PRESSED
	    case sf::Event::MouseButtonPressed:
	      if (event.mouseButton.button == sf::Mouse::Right)
		{
		  std::cout << "the right button was pressed" << std::endl;
		  std::cout << "mouse x: " << event.mouseButton.x << std::endl;
		  std::cout << "mouse y: " << event.mouseButton.y << std::endl;
		}
	      else if (event.mouseButton.button == sf::Mouse::Left)
		{
		  std::cout << "the left button was pressed" << std::endl;
		  std::cout << "mouse x: " << event.mouseButton.x << std::endl;
		  std::cout << "mouse y: " << event.mouseButton.y << std::endl;
		}

	      if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
		  // le bouton gauche est enfoncé : on tire
		  //gun.fire();
		}
	      break;

	      // CHECK WHEN THE MOUSE IS MOVING
	    case sf::Event::MouseMoved:
	      std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
	      std::cout << "new mouse y: " << event.mouseMove.y << std::endl;
	      break;

	      // CHECK WHEN THE MOUSE ENTERED OR LEFT THE WINDOW
	    case sf::Event::MouseEntered:
	      std::cout << "The mouse has entered to the window" << std::endl;
	      break;
	    case sf::Event::MouseLeft:
	      std::cout << "The mouse has left to the window" << std::endl;
	      break;
	      
	    default:
	      break;
	    }
	}
      window.clear(sf::Color::Black);
      window.draw(sprite);
      window.draw(pacman);
      window.draw(text);
      window.display();
    }
  return EXIT_SUCCESS;
}
