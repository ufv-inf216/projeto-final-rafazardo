//
// Created by andre on 14/12/2023.
//

#pragma once

#include "Menu.h"

class GameOverScreen : public Menu {
    public:
        GameOverScreen(class MyGame *game);

        void OnProcessInput(const Uint8 *state) override;
};
