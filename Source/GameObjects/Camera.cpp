//
// Created by andre on 13/10/2023.
//

#include "Camera.h"
#include "../GameSpecific/MyGame.h"
#include <cmath>

Camera::Camera(class MyGame* game, const Vector2 &min, const Vector2 &max, float scale):
    GameObject(game),
    mMinPosition(min), mMaxPosition(max),
    mScale(scale) {
    SetScale(scale);
}

void Camera::SetTarget(class GameObject *target, const Vector2 &offset) {
    mTarget = target;
    mCenter = target->GetPosition() + offset;
    mPosition = mCenter - Vector2(mGame->GetWindowWidth()/(2*mScale), mGame->GetWindowHeight()/(2*mScale));
}

void Camera::OnUpdate(float deltaTime) {
    Vector2 tgtPosition = mTarget->GetPosition();

    if(tgtPosition.x < (mCenter.x-mHalfWindowWidth)) {
        float dist = mCenter.x-mHalfWindowWidth-tgtPosition.x;
        mPosition.x -= dist;
        mCenter.x -= dist;
    }
    else if(tgtPosition.x > (mCenter.x+mHalfWindowWidth)) {
        float dist = tgtPosition.x-mCenter.x-mHalfWindowWidth;
        mPosition.x += dist;
        mCenter.x += dist;
    }
    else if(tgtPosition.y < (mCenter.y-mHalfWindowHeight)) {
        float dist = mCenter.y-mHalfWindowHeight-tgtPosition.y;
        mPosition.y -= dist;
        mCenter.y -= dist;
    }
    else if(tgtPosition.y > (mCenter.y+mHalfWindowHeight)) {
        float dist = tgtPosition.y-mCenter.y-mHalfWindowHeight;
        mPosition.y += dist;
        mCenter.y += dist;
    }
}

void Camera::SetWindow(int width, int height) {
    mHalfWindowWidth = width/2;
    mHalfWindowHeight = height/2;
}

void Camera::SetScale(float scale) {
    SDL_RenderSetScale(mGame->GetRenderer(), scale, scale);
}