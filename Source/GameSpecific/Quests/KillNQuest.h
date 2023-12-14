//
// Created by andre on 14/12/2023.
//

#pragma once

#include "Quest.h"
#include "../../Game/Global.h"

class KillNQuest : public Quest {
    private:
        int mObjective,
            mEnemyIndex;

    public:
        KillNQuest(class MyGame *game, std::string dialogues[3], int enemy, int obj):
            Quest(game, dialogues), mObjective(obj), mEnemyIndex(enemy) { }

        void OnUpdate(float deltaTime) override {
            if(mQuestState != NOT_FINISHED) return;

            if(GLOBAL_TotalEnemiesKilled[mEnemyIndex] == mObjective) {
                mQuestState = DONE;
                mNPC->SetDialogue(mDialogues[2]);
            }
        }
};
