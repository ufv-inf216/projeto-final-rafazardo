#include "Fade.h"
#include "../GameSpecific/MyGame.h"

#define CIRCLE_WIDTH 1098
#define CIRCLE_HEIGHT 1078

Fade::Fade(class MyGame *game, float duration):
    GameObject(game),
    mDuration(duration) {

    SDL_Rect *rect = new SDL_Rect;
    rect->x = 0; rect->y = 0;
    rect->w = 0; rect->h = 0;
    int color[4] {0, 0, 0, 0};

    mDrawRectComponent = new DrawRectComponent(this, rect, color, 10000);
    mDrawRectComponent->SetIsVisible(false);
    mTotalFaddingTime = 0;

    mFadeState = FadeState::None;
}

void Fade::In(std::vector<GameObject*> *keep_active, Vector2 pos) {
    mFadeState = FadeState::None;
    mFaddingIn = true;
    mFaddingOut = false;
    mGame->Pause(true);

    SetState(GameObjectState::Active);
    if(keep_active)
        for(auto go : *keep_active)
            go->SetState(GameObjectState::Active);

    mDrawRectComponent->SetRectDimension(mGame->GetWindowWidth(),mGame->GetWindowHeight());

    mDrawRectComponent->SetRectPosition(Vector2(0, 0));
    mDrawRectComponent->SetIsVisible(true);
}

void Fade::Out(bool resume) {
    mFadeState = FadeState::None;
    mFaddingIn = false;
    mFaddingOut = true;
    if(resume) mGame->Resume(true);
}

void Fade::OnUpdate(float deltaTime) {
    if(!mFaddingIn & !mFaddingOut) return;

    if(mFaddingIn) {
        mTotalFaddingTime += deltaTime;
        if(mTotalFaddingTime >= mDuration) {
            mTotalFaddingTime = 0;
            mFaddingIn = false;
            mDrawRectComponent->SetAlpha(255);
            mFadeState = FadeState::In;
            return;
        }
        mDrawRectComponent->SetAlpha((int)(255*(mTotalFaddingTime/mDuration)));

    } else if(mFaddingOut) {
        mTotalFaddingTime += deltaTime;
        if(mTotalFaddingTime >= mDuration) {
            mTotalFaddingTime = 0;
            mFaddingIn = false;
            mFaddingOut = false;
            mDrawRectComponent->SetIsVisible(false);
            mFadeState = FadeState::Out;
            SetState(GameObjectState::Paused);
            return;
        }
        mDrawRectComponent->SetAlpha((int)(255 - 255*(mTotalFaddingTime/mDuration)));
    }
}
