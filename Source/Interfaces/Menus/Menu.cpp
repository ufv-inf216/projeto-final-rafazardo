//
// Created by andre on 14/12/2023.
//

#include "Menu.h"
#include "../../GameSpecific/MyGame.h"

Menu::Menu(class MyGame *game, std::string path):
    GameObject(game) {

    mMenuSprite = new SpriteComponent(this, path);
    mMenuSprite->SetEnabled(false);
}

void Menu::Open() {
    mGame->Pause(false);
    mMenuSprite->SetEnabled(true);
}

void Menu::Close() {
    mGame->Resume(true);
    mMenuSprite->SetEnabled(false);
    SetState(GameObjectState::Destroy);
}