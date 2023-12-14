//
// Created by andre on 14/12/2023.
//

#pragma once

#include "Room.h"
#include "../../Characters/NPC.h"
#include "../../Chest.h"

class SafeRoom : public Room {
    public:
        NPC *mNPC;
        Chest *mChest;

    private:
        SafeRoom(class MyGame *game, const std::string &jsonPath):
            Room(game, jsonPath) { }

        void Initialize(bool enable) override;
};
