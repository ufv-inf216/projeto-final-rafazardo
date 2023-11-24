//
// Created by andre on 17/11/2023.
//

#include "Action.h"
#include "BattleCharacters/BattleCharacter.h"

Action::Action(std::string name, class BattleCharacter *character, int delta_hp):
    mName(name),
    mTarget(character),
    mDeltaHP(delta_hp) { }

void Action::Apply() {
    mTarget->SetHP(mTarget->GetHP() + mDeltaHP);
}


Heal::Heal(std::string name, class BattleCharacter *character, int delta_hp, int id):
    Action(name, character, delta_hp),
    mPotionId(id) { }

void Heal::Apply() {
    mTarget->SetHP(mTarget->GetHP() + mDeltaHP);
    mTarget->GetCharacter()->GetInventory()->UpdateItems("potion", mPotionId, -1);

    if(mTarget->GetCharacter()->GetInventory()->GetItemAmount("potion", mPotionId) == 0)
        mTarget->RemoveHeal(mPotionId);
}

Attack::Attack(std::string name, class BattleCharacter *character, int delta_hp):
    Action(name, character, delta_hp) { }

Spell::Spell(std::string name, class BattleCharacter *character, int delta_hp):
    Action(name, character, delta_hp) { }