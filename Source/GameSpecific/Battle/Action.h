//
// Created by andre on 17/11/2023.
//

#pragma once
#include <string>

class Action {
    protected:
        // The action name.
        std::string mName;

        // The character in which the action will be used.
        class BattleCharacter *mTarget;

        // How the action will modify the target's life.
        int mDice, mNumRolls, mMod;

    public:
        Action(std::string name, class BattleCharacter *character, int attack_data[3]);
        Action() { }

        virtual void Apply(BattleCharacter *applier) { }
        void SetTarget(BattleCharacter *trgt) { mTarget = trgt; }
};

class Heal : public Action {
    private:
        int mPotionId;

    public:
        Heal(std::string name, class BattleCharacter *character, int attack_data[3], int id);

        void Apply(BattleCharacter *applier) override;

        int GetPotionId() { return mPotionId; }
};

class Attack : public Action {
    public:
        Attack(std::string name, class BattleCharacter *character, int attack_data[3]);
        Attack(): Action() { }

        void Apply(BattleCharacter *applier) override;
};
