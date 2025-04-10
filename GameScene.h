#pragma once

#include "../External/KamataEngine/include/2d/Sprite.h"
#include <KamataEngine.h>
#include <cstdint>
#include <d3d12.h>

using namespace KamataEngine;

class GameScene {
public:
	Sprite* sprite_ = nullptr;
	uint32_t textureHandle_ = 0;
	DirectXCommon* dxCommon = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::WorldTransform* worldTransform_ = nullptr;
	KamataEngine::Camera* camera_;
	KamataEngine::DebugCamera* debugCamera_ = nullptr;

	float inputFloat[3] = {0.0f, 0.0f, 0.0f};

	GameScene();
	~GameScene();

	void Init();
	void Update();
	void Draw();
};