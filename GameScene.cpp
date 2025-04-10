#include "GameScene.h"
#include "../External/KamataEngine/include/3d/AxisIndicator.h"
#include <KamataEngine.h>
using namespace KamataEngine;

#include "../External/KamataEngine/include/3d/PrimitiveDrawer.h"

GameScene::GameScene() {
	dxCommon = DirectXCommon::GetInstance(); // ここで初期化
	sprite_ = nullptr;
}

GameScene::~GameScene() {
	if (sprite_) {
		delete sprite_;
		sprite_ = nullptr;
		delete model_;
	}

	delete player_;
}

void GameScene::Init() {
	dxCommon = DirectXCommon::GetInstance(); // 念のため再代入
	textureHandle_ = TextureManager::Load("mario.jpg");

	if (textureHandle_ == 0) {
		// エラーハンドリング（テクスチャ読み込み失敗時）
		textureHandle_ = TextureManager::Load("default.png");
	}

	model_ = Model::Create();

	worldTransform_ = new WorldTransform();
	worldTransform_->Initialize();

	camera_ = new Camera();
	camera_->Initialize();

	 
	player_ = new Player();
	player_->Initialize(model_, textureHandle_, camera_);
}

void GameScene::Update() {
	player_->Update();

}

void GameScene::Draw() {
	if (!dxCommon)
		return; // nullptrチェック

#pragma region 前景スプライト描画
	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();

	Model::PreDraw(dxCommon->GetCommandList());
	
	player_->Draw();

	Model::PostDraw();

#pragma endregion
}