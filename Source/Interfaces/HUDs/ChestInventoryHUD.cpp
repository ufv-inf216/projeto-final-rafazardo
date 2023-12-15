//
// Created by andre on 15/12/2023.
//

#include "ChestInventoryHUD.h"

ChestInventoryHUD::ChestInventoryHUD(MyGame *myGame) : Interface(myGame) {
    mFrame = new SpriteComponent(this, "../Assets/Sprites/HUDs/InventoryHUD/inv_hud.png",
                                 167, 110);
    mFrame->SetOffset(Vector2(50, 50));
}