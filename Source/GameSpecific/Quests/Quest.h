//
// Created by andre on 14/12/2023.
//

#pragma once

#include "../../GameObjects/GameObject.h"
#include "../../GameSpecific/Characters/NPC.h"

enum QuestType {
    KILL_N,
    GET_ITEM
};

enum QuestState {
    UNKOWN,
    NOT_FINISHED,
    DONE
};

class Quest : public GameObject{
    protected:
        QuestState mQuestState = UNKOWN;
        NPC *mNPC;

        std::string mDialogues[3];

    public:
        Quest(class MyGame *game, std::string dialogues[3]):
            GameObject(game) {

            mDialogues[0] = dialogues[0];
            mDialogues[1] = dialogues[1];
            mDialogues[2] = dialogues[2];

            mNPC->SetDialogue(mDialogues[0]);
        }

        void StartQuest() {
            mQuestState = NOT_FINISHED;
            mNPC->SetDialogue(mDialogues[1]);
        }

        void SetNPC(NPC *npc) { mNPC = npc; }
};
