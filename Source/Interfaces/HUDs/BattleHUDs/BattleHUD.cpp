

#include "BattleHUD.h"
#include "../../../GameSpecific/Battle/Battle.h"

BattleHUD::BattleHUD(MyGame *myGame, Battle *battle): Interface(myGame) {

    mHPBarBattleHud = new HPBarBattleHUD(myGame, battle->GetPlayer());
    mActionSelectorBattleHUD = new ActionSelectorBattleHUD(myGame);
    mItemSelectorBattleHUD = new ItemSelectorBattleHUD(myGame, battle->GetPlayer());
}

