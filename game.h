//=============================================================================
//
// ゲーム画面処理 [game.h]
// Author : 杉本幸宏
//
//=============================================================================
#pragma once

#include "player.h"			// プレイヤー
#include "enemy.h"			// エネミー
#include "mapchip.h"		// マップチップ
#include "userInterface.h"	// UI
#include "sideblack.h"		// 画面端処理
#include "floatforce.h"		// 浮力加速
#include "score.h"			// スコア

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//------------------- ファイルに関する定義
//#define GAME_MAP_DATA_TEST			"data/MAPCHIP/alpha_MAP.csv"	// マップ情報のファイル名
//#define GAME_MAP_DATA_1			"data/MAPCHIP/alpha_MAP.csv"	// マップ情報のファイル名
#define GAME_MAP_DATA_1				"data/MAPCHIP/MAP_01.csv"			// マップ情報のファイル名
#define GAME_MAP_DATA_2				"data/MAPCHIP/MAP_02.csv"			// マップ情報のファイル名
#define PLAYER_SYMBOL				'P'		// プレイヤーの記号
#define ENEMY_SYMBOL				'E'		// エネミーの記号
#define FURYOKU_SYMBOL				'F'		// 浮力加速エリアの記号

//------------------- マップチップに関する定義
#define TEXTURE_NAME_MAPCHIP		"data/TEXTURE/mapchip/0901_mapchip.png"
#define TEXTURE_NAME_MAPCHIP_DEBUG	"data/TEXTURE/mapchip/0829_Number.png"

/* マップチップテクスチャの分割数　→　固定値とする */
#define MAPCHIP_TEXTURE_DIVIDE_X	(5)		// 横方向の分割数
#define MAPCHIP_TEXTURE_DIVIDE_Y	(5)	// 縦方向の分割数

#define MAPCHIP_DEBUG_TEXTURE_DIVIDE_X	(5)	// 横方向の分割数
#define MAPCHIP_DEBUG_TEXTURE_DIVIDE_Y	(6)	// 縦方向の分割数


// 壁判定のマップチップ番号
/* "MAPCHIP_HIT_min" ~ "MAPCHIP_HIT_MAX" の番号が当たり判定属性を持つマップチップ */
#define MAPCHIP_HIT_min				(1)		// 壁判定属性のマップチップ番号の最小値
#define MAPCHIP_HIT_MAX				(9)		// 壁判定属性のマップチップ番号の最大値

// 毒のマップチップ番号
/* "MAPCHIP_POISON_min" ~ "MAPCHIP_POISON_MAX" の番号が毒判定属性を持つマップチップ */
#define MAPCHIP_POISON_min			(18)	// 毒判定属性のマップチップ番号の最小値
#define MAPCHIP_POISON_MAX			(19)	// 毒判定属性のマップチップ番号の最大値

// エンジンのマップチップ番号
/* "MAPCHIP_CANGE_GRAVITY_min" ~ "MAPCHIP_CANGE_GRAVITY_MAX" の番号が重力変更判定属性を持つマップチップ */
#define MAPCHIP_CANGE_GRAVITY_min	(10)	// 重力変更判定属性のマップチップ番号の最小値
#define MAPCHIP_CANGE_GRAVITY_MAX	(17)	// 重力変更判定属性のマップチップ番号の最大値
//#define CASE_CANGE_GRAVITY_NO		case 12:

// ゴールのマップチップ番号
/* "MAPCHIP_GOAL_min" ~ "MAPCHIP_GOAL_MAX" の番号がゴール判定属性を持つマップチップ */
#define MAPCHIP_GOAL_min			(20)	// ゴール判定属性のマップチップ番号の最小値
#define MAPCHIP_GOAL_MAX			(20)	// ゴール判定属性のマップチップ番号の最大値
//#define CASE_GOAL_NO				case 13:

//------------------- スクロール座標に関する定義
#define SCROLL_SET_X	(SCREEN_CENTER_X * 0.5f)	// スクロール座標のセット位置
#define SCROLL_SET_Y	(SCREEN_CENTER_Y)			// スクロール座標のセット位置

//------------------- プレイヤー
#define PLAYER_MAX					(1)			// プレイヤーのMax人数
#define PLAYER_TEXTURE_NAME			"data/TEXTURE/player/player01.png"		// プレイヤーのテクスチャのファイル名

//------------------- エネミー
#define ENEMY_MAX					(16)		// エネミーの最大数

//------------------- シネマチック処理
#define TEXTURE_NAME_SIDEBLACK		"data/TEXTURE/SideBlack/CinemaScope.png"	// テクスチャのファイル名

//------------------- ファイヤーブーツ
#define FIREBOOTS_BULLET_TEXNAME	"data/TEXTURE/Bullet/bullet01.png"	// ファイヤーブーツから出すバレットのテクスチャ名
#define FIREBOOTS_BULLET_WIDTH		(50.0f)
#define FIREBOOTS_BULLET_HEIGHT		(50.0f)
#define FIREBOOTS_BULLET_SIZE		D3DXVECTOR2(FIREBOOTS_BULLET_WIDTH, FIREBOOTS_BULLET_HEIGHT)	// 弾のサイズ
#define FIREBOOTS_BULLET_SPEED		(13.0f)		// ファイヤーブーツから出すバレットの速度

//------------------- 毒
#define POISON_ATTACK_VALUE			(3.0f)		// 毒の一回あたりの攻撃力
#define POISON_FLAME_WAIT			(6)			// 何フレームあたり毒の攻撃を行うか
#define POISON_PLAYER_CHANGE_ALPHA	(0.03f)		// 毒状態時の、プレイヤーの透明度を変える値

//------------------- 浮力加速
#define FURYOKU_TEX_NAME			"data/TEXTURE/buoyant/area.jpg"	// 浮力エリアのテクスチャ名
#define FURYOKU_TEX_COLOR			D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.85f)	// 浮力エリアのテクスチャの頂点色
#define FURYOKU_MAX					(32)							// 浮力エリアの最大数
#define FURYOKU_DIRECTION			D3DXVECTOR2(0.0, -1.0f)			// 浮力エリアの最大値
#define FURYOKU_FORCE				(10.0f)							// 

//------------------- スコア表示
#define SCORE_TEX_NAME				"data/TEXTURE/score/0829_Score_Number.png"	// スコアのテクスチャ名
#define SCORE_DRAW_SIZE				D3DXVECTOR2(35.0f, 35.0f)		// スコアの表示サイズ
#define SCORE_DRAW_POS_RIGHT		D3DXVECTOR2(930.0f, 35.0f)		// スコアの表示位置（最右の数字の位置）


//------------------- その他ゲーム内で使用するパラメータ
#define DEFAULT_GRAVITY_WAIT		(0.55f)		// 重力の値(デフォルトの時)
#define LEFT_GRAVITY_WAIT			(0.55f)		// 重力の値(左方向の時)


//*****************************************************************************
// クラス定義
//*****************************************************************************
class CModeGame
{
public:
//	CModeGame();
//	~CModeGame();

	//------------------- メンバ関数
	void Init();	// 初期化
	void Uninit();	// 終了処理
	void Update();	// 更新処理
	void Draw();	// 描画処理

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

#ifdef _DEBUG
	bool GetPauseFlag() { return m_bPauseFlag; };			// ポーズON/OFF
	bool GetMapchipDebugFlag() { return m_bMapchipDebug; };	// マップチップのデバッグ表示
#endif // _DEBUG


	//------------------- セッター関数
	void SetScrollPosition(D3DXVECTOR2 Pos);	// スクロール座標のセット

private:
	//------------------- メンバ関数(private)
	bool PutFloatForceArea(D3DXVECTOR2 Pos);	// 浮力加速エリアのセット（単位はマップチップ）
	bool PutEnemy(D3DXVECTOR2 Pos);				// エネミーのセット（単位はマップチップ）

	//------------------- 各インスタンス
	CGameUI m_GameUI;			// ゲームUI
	CPlayer	m_Player;			// プレイヤーのインスタンス
	CEnemy	m_Enemy[ENEMY_MAX];	// エネミー
	CMapchip m_Mapchip;			// マップチップ
	CSideBlack m_SideBlack;		// 画面端の黒くするやつ
	CFloatForce m_FloatForceArea[FURYOKU_MAX];	// 浮力加速エリア（一時的に16個用意。動的管理したい）
	CScore	m_Score;			// スコア

#ifdef _DEBUG
	CMapchip m_DebugMapchip;	// デバッグ表示用マップチップ
#endif // _DEBUG


	//------------------- メンバ変数
	D3DXVECTOR2 m_vScrollPos;		// スクロール座標
	int m_GravityDirection;			// 重力の方向
	int m_nFlameCnt;				// フレーム数のカウント
	bool m_bIsTouchGrvityChange;	// 重力変更エンジンに触れているかどうか

#ifdef _DEBUG
	bool	m_bPauseFlag;			// ポーズON/OFF
	bool	m_bMapchipDebug;		// マップチップのデバッグ表示
#endif // _DEBUG
};



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
int HitCheckMapchip(CMapchip Mapchip, D3DXVECTOR2* CurrentPos, D3DXVECTOR2 OldPos, bool FlagX = true, bool FlagY = true);

void SetGameCrea(bool CreaFlag);
bool GetGameCrea(void);