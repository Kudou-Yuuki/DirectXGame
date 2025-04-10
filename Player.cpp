#include "Player.h"
#include <cassert>

using namespace KamataEngine;

Player::Player() {}

Player::~Player() {}

void Player::Initialize(Model* model, uint32_t textureHandle, KamataEngine::Camera* camera) {
	assert(model);
	model_ = model;
	camera_ = camera;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize(); 
}

void Player::Update() {

	worldTransform_.TransferMatrix();
}

void Player::Draw() {  
   
   model_->Draw(worldTransform_, *camera_, textureHandle_, nullptr);  
}