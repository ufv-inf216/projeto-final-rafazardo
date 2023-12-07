// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// ----------------------------------------------------------------

#include "Dungeon.h"

Dungeon::Dungeon(class MyGame *game, Layer *first, Layer *last):
    GameObject(game) {

    mFirstLayer = first;
    mLastLayer = last;
}