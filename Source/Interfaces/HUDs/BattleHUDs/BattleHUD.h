

#include "../../Interface.h"
#include "./HPBarBattleHUD.h"
#include "./ActionSelectorBattleHUD.h"
#include "./ItemSelectorBattleHUD.h"
#pragma once

class BattleHUD : public Interface {
    private:
        HPBarBattleHUD *mHPBarBattleHud;
        ActionSelectorBattleHUD *mActionSelectorBattleHUD;
        ItemSelectorBattleHUD *mItemSelectorBattleHUD;

    public:
        BattleHUD(MyGame *myGame, Battle *battle);
};
