// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// Camera module for defining the rendering area during gameplay.
// ----------------------------------------------------------------

#pragma once

#include "GameObject.h"
#include "../Interfaces/Mask.h"

class Camera : public GameObject {
    private:
        // Render Scale
        float mScale;

        // Camera's important points
        Vector2 mCenter,
                mMinPosition,
                mMaxPosition;

        // Offset
        int mHalfWindowWidth,
            mHalfWindowHeight;

        Mask *mMask = nullptr;
        int mMaskWidth, mMaskHeight;

        // A Target which the camera will follow
        GameObject *mTarget;

    public:
        // Constructor
        // @param game The current game
        // @paramss min and max The min and max vertices os rendering rectangle
        // @param scale The scale for rendering
        Camera(class MyGame* game, const Vector2 &min, const Vector2 &max, float scale);

        // Defines a target to the camera
        // @param target The target
        // @param offset A offset from the target for the camera follows
        void SetTarget(class GameObject *target, const Vector2 &offset = Vector2(0, 0));

        // Define the window area
        // @param width and height The width and height of the window
        void SetWindow(int width, int height);

        Vector2 GetCenter() { return mCenter; }

        void SetScale(float scale);
        float GetScale() { return mScale; }

        void SetMask(const std::string &maskPath, int width, int height, int order) {
            mMask = new Mask(mGame, maskPath, width, height, order);
            mMaskWidth = width; mMaskHeight = height;
        }
        Mask *GetMask() { return mMask; }

        void OnUpdate(float deltaTime) override;
};