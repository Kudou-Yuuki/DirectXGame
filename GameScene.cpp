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
		delete Blockmodel_;
	}

	delete player_;

	for (WorldTransform * worldTransformBlock : worldTransformBlocks) {
		delete worldTransformBlock;
	}
	worldTransformBlocks.clear();
}

void GameScene::Init() {
	dxCommon = DirectXCommon::GetInstance(); // 念のため再代入
	textureHandle_ = TextureManager::Load("mario.jpg");
	BlocktextureHandle_ = TextureManager::Load("block.jpg");

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


	const uint32_t knumBlocHorizontal = 20;
	const float kBlockWidth = 2.0f;

	worldTransformBlocks.resize(knumBlocHorizontal);

	for (uint32_t i = 0; i < knumBlocHorizontal; i++) {
		worldTransformBlocks[i] = new WorldTransform();
		worldTransformBlocks[i]->Initialize();
		worldTransformBlocks[i]->translation_.x = i * kBlockWidth;
		worldTransformBlocks[i]->translation_.y = 1.0f;
		worldTransformBlocks[i]->rotation_.x = 1.0f;
		worldTransformBlocks[i]->rotation_.y = 1.0f;
		worldTransformBlocks[i]->scale_.x = 1.0f;
		worldTransformBlocks[i]->scale_.y = 1.0f;

	}
}

void GameScene::Update() {
	player_->Update();
	for (WorldTransform* worldTransformBlock : worldTransformBlocks) {

		worldTransformBlock->scale_;
		worldTransformBlock->rotation_;
		worldTransformBlock->translation_;

	/*	worldTransformBlock->matWorld_ = アフィン変換行列;*/

		worldTransformBlock->TransferMatrix();
	}
}

void GameScene::Draw() {
	if (!dxCommon)
		return; // nullptrチェック

#pragma region 前景スプライト描画
	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();

	Model::PreDraw(dxCommon->GetCommandList());
	
	player_->Draw();

	for (WorldTransform* worldTransformBlock : worldTransformBlocks) {
		Blockmodel_->Draw(*worldTransformBlock,camera);
	}

	Model::PostDraw();

#pragma endregion
}