//
// Created by vincy on 27/03/17.
//

#include "Evenement.hpp"

arcade::Evenement::Evenement(IEvenement::KeyCode keycode) : _keyCode(keycode),
															_action(IEvenement::Action::KeyPressDown),
															_score(0)
{  }

arcade::Evenement::~Evenement()
{}

arcade::IEvenement::Action arcade::Evenement::getAction() const { return (_action); }
arcade::IEvenement::KeyCode arcade::Evenement::getKeyCode() const { return (_keyCode); }
uint64_t arcade::Evenement::getScore() const { return (_score);}

void arcade::Evenement::setAction(const IEvenement::Action action) { _action = action; }
void arcade::Evenement::setKeyCode(const IEvenement::KeyCode keyCode) { _keyCode = keyCode; }
void arcade::Evenement::setScore(const uint64_t score) { _score = score; }

int32_t			arcade::Evenement::getData(void) const { return (0); }

