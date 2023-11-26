#include "Fade.h"
#include "../GameSpecific/MyGame.h"

#define CIRCLE_WIDTH 1098
#define CIRCLE_HEIGHT 1078

Fade::Fade(class MyGame *game, float duration):
    GameObject(game),
    mDuration(duration) {

    mCircleHeight = mGame->GetWindowHeight()/mGame->GetCamera()->GetScale();
    mCircleWidth = CIRCLE_WIDTH*((mGame->GetWindowHeight()/mGame->GetCamera()->GetScale())/CIRCLE_HEIGHT);
    mCircle = new SpriteComponent(this, "../Assets/Sprites/fade.png",
                                  mCircleWidth,mCircleHeight,1000);

    mCircle->SetIsVisible(false);
    mTotalFaddingTime = 0;
}

void Fade::In() {
    mFaddingIn = true;
    mFaddingOut = false;
    mGame->Pause(true);
    SetState(GameObjectState::Active);
    mCircle->SetIsVisible(true);

    auto diff = mGame->GetWindowWidth()-mGame->GetCamera()->GetScale()*mCircleWidth;
    mPosition = mGame->GetCamera()->GetPosition();
    mPosition.x += diff/(2.f*mGame->GetCamera()->GetScale());
}

void Fade::Out() {
    mFaddingIn = false;
    mFaddingOut = true;
    mGame->Resume(true);
}

void Fade::OnUpdate(float deltaTime) {
    if(!mFaddingIn & !mFaddingOut) return;

    if(mFaddingIn) {
        mTotalFaddingTime += deltaTime;
        if(mTotalFaddingTime >= mDuration) {
            mTotalFaddingTime = 0;
            mFaddingIn = false;
        }

        auto prev = mCircle->GetDimensions();
        float s = (mDuration-mTotalFaddingTime)/mDuration;
        mCircle->SetDimensions(mCircleWidth*s, mCircleHeight*s);
        auto new_dim = mCircle->GetDimensions();

        mPosition.x += (prev.x - new_dim.x)/mGame->GetCamera()->GetScale();
        mPosition.y += (prev.y - new_dim.y)/mGame->GetCamera()->GetScale();

    } else if(mFaddingOut) {
        mTotalFaddingTime += deltaTime;
        if(mTotalFaddingTime >= mDuration) {
            mTotalFaddingTime = 0;
            mFaddingIn = false;
        }

    }
}
