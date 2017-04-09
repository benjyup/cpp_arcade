//
// Created by vincent on 09/04/17.
//

#ifndef CPP_ARCADE_MAINOBSERVER_HPP
#define CPP_ARCADE_MAINOBSERVER_HPP

#include "IObserve.hpp"

namespace arcade
{
  class MainObserver : public IObserver
  {
   public:
    MainObserver();
    virtual ~MainObserver();

    virtual void getNotified(IEvenement const &);
  };
}

#endif //CPP_ARCADE_MAINOBSERVER_HPP
