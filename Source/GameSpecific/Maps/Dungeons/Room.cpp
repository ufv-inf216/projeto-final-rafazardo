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

Room::Room(class MyGame *game, const std::string &texturePath, const std::string &collisionPath, int width, int height)
        : Map(game, texturePath, collisionPath, width, height) {
    mConnectedRooms = { nullptr, nullptr, nullptr, nullptr };
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

Room *Room::GetNextRoom(ConnectionSide side) {
    switch(side) {
        case ConnectionSide::Top:
            return mConnectedRooms[TOP];
        case ConnectionSide::Down:
            return mConnectedRooms[DOWN];
        case ConnectionSide::Right:
            return mConnectedRooms[RIGHT];
        case ConnectionSide::Left:
            return mConnectedRooms[LEFT];
    }
}

void Room::Print() {

    int cnt = 0;
    for(auto room : mConnectedRooms) {
        if(room)
            cnt++;
    }
    SDL_Log("Room: %d", cnt);
}