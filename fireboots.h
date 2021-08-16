//==================================================================
//
// ファイヤーブーツ処理 [fireboots.cpp]
// Auther : 杉本幸宏
//
//==================================================================
#pragma once

#include "player.h"	// プレイヤー
#include "bullet.h"	// バレット

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BULLET_NUM		(3)		// ファイヤーブーツで使用する弾の数

#define BULLET_WIDTH	50.0f
#define BULLET_HEIGHT	50.0f
#define BULLET_SIZE		D3DXVECTOR2(BULLET_WIDTH, BULLET_HEIGHT)	// 弾のサイズ


//*****************************************************************************
// クラス定義
//*****************************************************************************
class CFireBoots
{
public:
	CFireBoots();	// コンストラクタ
	~CFireBoots();	// デストラクタ

	void Init(char* pTextureName = NULL, int TexDivX = 1, int TexDivY = 1, int AnimWait = 0);	// 初期化処理
	void Uninit();	// 終了処理
	void Update();	// 更新処理
	void Draw(D3DXVECTOR2 ScrollPos);	// 描画処理

	//------------------- セッター関数
//	void SetFireBoots(CPlayer* User);			// プレイヤーにファイヤーブーツをセット
	bool SetFireBoots(D3DXVECTOR2* UserPos);	// ファイヤーブーツをセットするキャラクターの座標をセット
	bool UnsetFireBoots();						// ファイヤーブーツの解除

	//------------------- ゲッター関数


private:
	CBullet m_Bullet[BULLET_NUM];	// ファイヤーブーツで下方向に飛ばすバレット
//	CPlayer* m_pUser;				// このファイヤーブーツを装着しているプレイヤーへのポインタ
	D3DXVECTOR2* m_pPosition;		// このファイヤーブーツを装着しているキャラクターの座標
	float m_fUpForce;				// ファイヤーブーツから弾を発射させたときの上方向への力
	int m_nUsedBulletNum;			// 既に発射したバレットの数
};
