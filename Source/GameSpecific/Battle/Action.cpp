//
// Created by andre on 17/11/2023.
//

#include "Action.h"
#include "BattleCharacters/BattleCharacter.h"
#include "../../Game/Random.h"

// Default action
Action::Action(std::string name, class BattleCharacter *character, int attack_data[3]):
    mName(name),
    mTarget(character) {

    mDice = attack_data[0]; mNumRolls = attack_data[1]; mMod = attack_data[2];
}

// Healling actions.
Heal::Heal(std::string name, class BattleCharacter *character, int attack_data[3], int id):
    Action(name, character, attack_data),
    mPotionId(id) { }

void Heal::Apply(BattleCharacter *applier) {
    int delta_hp = 0;
    for(int i = 0; i < mNumRolls; i++)
        delta_hp += Random::GetIntRange(1, mDice);
    delta_hp += applier->GetCharacterSheet()->GetMod(mMod);

    mTarget->SetHP(std::max(mTarget->GetHP() + delta_hp, mTarget->GetMaxHP()));
    mTarget->GetCharacter()->GetInventory()->UpdateItems("potion", mPotionId, -1);

    if(mTarget->GetCharacter()->GetInventory()->GetItemAmount("potion", mPotionId) == 0)
        mTarget->RemoveHeal(mPotionId);
}

// Attacking actions.
Attack::Attack(std::string name, class BattleCharacter *character, int attack_data[3]):
    Action(name, character, attack_data) { }

void Attack::Apply(BattleCharacter *applier) {
    int delta_hp = 0;
    for(int i = 0; i < mNumRolls; i++)
        delta_hp += Random::GetIntRange(1, mDice);
    delta_hp += applier->GetCharacterSheet()->GetMod(mMod);

    SDL_Log("O mMod do venom %d", applier->GetCharacterSheet()->GetMod(mMod));

    mTarget->SetHP(mTarget->GetHP() - delta_hp);
}
