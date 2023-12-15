#pragma once

#include <vector>
#include "../Interface.h"
#include "../../Components/DrawComponents/SpriteComponent.h"

class ChestInventoryHUD : public Interface {
    private:
        std::vector<SpriteComponent*> mWeaponIcons = std::vector<SpriteComponent*>(3, nullptr);
        std::vector<SpriteComponent*> mPotionIcons = std::vector<SpriteComponent*>(3, nullptr);
        SpriteComponent *mFrame;

    public:
        ChestInventoryHUD(MyGame *myGame);

        bool AddWeapon(int id, std::string txtDir);
        void RemoveWeapon(int id);

        bool AddPotion(int id, std::string txtDir);
        void RemovePotion(int id);
};
