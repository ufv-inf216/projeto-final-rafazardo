//
// Created by andre on 14/12/2023.
//

#include "CharacterCreationMenu.h"
#include "../../GameSpecific/MyGame.h"
#include "SDL_ttf.h"

void CharacterCreationMenu::OnProcessInput(const Uint8 *state) {

}

void CharacterCreationMenu::StartGame() {
    int attrs[6] { STR, DEX, CON, SMA, WIS, CHA };
    mGame->GetPlayer()->SetCharacterSheet(attrs);
    mGame->GetPlayer()->SetMaxHP(10 + mGame->GetPlayer()->GetMod(2));
    Close();
}
