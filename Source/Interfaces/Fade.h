//
// Created by andre on 26/11/2023.
//

#pragma once

#include "../GameObjects/GameObject.h"
#include "../Components/DrawComponents/DrawRectComponent.h"

enum FadeState {
    In,
    Out,
    None
};

class Fade : public GameObject {
    private:
        DrawRectComponent *mDrawRectComponent;
        FadeState mFadeState;

        float mDuration,
              mTotalFaddingTime;

        bool mFaddingIn  = false,
             mFaddingOut = false;

    public:
        Fade(class MyGame *game, float duration);

        void In(std::vector<GameObject*> *keep_active, Vector2 pos=Vector2::Zero);
        void Out(bool resume=true);

        bool IsFadding() { return mFaddingIn | mFaddingOut; }
        bool IsFaddingIn() { return mFaddingIn; }
        bool IsFaddingOut() { return mFaddingOut; }

        void OnUpdate(float deltaTime) override;

        FadeState GetFadeState() { return mFadeState; }
};
