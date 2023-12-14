//
// Created by andre on 14/12/2023.
//

#pragma once

#include "Quest.h"

class GetItemQuest : public Quest {
    public:
        GetItemQuest(class MyGame *game, std::string dialogues[3]):
            Quest(game, dialogues) { }
};
