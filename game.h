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
// マクロ定義
//*****************************************************************************
#define PLAYER_SYMBOL		'P'		// プレイヤーの記号
#define ENEMY_SYMBOL		'E'		// エネミーの記号

/* マップチップテクスチャの分割数　→　固定値とする */
#define MAPCHIP_TEXTURE_DIVIDE_X	4			// 横方向の分割数
#define MAPCHIP_TEXTURE_DIVIDE_Y	4			// 縦方向の分割数

// マップチップのファイル名
#define GAME_MAP_DATA_1			"data/MAPCHIP/alpha_MAP.csv"	// マップ情報のファイル名

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

	//【注意】↓ この関数を呼び出す前に、全てのオブジェクトの初期化処理を行うこと！
	int PutAllObject(const char* pCsvStr);	// 全てのオブジェクトの設置
//	void PutAllObject(char* MapDataFile, int chipTexDivX, int chipTexDivY);	// 全てのオブジェクトを配置する（マップチップ, プレイヤー, エネミー, ギミック... などなど）
//	void PutPlayer(const char* csvMapData, char Symbol);	// csvのマップデータから、プレイヤーを配置する
//	void PutEnemy(const char* csvMapData, char Symbol);		// csvのマップデータから、エネミーを配置する
//	void PutGimmick(const char* csvMapData, char Symbol);	// csvのマップデータから、ギミックを配置する


	//------------------- ゲッター関数
	D3DXVECTOR2 GetScrollPosition();
	CMapchip* GetMapchip();			// マップチップのインスタンスへのアクセス
	int GetGravityDirection();		// 重力の方向を取得

	//------------------- セッター関数
	void SetScrollPosition(D3DXVECTOR2 Pos);	// スクロール座標のセット
	void SetGravityDirection(int Direction);	// ゲーム全体の重力の方向をセット

private:
	//------------------- 各インスタンス
	CPlayer m_Player[PLAYER_MAX];		// プレイヤーのインスタンス
	CMapchip m_Mapchip;					// マップチップのサンプル

	//------------------- メンバ変数
	D3DXVECTOR2 m_vScrollPos;			// スクロール座標
	int m_GravityDirection;				// 重力の方向
	bool m_bIsTouchGrvityChange;		// 重力変更エンジンに触れているかどうか


#ifdef _DEBUG
	bool	m_bPauseFlag;				// ポーズON/OFF
#endif // _DEBUG
};

#endif // GAMEMODE_CLASS

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//int HitCheckMapchip(CMapchip Mapchip, D3DXVECTOR2* CurrentPos, D3DXVECTOR2 OldPos, D3DXVECTOR2 HalfObjectSize);
//int HitCheckMapchip(CMapchip Mapchip, D3DXVECTOR2* CurrentPos, D3DXVECTOR2 OldPos, bool Flag = true);
int HitCheckMapchip(CMapchip Mapchip, D3DXVECTOR2* CurrentPos, D3DXVECTOR2 OldPos, bool FlagX = true, bool FlagY = true);




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
