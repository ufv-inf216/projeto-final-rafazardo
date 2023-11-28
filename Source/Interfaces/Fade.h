//
// Created by andre on 26/11/2023.
//

#pragma once

#include "../GameObjects/GameObject.h"
#include "../Components/DrawComponents/DrawRectComponent.h"

class Fade : public GameObject {
    private:
        DrawRectComponent *mDrawRectComponent;

        float mDuration,
              mTotalFaddingTime;

        bool mFaddingIn  = false,
             mFaddingOut = false;

    public:
        Fade(class MyGame *game, float duration);

        void In(std::vector<GameObject*> *keep_active);
        void Out(bool resume=true);

        bool IsFadding() { return mFaddingIn | mFaddingOut; }
        bool IsFaddingIn() { return mFaddingIn; }
        bool IsFaddingOut() { return mFaddingOut; }

        void OnUpdate(float deltaTime) override;
};
