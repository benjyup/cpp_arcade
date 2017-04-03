//
// Created by puente_t on 13/03/17.
//

#ifndef ARCADE_IOBSERVE_HPP
#define ARCADE_IOBSERVE_HPP

#include <cstdint>
#include <memory>
#include <algorithm>

namespace arcade
{
  //
  //		IEvenement System for keyboard entry
  //

  class IEvenement
  {
   public:

    //
    //		Enum listing the possible event
    //

    enum class Action : uint8_t
    {
      Nothing = 0,
      KeyPressDown,
      KeyRelease,
      LoadGame
    };

    //
    //		Enum listing all the possible binding
    //

    enum class KeyCode : char
    {
      Key_Undefined = 0,
      Key_ENTER,
      Key_UP,
      Key_DOWN,
      Key_LEFT,
      Key_RIGHT,
      Key_F1,
      Key_F2,
      Key_F3,
      Key_F4,
      Key_F5,
      Key_F6,
      Key_F7,
      Key_F8,
      Key_F9,
      Key_F10,
      Key_CAPSLOCK,
      Key_SHIFT,
      Key_A = 'a',
      Key_D = 'd',
      Key_Q = 'q',
      Key_S = 's',
      Key_Z = 'z',
      Key_1 = '1',
      Key_2 = '2',
      Key_3 = '3',
      Key_4 = '4',
      Key_5 = '5',
      Key_6 = '6',
      Key_7 = '7',
      Key_8 = '8',
      Key_9 = '9'
    };

    virtual ~IEvenement(void)
    {};

    //
    //		Getters
    //

    virtual IEvenement::Action		getAction(void) const = 0;
    virtual IEvenement::KeyCode		getKeyCode(void) const = 0;
    virtual int32_t			getData(void) const = 0;
  };

  //
  // 		Primitive Observer / Observed system
  //

  //	Predeclaration

  class IObserved;

  class IObserver
  {
   public:
    virtual ~IObserver(void)
    {};

    //
    //		Function to call when Observer have to be notify by Observed
    // 			(called by arcade::IObserved::notify)
    //

    virtual void getNotified(IEvenement const &) = 0;
  };

  class IObserved
  {
   protected:

    //
    //		Function notify all the Observer of a event
    // 			(call arcade::IObserver::getNotified)
    //

    virtual void notify(IEvenement const &) = 0;

   public:
    virtual ~IObserved(void)
    {};

    //
    //		Function to call if a observer need to forcelly get the event
    //

    virtual std::shared_ptr<IEvenement> getEvent(void) = 0;

    //
    //		Add a observer from observer vector
    //

    virtual void registerObserver(arcade::IObserver*) = 0;

    //
    //		Remove a observer from observer vector
    //

    virtual void removeObserver(arcade::IObserver*) = 0;
  };
}
#endif //ARCADE_IOBSERVE_HPP
