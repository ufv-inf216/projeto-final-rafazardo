//
// Created by andre on 07/12/2023.
//

#pragma once
#include "../Enemy.h"

class Slime : public Enemy {
    public:
        Slime(class MyGame *game, const std::string &img_path, Vector2 img_dims, int attrs[6]):
            Enemy(game, "../Assets/Sprites/Enemies/Slime/slime_sprite.png",
                  "../Assets/Sprites/Enemies/Slime/sprite_sheet_data.json", img_path, img_dims, attrs, 0) {

            mAnimatedSpriteComponent->AddAnimation("idle", { 0 });
            mAnimatedSpriteComponent->SetAnimation("idle");
            mAnimatedSpriteComponent->SetAnimFPS(1.0f);
        }
};
