//
// Created by vincent on 09/04/17.
//

#ifndef CPP_ARCADE_EVENEMENTGAME_HPP
#define CPP_ARCADE_EVENEMENTGAME_HPP

#include "IObserve.hpp"

namespace arcade {
  
  class EvenementGame : public IEvenement
  {
  public:
    EvenementGame(IEvenement::Action);
    virtual ~EvenementGame();

    virtual IEvenement::Action		getAction(void) const;
    virtual IEvenement::KeyCode		getKeyCode(void) const;
    virtual uint64_t			getScore(void) const;
    virtual int32_t			getData(void) const;

    void 					setAction(const IEvenement::Action);
    void 					setKeyCode(const IEvenement::KeyCode);
    void 					setScore(const uint64_t);

  private:
    IEvenement::KeyCode 			_keyCode;
    IEvenement::Action 			_action;
    uint64_t 				_score;

  };
};


#endif //CPP_ARCADE_EVENEMENTGAME_HPP
