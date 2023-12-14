// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023.
// Room module for storing a room data.
// ----------------------------------------------------------------

#pragma once

#include "../Map.h"

enum class ConnectionSide {
    Top,
    Down,
    Right,
    Left
};

enum class RoomType {
    Teasure,
    Enemies
};

class Room : public Map {
    private:
        // The next rooms accessible from this one.
        std::vector<Room*> mConnectedRooms;
        Vector2 mDoorTop, mDoorRight,
                mDoorDown, mDoorLeft;

        // The areas where enemies can spawn.
        std::pair<Vector2, Vector2> mArea1, mArea2,
                                    mArea3, mArea4;

    public:
        // Constructor
        // @param game The current game
        // @params texturePath and collisionPath The map texture and colision directories
        // @params width and height The map dimensions
        Room(class MyGame *game, const std::string &jsonPath);
        Room(class MyGame *game, const std::string &jsonPath, int idx);

        // Connect a room to another (Note: this is a single-way connection)
        // @params other The other room to connect to this one
        void Connect(Room *other, ConnectionSide connection);

        Room* GetNextRoom(ConnectionSide side);
        Vector2 GetDoorPosition(ConnectionSide side);

        void Print();

        void Initialize(bool enable) override;
};
