
#pragma once

#include "../../Interface.h"
#include "./HPBarBattleHUD.h"
#include "./ActionSelectorBattleHUD.h"
#include "./ItemSelectorBattleHUD.h"
#include "./EnemySelectorBattleHUD.h"

class BattleHUD : public Interface {
    private:
        HPBarBattleHUD *mHPBarBattleHud;
        ActionSelectorBattleHUD *mActionSelectorBattleHUD;
        ItemSelectorBattleHUD *mItemSelectorBattleHUD;
        EnemySelectorBattleHUD *mEnemySelectorBattleHUD;

    public:
        BattleHUD(MyGame *myGame, Battle *battle);
};
