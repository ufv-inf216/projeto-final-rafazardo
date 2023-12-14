//
// Created by andre on 14/12/2023.
//

#pragma once

#include "../../GameObjects/GameObject.h"
#include "../../Components/DrawComponents/SpriteComponent.h"

class Menu : public GameObject {
    private:
        SpriteComponent *mMenuSprite;

    public:
        Menu(class MyGame *game, std::string path);

        virtual void Open();
        virtual void Close();
};
