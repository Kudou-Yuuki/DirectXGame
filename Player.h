#pragma once
#include <KamataEngine.h>
class Player {

public:
	Player();
	~Player();
	void Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera);
	void Update();
	void Draw();

private:
	KamataEngine::Camera* camera_;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;
	uint32_t textureHandle_ = 0;
	

};
