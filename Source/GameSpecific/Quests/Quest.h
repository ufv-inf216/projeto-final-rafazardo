//
// Created by andre on 14/12/2023.
//

#pragma once

#include "../../GameObjects/GameObject.h"
#include "../../GameSpecific/Characters/NPC.h"
#include "../MyGame.h"

class Quest : public GameObject{
    protected:
        int mObjective = 5,
            mEnemyIndex = 1;
        NPC *mNPC;

        bool mIsDone = false;

        SpriteComponent *mFrame;

    public:
        Quest(class MyGame *game, const std::string &frameDir):
            GameObject(game) {

            mFrame = new SpriteComponent(this, frameDir, 202, 45);
            mFrame->SetEnabled(false);
        }

        void SetNPC(NPC *npc) { mNPC = npc; }

        void OnUpdate(float deltaTime) override {
            if(GLOBAL_TotalEnemiesKilled[mEnemyIndex] == mObjective) {
                mIsDone = true;
            }
        }

        void Open() {
            SetPosition(mGame->GetCamera()->GetPosition());
            mFrame->SetOffset(Vector2(35, 125));

            mFrame->SetEnabled(true);
            mGame->GetCamera()->Disable();
            mGame->GetPlayer()->Disable();
            mGame->GetPlayer()->Enable(true);
        }

        void Close() {
            mGame->GetCamera()->Enable();
            mGame->GetPlayer()->Enable();
            mFrame->SetEnabled(false);
        }

        bool IsDone() { return  mIsDone; }
};
