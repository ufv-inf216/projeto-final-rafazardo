//
// Created by andre on 07/12/2023.
//

#pragma once

#include "../GameObjects/GameObject.h"
#include "../Components/DrawComponents/SpriteComponent.h"

class Mask : public GameObject {
    private:
        SpriteComponent *mSpriteComponent;

    public:
        Mask(class MyGame *game, const std::string path, int width, int height, int order):
            GameObject(game) {

            mSpriteComponent = new SpriteComponent(this, path, width, height, order);
        }
};
