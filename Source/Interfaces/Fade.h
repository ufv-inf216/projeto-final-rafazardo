//
// Created by andre on 26/11/2023.
//

#pragma once

#include "../GameObjects/GameObject.h"
#include "../Components/DrawComponents/SpriteComponent.h"

class Fade : public GameObject {
    private:

        float mDuration,
              mTotalFaddingTime;

        bool mFaddingIn  = false,
             mFaddingOut = false;

        SpriteComponent *mCircle;
        int mCircleWidth,
            mCircleHeight;

    public:
        Fade(class MyGame *game, float duration);

        void In();
        void Out();

        bool IsFadding() { return mFaddingIn | mFaddingOut; }

        void OnUpdate(float deltaTime) override;
};
