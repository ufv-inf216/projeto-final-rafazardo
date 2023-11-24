// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023.
// Dungeon module for storing a dungeon data.
// ----------------------------------------------------------------

#pragma once

#include "Layer.h"

class Dungeon : public GameObject {
    private:
        // A pointer to the very first and final layer of a dungeon.
        Layer *mFirstLayer,
              *mLastLayer;

    public:
        // Constructor
        // @param game The current game
        // @params first, last Pointer to the first and last dungeons layers
        Dungeon(class MyGame *game, Layer *first, Layer *last);

        // Getter for the first layer.
        // @returns A pointer to the first layer.
        Layer* GetFirstLayer() { return mFirstLayer; }

        // Getter for the last layer.
        // @returns A pointer to the last layer.
        Layer* GetLastLayer() { return mFirstLayer; }
};
