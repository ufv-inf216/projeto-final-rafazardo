// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023.
// Dungeon module for storing a layer data.
// ----------------------------------------------------------------

#pragma once

#include "Room.h"

class Layer : public GameObject {
    private:
        // A pointer to the very first and final rooms of a dungeon layer.
        Room *mFirstRoom,
             *mLastRoom;

        // A pointer to the previous and next layers.
        Layer *mPreviousLayer,
              *mNextLayer;

    public:
        // Constructor
        // @param game The current game
        // @params first, last Pointer to the first and last dungeons rooms
        Layer(class MyGame *game, Layer *prev, Room *first, Room *last);

        // Getter for the next layer.
        // @return A pointer to the next layer.
        Layer* GetNext() { return mNextLayer; }

        // Getter for the previous layer.
        // @return A pointer to the previous layer.
        Layer* GetPrevious() { return mPreviousLayer; }

        Room* GetFirstRoom() { return mFirstRoom; }
};