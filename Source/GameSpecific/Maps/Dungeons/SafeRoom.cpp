//
// Created by andre on 14/12/2023.
//

#include "SafeRoom.h"

void SafeRoom::Initialize(bool enable) {
    int a[6] = {0, 0, 0, 0, 0, 0};
    mNPC = new NPC(mGame, "", "", a);
    mNPC->SetQuest(GLOBAL_GenerateRandomQuest(mGame));
    mChest = GLOBAL_GenerateRandomChest();
}