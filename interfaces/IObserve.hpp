//
// Created by puente_t on 13/03/17.
//

#ifndef ARCADE_IOBSERVE_HPP
#define ARCADE_IOBSERVE_HPP

#include <cstdint>

//
// Basic Evenement System
//

namespace arcade
{
  class 	IEvenement
  {
  public:
    enum class Action: uint8_t
    {
      Nothing = 0,
	KeyPressDown,
	KeyRelease
	};

    enum class KeyCode : char
    {
      Key_A = 'a',
	Key_D = 'd',
	Key_Q = 'q',
	Key_S = 's',
	Key_Z = 'z',
	Key_Undefined = 0
	};

    virtual ~IEvenement() {};
    virtual IEvenement::Action	getAction() const = 0;
    virtual IEvenement::KeyCode	getKeyCode() const = 0;
  };

// Basic Observer/Observed

class 	IObserved;

class 	IObserver
{
 public:
  virtual ~IObserver() {};

  virtual void 			getNotified(IEvenement const &) = 0;
};

class 	IObserved
{
 protected:
  virtual void			notify(IEvenement const &) = 0;
 public:
  virtual ~IObserved() {};

  virtual IEvenement *		getEvent() = 0;
  virtual void 			removeObserver(IObserver *) = 0;
  virtual void 			registerObserver(IObserver *) = 0;
};
}
#endif //ARCADE_IOBSERVE_HPP
