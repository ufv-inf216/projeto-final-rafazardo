
#include "InventoryHUD.h"
#include "../../GameSpecific/MyGame.h"

InventoryHUD::InventoryHUD(MyGame *myGame) : Interface(myGame) {
    mFrame = new SpriteComponent(this, "../Assets/Sprites/HUDs/InventoryHUD/inv_hud.png",
                                 167, 110);
    mFrame->SetOffset(Vector2(50, 50));
}

bool InventoryHUD::AddWeapon(int id, std::string txtDir) {

    for(int i=0; i<mWeaponIcons.size(); i++)
        if(!mWeaponIcons[i]) {
            mWeaponIcons[id] =new SpriteComponent(this, txtDir, 24, 24);
            return true;
        }

    return false;

}

void InventoryHUD::RemoveWeapon(int id) {

    mGame->RemoveDrawable(mWeaponIcons[id]);
    mWeaponIcons[id] = nullptr;

}

bool InventoryHUD::AddPotion(int id, std::string txtDir) {

    for(int i=0; i<mPotionIcons.size(); i++)
        if(!mPotionIcons[i]) {
            mPotionIcons[id] = new SpriteComponent(this, txtDir, 24, 24);
            return true;
        }

    return false;

}

void InventoryHUD::RemovePotion(int id) {

    mGame->RemoveDrawable(mPotionIcons[id]);
    mPotionIcons[id] = nullptr;

}