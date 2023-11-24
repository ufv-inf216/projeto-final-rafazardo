// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// ----------------------------------------------------------------

#include "Room.h"

#define TOP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

Room::Room(class MyGame *game) {
    mConnectedRooms.resize(4);
}

void Room::Connect(Room *other, ConnectionSide connection) {
    switch(connection) {
        case ConnectionSide::Top:
            mConnectedRooms[TOP] = other;
            break;
        case ConnectionSide::Down:
            mConnectedRooms[DOWN] = other;
            break;
        case ConnectionSide::Right:
            mConnectedRooms[RIGHT] = other;
            break;
        case ConnectionSide::Left:
            mConnectedRooms[LEFT] = other;
            break;
        default:
            break;
    }
}