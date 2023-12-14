//
// Created by andre on 14/12/2023.
//

#pragma once

#include "Menu.h"

class CharacterCreationMenu : public Menu {
    private:
        int STR = 8, DEX = 8, CON = 8, SMA = 8, WIS = 8, CHA = 8;
        int TOTAL_POINTS = 12;

    public:
        CharacterCreationMenu(class MyGame *game):
            Menu(game, "") { }

        void OnProcessInput(const Uint8* state) override;

        void StartGame();
};
