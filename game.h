//=============================================================================
//
// ゲーム画面処理 [game.h]
// Author : 杉本幸宏
//
//=============================================================================
#pragma once

#include "player.h"		// プレイヤー
#include "mapchip.h"	// マップチップ

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//------------------- ファイルに関する定義
#define GAME_MAP_DATA_1				"data/MAPCHIP/alpha_MAP.csv"	// マップ情報のファイル名
#define PLAYER_SYMBOL				'P'		// プレイヤーの記号
#define ENEMY_SYMBOL				'E'		// エネミーの記号
/* マップチップテクスチャの分割数　→　固定値とする */
#define MAPCHIP_TEXTURE_DIVIDE_X	(4)		// 横方向の分割数
#define MAPCHIP_TEXTURE_DIVIDE_Y	(4)		// 縦方向の分割数

//------------------- スクロール座標に関する定義
#define SCROLL_SET_X	(SCREEN_CENTER_X)	// スクロール座標のセット位置
#define SCROLL_SET_Y	(SCREEN_CENTER_Y)	// スクロール座標のセット位置

//------------------- ゲーム内オブジェクトに関する定義
#define PLAYER_MAX		(1)			// プレイヤーのMax人数


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
	void ChangeGravityDirection(int Direction);	// ゲーム全体の重力の方向を変える

	//【注意】↓ この関数を呼び出す前に、全てのオブジェクトの初期化処理を行うこと！
	int PutAllObject(const char* pCsvStr);	// 全てのオブジェクトの設置
//	void PutAllObject(char* MapDataFile, int chipTexDivX, int chipTexDivY);	// 全てのオブジェクトを配置する（マップチップ, プレイヤー, エネミー, ギミック... などなど）
//	void PutPlayer(const char* csvMapData, char Symbol);	// csvのマップデータから、プレイヤーを配置する
//	void PutEnemy(const char* csvMapData, char Symbol);		// csvのマップデータから、エネミーを配置する
//	void PutGimmick(const char* csvMapData, char Symbol);	// csvのマップデータから、ギミックを配置する


	//------------------- ゲッター関数
	D3DXVECTOR2 GetScrollPosition();
	CMapchip* GetMapchip();			// マップチップのインスタンスへのアクセス
	CPlayer* GetPlayer();			// プレイヤーのインスタンスへのアクセス
	int GetGravityDirection();		// 重力の方向を取得

	//------------------- セッター関数
	void SetScrollPosition(D3DXVECTOR2 Pos);	// スクロール座標のセット

private:
	//------------------- メンバ関数(private)


	//------------------- 各インスタンス
	CPlayer	m_Player;				// プレイヤーのインスタンス
	CMapchip m_Mapchip;				// マップチップのサンプル

	//------------------- メンバ変数
	D3DXVECTOR2 m_vScrollPos;		// スクロール座標
	int m_GravityDirection;			// 重力の方向
	bool m_bIsTouchGrvityChange;	// 重力変更エンジンに触れているかどうか


#ifdef _DEBUG
	bool	m_bPauseFlag;			// ポーズON/OFF
#endif // _DEBUG
};



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
int HitCheckMapchip(CMapchip Mapchip, D3DXVECTOR2* CurrentPos, D3DXVECTOR2 OldPos, bool FlagX = true, bool FlagY = true);
