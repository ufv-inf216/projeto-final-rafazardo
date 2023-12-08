

#include "../../Interface.h"
#include "./HPBarBattleHUD.h"
#include "./ActionSelectorBattleHUD.h"
#pragma once

class BattleHUD : public Interface {
    private:
        HPBarBattleHUD *mHPBarBattleHud;
        ActionSelectorBattleHUD *mActionSelectorBattleHUD;

    public:
        BattleHUD(MyGame *myGame, Battle *battle);
};
