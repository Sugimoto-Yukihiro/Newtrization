//=============================================================================
//
// ゲーム画面処理 [game.h]
// Author : 杉本幸宏
//
//=============================================================================
#pragma once

#include "player.h"		// プレイヤー
#include "mapchip.h"	// マップチップ

// ゲーム画面処理の管理方法の選択
//#define GAMEMODE_STRUCT
#define GAMEMODE_CLASS

// クラス管理
#ifdef GAMEMODE_CLASS

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CModeGame
{
public:
	//------------------- メンバ関数
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void CollisionCheck();	// 当たり判定

	//------------------- ゲッター関数
	D3DXVECTOR2 GetScrollPosition();
	CMapchip* GetMapchip();			// マップチップのインスタンスへのアクセス
	int GetGravityDirection();		// 重力の方向を取得

#ifdef _DEBUG
	bool GetPauseFlag();			// ポーズフラグの取得
#endif // _DEBUG

	//------------------- セッター関数
	void SetScrollPosition(D3DXVECTOR2 Pos);		// スクロール座標のセット
	void SetGravityDirection(int Direction);	// 重力の向きを変更

#ifdef _DEBUG
	void SetPauseFlag(bool Flag);		// ポーズフラグのセット
#endif // _DEBUG

private:
	//------------------- 各インスタンス
	CPlayer m_Player[PLAYER_MAX];		// プレイヤーのインスタンス
	CMapchip m_Mapchip;					// マップチップのサンプル

	//------------------- メンバ変数
	D3DXVECTOR2 m_vScrollPos;			// スクロール座標
	int m_GravityDirection;	// 重力の方向
#ifdef _DEBUG
	bool	m_bPauseFlag;				// ポーズON/OFF
#endif // _DEBUG
};

#endif // GAMEMODE_CLASS

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//int HitCheckMapchip(CMapchip Mapchip, D3DXVECTOR2* CurrentPos, D3DXVECTOR2 OldPos, D3DXVECTOR2 HalfObjectSize);
int HitCheckMapchip(CMapchip Mapchip, D3DXVECTOR2* CurrentPos, D3DXVECTOR2 OldPos);




// 構造体管理
#ifdef GAMEMODE_STRUCT

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);

void SetScrollPosition(D3DXVECTOR2 Pos);
D3DXVECTOR2* GetScrollPosition();
#endif // GAMEMODE_STRUCT
