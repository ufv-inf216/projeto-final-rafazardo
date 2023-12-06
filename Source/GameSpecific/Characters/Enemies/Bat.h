// -----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// Bat module for implementing specific enemy characteristics
// -----------------------------------------------------------------

#pragma once

#include "../Enemy.h"
#include "../../../Components/AIComponents/FSMComponent.h"

class Bat : public Enemy {
public:
    Bat(class MyGame *game, int atributes[]);
private:
    FSMComponent *mFSMComponent;
};