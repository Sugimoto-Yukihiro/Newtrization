//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 立石大智, 杉本幸宏
//
//=============================================================================
#pragma once

#include "texture.h"	// テクスチャ描画処理
#include "gravity.h"	// 重力処理
#include "mapchip.h"	// マップチップ

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_MAX		(1)			// プレイヤーのMax人数

#define SCROLL_SET_X	(SCREEN_CENTER_X)	// スクロール座標のセット位置
#define SCROLL_SET_Y	(SCREEN_CENTER_Y)	// スクロール座標のセット位置

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPlayer : public CTexture, public CGravity
{
public:
	CPlayer();	// コンストラクタ
	~CPlayer();	// デストラクタ

	//------------------- メンバ関数
	void Init();	// 初期化
//	void Uninit();	// 終了処理
	void Update();	// 更新処理
	void Draw();	// 描画処理

	//------------------- セッター関数
	void SetPlayer(D3DXVECTOR2 Pos);		// プレイヤーを出現させる
	void SetPlayerPos(D3DXVECTOR2 Pos);		// プレイヤーの座標をセット
	void SetPlayerSize(D3DXVECTOR2 Size);	// プレイヤーのサイズをセット
	void SetPlayerUseFlag(bool Use);		// プレイヤーのuseフラグのセット
	void KillPlayer();						// プレイヤーを殺す処理

	//------------------- ゲッター関数
	D3DXVECTOR2 GetPlayerPos();	// プレイヤーの座標を取得
	D3DXVECTOR2 GetPlayerSize();// プレイヤーの大きさを取得
	bool GetPlayerUseFlag();	// プレイヤーのuseフラグの取得

	//------------------- マクロ定義
	#define PLAYER_ALIVE	SetPlayerUseFlag(true)	// プレイヤーを生き返らせる
	#define PLAYER_KILL		KillPlayer()			// プレイヤーを殺す


private:
	//------------------- メンバ関数(private)
	/* ↓ジャンプ処理はこの関数内で行ってるよ（ジャンプ処理専用の関数作る予定） */
	void ControllPlayerInput(D3DXVECTOR2 NowPosition);					// プレイヤーを キーまたはゲームパッド入力 で動かす
	void CollisionMapchip(CMapchip Mapchip, D3DXVECTOR2 PlayerOldPos);	// マップチップとの当たり判定を取って押し出し処理を行う

	//------------------- メンバ変数
//	int		m_nCurrentMapChipNo;		// プレイヤーの現在いるマップチップ番号
//-	int		m_nMapchipX, m_nMapchipY;	// マップチップ座標系での、プレイヤーの現在位置
	int		m_nTexNo;					// テクスチャ番号
	bool	m_bUse;						// true:使っている(生存)  false:未使用(死亡)
	bool	m_bDush;					// プレイヤーがダッシュ中かどうか
	bool	m_bIsJump;					// プレイヤーがジャンプ中かどうか
	bool	m_bIsMove;					// プレイヤーの動作フラグ   true:動いてる false:停止中
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void CreatePlayerTextureAndBuffer(void);
void ReleasePlayerTextureAndBuffer(void);
void PresetDrawPlayer(void);