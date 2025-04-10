#include "GameScene.h"
#include <KamataEngine.h>
#include "../External/KamataEngine/include/3d/AxisIndicator.h"
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
	delete debugCamera_;
}

void GameScene::Init() {
	dxCommon = DirectXCommon::GetInstance(); // 念のため再代入
	textureHandle_ = TextureManager::Load("mario.jpg");

	if (textureHandle_ == 0) {
		// エラーハンドリング（テクスチャ読み込み失敗時）
		textureHandle_ = TextureManager::Load("default.png");
	}

	sprite_ = Sprite::Create(textureHandle_, {100, 50});

	model_ = Model::Create();

	worldTransform_ = new WorldTransform();
	worldTransform_->Initialize();

	camera_ = new Camera();
	camera_->Initialize();

	soundDataHandle_ = Audio::GetInstance()->LoadWave("mokugyo.wav");

	Audio::GetInstance()->PlayWave(soundDataHandle_);
	voiceHandle = Audio::GetInstance()->PlayWave(soundDataHandle_, true);

	PrimitiveDrawer::GetInstance()->SetViewProjection(camera_);
	debugCamera_ = new DebugCamera(1280, 720);

	AxisIndicator::GetInstance()->SetVisible(true);

	AxisIndicator::GetInstance()->SetTargetCamera(&debugCamera_->GetCamera());
}

void GameScene::Update() {
	Vector2 position = sprite_->GetPosition();

	position.x += 2.0f; // x座標を1.0f増加
	position.y += 1.0f; // x座標を1.0f増加
	sprite_->SetPosition(position);

	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
	
		Audio::GetInstance()->StopWave(voiceHandle);
	};
	debugCamera_->Update();
#ifdef DEBUG

	ImGui::Begin("GameScene");
	ImGui::Text("Kamata Tarou %d.%d.%d", 2050, 12, 31);
	ImGui::InputFloat3("InputFloat3",inputFloat);
	ImGui::SliderFloat3("SliderFloat3", inputFloat, 0.0f, 1.0f);
	ImGui::ShowDemoWindow();
	ImGui::End();

#endif 

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


	Model::PreDraw(dxCommon->GetCommandList());

	model_->Draw(*worldTransform_, debugCamera_->GetCamera(), textureHandle_);
	PrimitiveDrawer::GetInstance()->DrawLine3d({0, 0, 0}, {0, 10, 0}, {1.0f, 0.0f, 0.0f, 1.0f});

	Model::PostDraw();

#pragma endregion
}