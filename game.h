//=============================================================================
//
// ゲーム画面処理 [game.h]
// Author : 杉本幸宏
//
//=============================================================================
#pragma once

#include "player.h"
#include "mapchip.h"

// ゲーム画面処理の管理方法の選択
//#define GAMEMODE_STRUCT
#define GAMEMODE_CLASS

// クラス管理
#ifdef GAMEMODE_CLASS

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CGameMode
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
#ifdef _DEBUG
	bool GetPauseFlag();				// ポーズフラグの取得
#endif // _DEBUG

	//------------------- セッター関数
	void SetScrollPosition(D3DXVECTOR2 Pos);	// スクロール座標のセット
#ifdef _DEBUG
	void SetPauseFlag(bool Flag);		// ポーズフラグのセット
#endif // _DEBUG

private:
	//------------------- 各インスタンス
	CPlayer m_Player[PLAYER_MAX];		// プレイヤーのインスタンス
	CMapchip m_Mapchip[MAPCHIP_MAX];	// マップチップのサンプル

	//------------------- メンバ変数
	D3DXVECTOR2 m_vScrollPos;			// スクロール座標
#ifdef _DEBUG
	bool	m_bPauseFlag;				// ポーズON/OFF
#endif // _DEBUG
};

#endif // GAMEMODE_CLASS


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
