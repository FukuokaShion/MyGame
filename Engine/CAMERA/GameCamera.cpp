/**
 * @file GameCamera.cpp
 * @brief ゲームカメラ
 */

#include"GameCamera.h"
#include<cmath>

GameCamera::GameCamera() {}

void GameCamera::Initialize(int window_width, int window_height) {
	Camera::Initialize(window_width, window_height);

	parentPos_ = { 0,0,0 };
	localPos_ = { 0,3,0 };

	const float PI = 3.141592f;
	rota_ = { 0.0f,PI,0.f };
	upLimit_ = PI / 5.0f;
	downLimit_ = -PI / 3.0f;

	sensitivity_ = { 0.05f,0.05f };
	
	isViewReset = false;
	resetSpeed = 0.2f;
}

void GameCamera::Update() {
	Rota();
	ViewReset();

	UpdateViewMatrix();
	UpdateProjectionMatrix();
	matViewProjection_ = matView_ * matProjection_;
}

void GameCamera::Rota() {
	Vector2 stick = Input::GetInstance()->GetRightStickVec();
	Vector2 velocity = { stick.x * sensitivity_.x ,stick.y * sensitivity_.y };
	rota_.x += velocity.y;
	rota_.y += velocity.x;
	if (rota_.x > upLimit_) {
		rota_.x = upLimit_;
	}else if (rota_.x < downLimit_) {
		rota_.x = downLimit_;
	}

	Matrix4 cameraRot = Matrix4::Rotation(rota_, 6);

	target_ = parentPos_ + localPos_;

	Vector3 forward = { 0,0,distance_ };
	forward = Matrix4::bVelocity(forward, cameraRot);
	forward.nomalize();

	eye_ = target_ + (forward * distance_);
}

void GameCamera::ViewReset() {
	if (Input::GetInstance()->PButtonTrigger(X)) {
		rota_ = parentViewVec_;
	}



	//Vector3 viewDifference = parentViewVec_ - rota_;
	//resetVec = viewDifference.nomalize();
	//if (isViewReset) {
	//	rota_ += resetSpeed * resetVec;
	//	if (resetSpeed > abs(parentViewVec_.y - rota_.y)) {
	//		rota_ = parentViewVec_;
	//		isViewReset = false;
	//	}

	//}else if (Input::GetInstance()->PButtonTrigger(X)) {
	//	isViewReset = true;
	//}


}


void GameCamera::SetParentViewVec(Vector3 SetParentViewVec) {
	parentViewVec_ = SetParentViewVec;
	const float PI = 3.141592f;
	parentViewVec_.y += PI;
};