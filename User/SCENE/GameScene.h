#pragma once
#include"SceneState.h"
#include"Sprite.h"

#include"Field.h"
#include"Player.h"
#include"Enemy.h"

class GameScene : public SceneState {
public:
	GameScene();
	void Initialize();
	~GameScene();

	//更新
	void Update() override;

	//描画
	void ObjectDraw() override;
	void FbxDraw() override;
	void SpriteDraw() override;

private:
	void StateTransition() override;

private:
	//画像
	SpriteCommon* spriteCommon = nullptr;

	//メンバ変数
	//カメラ
	Camera* camera = nullptr;
	//フィールド
	Field* field = nullptr;

	//プレイヤー
	Player* player = nullptr;
	//エネミー
	Enemy* enemy = nullptr;

	//画像
	Sprite* UIBase;

	Sprite* hpGauge;
	Sprite* enemyHpGauge;
};

/*
/// <summary>
/// ゲームシーン
/// </summary>
class GameScene
{
private: // 静的メンバ変数

public: // メンバ関数

	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Input* input);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

public:
	//音を止める関数
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };

private: //メンバ変数 (固定)
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;

	SpriteCommon* spriteCommon = nullptr;
	Audio* audio = nullptr;

	const float PI = 3.141592f;

private:
	enum class Scene{
		Titele,
		Option,
		Game,
		Clear,
		GAmeOver,
	};
	Scene scene;
	
	
	//メンバ変数
	//カメラ
	Camera* camera = nullptr;
	//フィールド
	Field* field = nullptr;

	//プレイヤー
	Player* player = nullptr;
	//エネミー
	Enemy* enemy = nullptr;

	//画像
	Sprite* titlePic;
	Sprite* clearPic;
	Sprite* gameoverPic;

	Sprite* UIBase;

	Sprite* hpGauge;
	Sprite* enemyHpGauge;
};*/