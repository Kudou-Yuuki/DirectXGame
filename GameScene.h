#pragma once

#include "../External/KamataEngine/include/2d/Sprite.h"
#include <KamataEngine.h> // KamataEngine のコンポーネントを使用するために追加
#include <cstdint>
#include <d3d12.h>

using namespace KamataEngine;

class GameScene {
public:
	Sprite* sprite_ = nullptr;
	uint32_t textureHandle_ = 0;
	DirectXCommon* dxCommon = nullptr;

	GameScene();
	~GameScene();

	void Init();
	void Update();
	void Draw();
};