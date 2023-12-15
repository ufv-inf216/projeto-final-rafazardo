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
#include "../../Characters/NPC.h"

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

        NPC *mNPC = nullptr;

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

        // Stops Genearting Outputs and Updating its GameObjects.
        void Disable() override {
            SetState(GameObjectState::Paused);
            mSpriteComponent->SetEnabled(false);
            mCollisionMatrixComponent->SetEnabled(false);
            for(auto obj : mGameObjects)
                if(obj) obj->Disable();
            if(mNPC) mNPC->Disable();
        }

        // Enable Outputs and GameObjects.
        void Enable(bool draw_only = false) override {
            if(!draw_only)
                SetState(GameObjectState::Active);

            mSpriteComponent->SetEnabled(true);
            mCollisionMatrixComponent->SetEnabled(true);
            for(auto obj : mGameObjects)
                if(obj) obj->Enable();
            if(mNPC) mNPC->Enable();
        }

        void AddNPC(NPC *npc) {
            mNPC = npc;
            mNPC->SetPosition(Vector2(24*9, 24*8));
            mNPC->Disable();
        }
};
