//
// Created by andre on 14/12/2023.
//

#pragma once

#include "Menu.h"

class MainMenu : public Menu {
    public:
        MainMenu(class MyGame *game):
            Menu(game, "") { }

        void StartNewGame();
};
