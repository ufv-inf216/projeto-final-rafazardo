#include "../../../GameObjects/GameObject.h"
#include "../../../Components/DrawComponents/SpriteComponent.h"

#pragma once

class PressSpaceHUD : public GameObject {
    private:
        SpriteComponent *mHUD;

    public:
        PressSpaceHUD(class MyGame *game):
            GameObject(game) {

            mHUD = new SpriteComponent(this, "../Assets/Sprites/HUDs/GameHUD/press_space.png",
                                       95, 23, 1000);
            mHUD->SetIsVisible(false);
        }

        void MakeVisible() {
            mHUD->SetIsVisible(true);
            SetPosition(Vector2(0, 0));
            mHUD->SetOffset(mGame->GetCamera()->GetPosition() +
                            Vector2(mGame->GetWindowWidth()/8 - 48,
                                    mGame->GetWindowHeight()/4 - 35));
            // mHUD->SetOffset(mGame->GetCamera()->GetPosition());
        }

        void Hide() {
            mHUD->SetIsVisible(false);
        }
};
