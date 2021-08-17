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
#define BOOTS_BULLET_NUM		(3)		// ファイヤーブーツで使用する弾の数

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CFireBoots
{
public:
	CFireBoots();	// コンストラクタ
	~CFireBoots();	// デストラクタ

	void Init(char* pBulletTextureName = NULL, int TexDivX = 1, int TexDivY = 1, int AnimWait = 0);	// 初期化処理
	void Uninit();	// 終了処理
	void Update(D3DXVECTOR2 StageSize);	// 更新処理
	void Draw(D3DXVECTOR2 ScrollPos);	// 描画処理

	//------------------- メンバ関数
	bool ActivateFireBoots(D3DXVECTOR2 BulletMove, D3DXVECTOR2 BulletSize, float Attack = 0.0f, float HP = 0.0f);	// ファイヤーブーツの起動

	//------------------- セッター関数
//	void SetFireBoots(CPlayer* User);			// プレイヤーにファイヤーブーツをセット
	bool SetFireBoots(D3DXVECTOR2* UserPos);	// ファイヤーブーツをセットするキャラクターの座標をセット
	bool UnsetFireBoots();						// ファイヤーブーツの解除

	//------------------- ゲッター関数


private:
	CBullet m_Bullet[BOOTS_BULLET_NUM];	// ファイヤーブーツで下方向に飛ばすバレット
//	CPlayer* m_pUser;				// このファイヤーブーツを装着しているプレイヤーへのポインタ
	D3DXVECTOR2* m_pPosition;		// このファイヤーブーツを装着しているキャラクターの座標
	int m_nUsedBulletNum;			// 既に発射したバレットの数
};
