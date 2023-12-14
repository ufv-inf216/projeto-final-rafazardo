//
// Created by andre on 14/12/2023.
//

#include "MainMenu.h"
#include "../../GameSpecific/MyGame.h"

void MainMenu::StartNewGame() {
    mGame->GetCharacterCreationMenu()->Open();
    Close();
}