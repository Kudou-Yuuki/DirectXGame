#include "GameScene.h"
#include <KamataEngine.h>

using namespace KamataEngine;

GameScene::GameScene() {
	dxCommon = DirectXCommon::GetInstance(); // ここで初期化
	sprite_ = nullptr;
}

GameScene::~GameScene() {
	if (sprite_) {
		delete sprite_;
		sprite_ = nullptr;
	}
}

void GameScene::Init() {
	dxCommon = DirectXCommon::GetInstance(); // 念のため再代入
	textureHandle_ = TextureManager::Load("mario.jpg");

	if (textureHandle_ == 0) {
		// エラーハンドリング（テクスチャ読み込み失敗時）
		textureHandle_ = TextureManager::Load("default.png");
	}

	sprite_ = Sprite::Create(textureHandle_, {100, 50});
}

void GameScene::Update() {
	// 更新処理（もし何か追加するなら）
}

void GameScene::Draw() {
	if (!dxCommon)
		return; // nullptrチェック

#pragma region 前景スプライト描画
	Sprite::PreDraw(dxCommon->GetCommandList());

	if (sprite_) {
		sprite_->Draw();
	}

	Sprite::PostDraw();
#pragma endregion
}