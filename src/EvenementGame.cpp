//
// Created by vincent on 09/04/17.
//

#include "EvenementGame.hpp"

arcade::EvenementGame::EvenementGame(IEvenement::KeyCode keycode)
	: _keyCode(keycode),
	  _action(IEvenement::Action::KeyPressDown),
	  _score(0)
{  }

arcade::EvenementGame::~EvenementGame()
{ }

arcade::IEvenement::Action 	arcade::EvenementGame::getAction() const { return (_action); }
arcade::IEvenement::KeyCode 	arcade::EvenementGame::getKeyCode() const { return (_keyCode); }
uint64_t 			arcade::EvenementGame::getScore() const { return (_score);}
int32_t				arcade::EvenementGame::getData(void) const { return (0); }

void 				arcade::EvenementGame::setAction(const IEvenement::Action action) { _action = action; }
void 				arcade::EvenementGame::setKeyCode(const IEvenement::KeyCode keyCode) { _keyCode = keyCode; }
void 				arcade::EvenementGame::setScore(const uint64_t score) { _score = score; }
