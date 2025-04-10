#pragma once  

#include "../External/KamataEngine/include/2d/Sprite.h"  
#include <KamataEngine.h>  
#include <cstdint>  
#include <d3d12.h>  
#include "Player.h"  
#include <vector>
using namespace KamataEngine;  

class GameScene {  
public:  
   Player* player_ = nullptr;
   Sprite* sprite_ = nullptr;  
   uint32_t textureHandle_ = 0;  
   uint32_t BlocktextureHandle_ = 0;  
   DirectXCommon* dxCommon = nullptr;  
   KamataEngine::Model* model_ = nullptr;  
   KamataEngine::Model* Blockmodel_ = nullptr;  
   KamataEngine::WorldTransform* worldTransform_ = nullptr;  
   KamataEngine::Camera* camera_;  
    std::vector < std::vector<KamataEngine::WorldTransform*>>worldTransformBlocks_;
   GameScene();  
   ~GameScene();  

   void Init();  
   void Update();  
   void Draw();  
};