//
// Created by vincy on 27/03/17.
//

#include "Evenement.hpp"

namespace arcade
{
  Evenement::Evenement(IEvenement::KeyCode keycode) : _keyCode(keycode),
						      _action(IEvenement::Action::Nothing),
						      _score(0)
  {  }

  Evenement::~Evenement()
  {}

  IEvenement::Action Evenement::getAction() const { return (_action); }
  IEvenement::KeyCode Evenement::getKeyCode() const { return (_keyCode); }
  uint64_t Evenement::getScore() const { return (_score);}

  void Evenement::setAction(const IEvenement::Action action) { _action = action; }
  void Evenement::setKeyCode(const IEvenement::KeyCode keyCode) { _keyCode = keyCode; }
  void Evenement::setScore(const uint64_t score) { _score = score; }
}