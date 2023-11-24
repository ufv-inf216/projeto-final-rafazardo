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
        int mDeltaHP;

    public:
        Action(std::string name, class BattleCharacter *character, int delta_hp);

        virtual void Apply();
};

class Heal : public Action {
    private:
        int mPotionId;

    public:
        Heal(std::string name, class BattleCharacter *character, int delta_hp, int id);

        void Apply() override;

        int GetPotionId() { return mPotionId; }
};

class Attack : public Action {
    public:
        Attack(std::string name, class BattleCharacter *character, int delta_hp);
};

class Spell : public Action {
    public:
        Spell(std::string name, class BattleCharacter *character, int delta_hp);
};
