// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// ----------------------------------------------------------------

#include "Layer.h"

Layer::Layer(class MyGame *game, Layer* prev, Room *first, Room *last):
    GameObject(game),
    mFirstRoom(first),
    mLastRoom(last),
    mNextLayer(nullptr) {

    mPreviousLayer = prev;
}