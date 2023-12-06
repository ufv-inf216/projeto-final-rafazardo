//
// Created by Lucas N. Ferreira on 28/09/23.
//

#include "AnimatedSpriteComponent.h"
#include "../../GameObjects/GameObject.h"
#include "../../GameSpecific/MyGame.h"
#include "../../Game/Json.h"
#include <fstream>

AnimatedSpriteComponent::AnimatedSpriteComponent(class GameObject* owner, const std::string &spriteSheetPath, const std::string &spriteSheetData, int drawOrder)
        : SpriteComponent(owner, spriteSheetPath, 0, 0, drawOrder)
{
    LoadSpriteSheet(spriteSheetPath, spriteSheetData);
}

AnimatedSpriteComponent::~AnimatedSpriteComponent()
{
    for (const auto& rect : mSpriteSheetData)
    {
        delete rect;
    }
    mSpriteSheetData.clear();
}

void AnimatedSpriteComponent::LoadSpriteSheet(const std::string& texturePath, const std::string& dataPath)
{
    // Load sprite sheet texture
    mSpriteSheetSurface = mOwner->GetGame()->LoadTexture(texturePath);
    if(!mSpriteSheetSurface) SDL_Log("Couldn't open Sprite Sheet");

    // Load sprite sheet data
    std::ifstream spriteSheetFile(dataPath);
    nlohmann::json spriteSheetData = nlohmann::json::parse(spriteSheetFile);

    SDL_Rect* rect = nullptr;
    for(const auto& frame : spriteSheetData["frames"]) {

        int x = frame["frame"]["x"].get<int>();
        int y = frame["frame"]["y"].get<int>();
        int w = frame["frame"]["w"].get<int>();
        int h = frame["frame"]["h"].get<int>();
        rect = new SDL_Rect({x, y, w, h});

        mSpriteSheetData.emplace_back(rect);
    }
}

void AnimatedSpriteComponent::Draw(SDL_Renderer *renderer) {
    // TODO 2.1 (1 linha): Todos os quadros desse objeto estão armazenados no vetor
    //  `mSpriteSheetData`. Cada posição desse vetor é um ponteiro para um SDL_Rect*, representando as coordenadas
    //  de um sprite no sprite sheet. Além disso, todas as animações estão armazenadas no mapa `mAnimations`.
    //  Uma animação é identificada por um nome (string) e definida por um vetor de índices de quadros
    //  (armazenados em mSpriteSheetData). A animação corrente é armazenada na variável membro `mAnimName`.
    //  Sempre que um objeto com o componente AnimatedSpriteComponent é desenhado na tela,
    //  precisamos obter o índice do quadro corrente a partir do timer da animação. Para isso,
    //  basta converter o timer da animação (`mAnimTimer`) para inteiro. Obtenha o índice do quadro corrente
    //  indexando o mapa ` mAnimations` com o timer da animação (`mAnimTimer`) convertido para inteiro.
    //  Note que `mAnimations[mAnimName]` armazena os índices dos quadros da animação atual. Armazene
    //  o resultado em uma variável `spriteIdx`.
    int spriteIdx = this->mAnimations[mAnimName][(int)this->mAnimTimer];

    // TODO 2.2 (~8 linhas): Utilize a função SDL_RenderCopyEx para desenhar o sprite
    //  com índice `spriteIdx`. O SDLRect que define a região do sprite no sprite sheet está armazenado
    //  em `mSpriteSheetData[spriteIdx]`. Além disso, você terá que criar um SDL_Rect para definir a região
    //  da tela onde será desenhado o sprite, assim como no `SpriteComponent`. Você também terá que
    //  criar uma flag do tipo SDL_RendererFlip assim como no SpriteComponent.
    Vector2 pos = mOwner->GetPosition();
    Vector2 cam_pos = this->mOwner->GetGame()->GetCamera()->GetPosition();

    SDL_Rect dstrect;
    dstrect.w = 24; dstrect.h = 24;
    dstrect.x = pos.x-cam_pos.x; dstrect.y = pos.y-cam_pos.y;

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if(this->mOwner->GetRotation() == Math::Pi)
        flip = SDL_FLIP_HORIZONTAL;

    SDL_RenderCopyEx(renderer, this->mSpriteSheetSurface, mSpriteSheetData[spriteIdx], &dstrect,
                     .0f, nullptr, flip);
}

void AnimatedSpriteComponent::Update(float deltaTime) {
    // TODO 1.1 (~2 linhas): Verifique se animação está pausada (`mIsPaused`). Se estiver, saia da função (return).
    if(this->mIsPaused) return;

    // TODO 1.2 (~1 linha): Atualize o timer da animação `mAnimTimer` com base na taxa de atualização
    //  (`mAnimFPS`) e no delta time.
    this->mAnimTimer += this->mAnimFPS*deltaTime;

    // TODO 1.3 (~3 linhas): Podemos converter o timer da animação `mAnimTimer`para inteiro para obter o índice do quadro
    //  atual. No entanto, temos que garantir que esse índice não será maior do que número total de quadros da animação
    //  corrente (`mAnimations[mAnimName].size()). Verifique se o timer da animação é maior ou igual ao número de quadros
    //  da animação corrente. Se for, utilize um laço `while` para decrementar o timer por esse mesmo número
    //  até essa condição seja falsa.
    if(this->mAnimTimer >= mAnimations[mAnimName].size()) this->mAnimTimer = 0;
}

void AnimatedSpriteComponent::SetAnimation(const std::string& name) {
    // TODO 3.1 (~2 linhas): salve o nome da animação corrente `name` na variável membro `mAnimName` e
    //  chame a função Update passando delta time igual a zero para reinicializar o timer da animação
    //  `mAnimTimer`.
    this->mAnimName = name;
    this->Update(0);
}

void AnimatedSpriteComponent::AddAnimation(const std::string& name, const std::vector<int>& spriteNums) {
    mAnimations.emplace(name, spriteNums);
}
