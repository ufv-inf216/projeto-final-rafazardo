cmake_minimum_required(VERSION 3.26)
# Configurando o padrão c++
set(CMAKE_CXX_STANDARD 17)

# INIT NO SCREEN BUGFIX
# Em alguns casos, o programa pode não renderizar a tela. Por isso temos
# as seguintes linhas. Caso encontre algum problema, comente-as.
set(CMAKE_SKIP_RPATH ON)
set(CMAKE_SKIP_RPATH ON CACHE BOOL "Skip RPATH" FORCE)
# END NO SCREEN BUGFIX
####### DO NOT EDIT ABOVE

# Configurando o nome e executável do projeto
set(PROJECT_NAME "projeto-final-inf216")
project(${PROJECT_NAME})
add_executable(${PROJECT_NAME}
        Source/Main.cpp
        Source/Game/Math.cpp
        Source/Game/Random.cpp
        Source/GameObjects/GameObject.cpp
        Source/Components/Component.cpp
        Source/Game/Game.cpp
        Source/Components/DrawComponents/DrawComponent.cpp
        Source/Components/PhysicsComponents/RigidBodyComponent.cpp
        Source/Components/DrawComponents/SpriteComponent.cpp
        Source/Components/DrawComponents/DrawPolygonComponent.cpp
        Source/Components/ColliderComponents/BoxColliderComponent.cpp
        Source/GameObjects/Spawner.cpp
        Source/Components/DrawComponents/AnimatedSpriteComponent.cpp
        Source/GameSpecific/MyGame.cpp
        Source/GameObjects/Camera.cpp
        Source/GameSpecific/Maps/Map.cpp
        Source/GameSpecific/Characters/Character.cpp
        Source/GameSpecific/Characters/Player.cpp
        Source/Components/ColliderComponents/CollisionMatrixComponent.cpp
        Source/GameSpecific/Characters/NPC.cpp
        Source/GameSpecific/Inventory.cpp
        Source/Game/Global.cpp
        Source/GameSpecific/Characters/Enemy.cpp
        Source/GameSpecific/Characters/Crafter.cpp
        Source/GameSpecific/Chest.cpp
        Source/GameSpecific/Saver.cpp
        Source/GameObjects/Trigger.cpp
        Source/GameSpecific/Maps/Dungeons/Room.cpp
        Source/GameSpecific/Maps/Dungeons/Layer.cpp
        Source/GameSpecific/Maps/Dungeons/Dungeon.cpp
        Source/GameSpecific/Maps/Dungeons/DungeonGeneration/DungeonGenerator.cpp
        Source/GameSpecific/Maps/Dungeons/DungeonGeneration/LayerGeneration.cpp
        Source/GameSpecific/Maps/Dungeons/DungeonGeneration/DungeonGridGeneration.cpp
        Source/GameSpecific/Battle/BattleCharacters/BattleCharacter.cpp
        Source/GameSpecific/Battle/BattleCharacters/BattlePlayer.cpp
        Source/GameSpecific/Battle/BattleCharacters/BattleEnemy.cpp
        Source/GameSpecific/Battle/Battle.cpp
        Source/GameSpecific/Battle/Action.cpp
        Source/Game/AudioSystem.cpp
        Source/GameObjects/Door.cpp
        Source/Interfaces/Fade.cpp
        Source/Components/DrawComponents/DrawRectComponent.cpp
        Source/Components/AIComponents/FSMComponent.cpp
        Source/Components/AIComponents/FSMComponent.h
        Source/Components/AIComponents/FSMState.cpp
        Source/Components/AIComponents/FSMState.h
        Source/GameSpecific/Characters/Enemies/Bat.cpp
        Source/GameSpecific/Characters/Enemies/Bat.h
        Source/GameSpecific/Characters/Enemies/States/BatIdleState.cpp
        Source/GameSpecific/Characters/Enemies/States/BatIdleState.h
        Source/GameSpecific/Characters/Enemies/States/BatMovingState.cpp
        Source/GameSpecific/Characters/Enemies/States/BatMovingState.h
        Source/GameSpecific/Characters/Enemies/States/BatState.cpp
        Source/GameSpecific/Characters/Enemies/States/BatState.h
        Source/Interfaces/HUDs/BattleHUDs/BattleHUD.cpp
        Source/Interfaces/HUDs/BattleHUDs/BattleHUD.h
        Source/Interfaces/HUDs/BattleHUDs/HPBarBattleHUD.cpp
        Source/Interfaces/HUDs/BattleHUDs/HPBarBattleHUD.h
        Source/Interfaces/Interface.cpp
        Source/Interfaces/HUDs/BattleHUDs/ActionSelectorBattleHUD.cpp
        Source/Interfaces/HUDs/BattleHUDs/ActionSelectorBattleHUD.h
        Source/Interfaces/HUDs/BattleHUDs/ItemSelectorBattleHUD.cpp
        Source/Interfaces/HUDs/BattleHUDs/ItemSelectorBattleHUD.h
        Source/Interfaces/HUDs/GameHUDs/PressSpaceHUD.h
        Source/Interfaces/HUDs/BattleHUDs/EnemySelectorBattleHUD.cpp
)

####### DO NOT EDIT BELLOW
find_package(SDL2 2.28.2 EXACT REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES}  SDL2_image::SDL2_image SDL2_mixer::SDL2_mixer SDL2_ttf::SDL2_ttf)