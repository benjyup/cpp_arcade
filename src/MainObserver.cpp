//
// Created by vincent on 09/04/17.
//

#include "MainObserver.hpp"

arcade::MainObserver::MainObserver() { }

arcade::MainObserver::~MainObserver() { }


void arcade::MainObserver::getNotified(IEvenement const &event) {


    if (event.getAction() == arcade::IEvenement::Action::LoadGame)
        reloadMenu();
}

void        arcade::reloadMenu