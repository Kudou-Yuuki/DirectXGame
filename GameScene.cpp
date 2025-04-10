#include "GameScene.h"
#include "../External/KamataEngine/include/3d/AxisIndicator.h"
#include <KamataEngine.h>

using namespace KamataEngine;

#include "../External/KamataEngine/include/3d/PrimitiveDrawer.h"
#include "../External/KamataEngine/include/math/MathUtility.h"


using namespace KamataEngine::MathUtility;


GameScene::GameScene() {
	dxCommon = DirectXCommon::GetInstance(); 
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
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {

		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}
	worldTransformBlocks_.clear();
}
void GameScene::Init() {
	dxCommon = DirectXCommon::GetInstance(); 
	textureHandle_ = TextureManager::Load("mario.jpg");
	BlocktextureHandle_ = TextureManager::Load("block.jpg");

	if (textureHandle_ == 0) {
		// エラーハンドリング（テクスチャ読み込み失敗時）
		textureHandle_ = TextureManager::Load("default.png");
	}

	model_ = Model::Create();
	Blockmodel_ = Model::Create();

	worldTransform_ = new WorldTransform();
	worldTransform_->Initialize();

	camera_ = new Camera();
	camera_->Initialize();

	player_ = new Player();
	player_->Initialize(model_, textureHandle_, camera_);

	const uint32_t knumBlockVirtical = 10;
	const uint32_t knumBlocHorizontal = 20;

	const float kBlockWidth = 2.0f;
	const float kBlockHeight = 2.0f;

	worldTransformBlocks_.resize(knumBlockVirtical);

	for (uint32_t i = 0; i < knumBlockVirtical; i++) {
		worldTransformBlocks_[i].resize(knumBlocHorizontal);
	}

	// 市松模様のようにブロックを配置
	for (uint32_t i = 0; i < knumBlockVirtical; i++) {
		for (uint32_t j = 0; j < knumBlocHorizontal; j++) {
			if ((i + j) % 2 == 0) { 
				worldTransformBlocks_[i][j] = new WorldTransform();
				worldTransformBlocks_[i][j]->Initialize();
				worldTransformBlocks_[i][j]->translation_.x = j * kBlockWidth;
				worldTransformBlocks_[i][j]->translation_.y = i * kBlockHeight;
				worldTransformBlocks_[i][j]->rotation_.x = 0.0f;
				worldTransformBlocks_[i][j]->rotation_.y = 0.0f;
				worldTransformBlocks_[i][j]->scale_.x = 1.0f;
				worldTransformBlocks_[i][j]->scale_.y = 1.0f;
			} else {
				
				worldTransformBlocks_[i][j] = nullptr;
			}
		}
	}
}

void GameScene::Update() {
	player_->Update();

	for (std::vector<WorldTransform*>& blockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : blockLine) {
			if (!worldTransformBlock) {
				continue;
			} else {
				Matrix4x4 scaleMatrix = MakeScaleMatrix(worldTransformBlock->scale_);
				Matrix4x4 rotationXMatrix = MakeRotateXMatrix(worldTransformBlock->rotation_.x);
				Matrix4x4 rotationYMatrix = MakeRotateYMatrix(worldTransformBlock->rotation_.y);
				Matrix4x4 rotationZMatrix = MakeRotateZMatrix(worldTransformBlock->rotation_.z);
				Matrix4x4 rotationMatrix = rotationXMatrix * rotationYMatrix * rotationZMatrix;
				Matrix4x4 translationMatrix = MakeTranslateMatrix(worldTransformBlock->translation_);

				worldTransformBlock->matWorld_ = scaleMatrix * rotationMatrix * translationMatrix;

				worldTransformBlock->TransferMatrix();
			}
		}
	}
}

void GameScene::Draw() {
	if (!dxCommon)
		return; 

#pragma region 前景スプライト描画
	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();

	Model::PreDraw(dxCommon->GetCommandList());
	/*
	player_->Draw();*/

	for (std::vector<WorldTransform*>& blockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : blockLine) {
			if (worldTransformBlock) {
				Blockmodel_->Draw(*worldTransformBlock, *camera_, BlocktextureHandle_);
			}
		}
	}

	Model::PostDraw();

#pragma endregion
}