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
#include "fireboots.h"	// ファイヤーブーツ
#include "poison.h"		// 毒処理

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPlayer : public CTexture, public CGravity
{
public:
	CPlayer();	// コンストラクタ
	~CPlayer();	// デストラクタ

	//------------------- メンバ関数
	void Init(char* FireBootsTexName = NULL);		// 初期化
	void Uninit();						// 終了処理
	void Update(int FalmeCnt = 0);		// 更新処理
	void Draw(D3DXVECTOR2 ScrollPos);	// 描画処理

	//------------------- その他メンバ関数
	void KillPlayer();	// このプレイヤーを殺す処理

	//------------------- セッター関数
	void SetPlayer(D3DXVECTOR2 Pos);	// プレイヤーを出現させる
	void SetPosition(D3DXVECTOR2 Pos);	// プレイヤーの座標をセット

	void SetSize(D3DXVECTOR2 Size) { SetGravityObjectSize(Size); };	// プレイヤーのサイズをセット
	void SetBouyant(D3DXVECTOR2 Bouyant) { m_fBouyant = Bouyant; };	// プレイヤーの浮力をセット
	void SetJumpForce(float Force) { m_fJumpForce = Force; };		// プレイヤーのジャンプベクトルを取得
	void SetHPMax(float MaxHP) { m_fHitPointMAX = MaxHP; };			// プレイヤーのHPのMAX値をセット
	void SetCurrentHP(float CurHP) { m_fCurrentHP = CurHP; };		// プレイヤーの現在のHPをセット
	void SetUseFlag(bool Use) { m_bUse = Use; };					// プレイヤーのuseフラグのセット
	void SetPoisonFlag(bool Poison) { m_bPoison = Poison; };		// プレイヤーのuseフラグのセット

	//------------------- ゲッター関数
	D3DXVECTOR2 GetPosition() { return GetGravityObjectPos(); };	// プレイヤーの座標を取得
	D3DXVECTOR2 GetSize() { return GetGravityObjectSize(); };		// プレイヤーの大きさを取得
	D3DXVECTOR2 GetLegPos() { return m_LegPosition; };	// プレイヤーの足の位置を取得
	D3DXVECTOR2 GetBouyant() { return m_fBouyant; };	// プレイヤーの浮力を取得
	float GetJumpForce() { return m_fJumpForce; };		// プレイヤーのジャンプ力を取得
	float GetHP() { return m_fHitPointMAX; };			// プレイヤーのHPを取得
	float GetCurrentHP() { return m_fCurrentHP; };		// プレイヤーの現在のHPを取得
	bool GetUseFlag() { return m_bUse; };				// プレイヤーのuseフラグの取得
	bool GetIsDush() { return m_bDush; };				// プレイヤーのダッシュフラグを取得
	bool GetIsGround() { return m_bOnGround; };			// プレイヤーの接地フラグを取得
	bool GetIsJump() { return m_bIsJump; };				// プレイヤーのジャンプフラグを取得
	bool GetIsMove() { return m_bIsMove; };				// プレイヤーのジャンプフラグを取得
	bool GetIsPoison() { return m_bPoison; };			// プレイヤーの毒状態フラグを取得


	//------------------- マクロ定義
	#define PLAYER_ALIVE	SetUseFlag(true)	// プレイヤーを生き返らせる
	#define PLAYER_KILL		KillPlayer()		// プレイヤーを殺す


private:
	//------------------- メンバ関数(private)
	/* ↓ジャンプ処理はこの関数内で行ってるよ（ジャンプ処理専用の関数作る予定） */
	void InputControllPlayer();					// プレイヤーを キーまたはゲームパッド入力 で動かす
	void CollisionMapchip(CMapchip Mapchip, D3DXVECTOR2 PlayerOldPos);	// マップチップとの当たり判定を取って押し出し処理を行う
	void OnGround();	// 着地した時の処理
	void NotOnGround();	// 空中にいる時の処理

	//------------------- メンバ変数
	CFireBoots	m_FireBoots;				// ファイヤーブーツ
	CPoison		m_Poison;					// 毒処理
	D3DXVECTOR2	m_LegPosition;				// プレイヤーの足の座標
	D3DXVECTOR2	m_fBouyant;					// 浮力加速エリアにぶつかった時の力を保存する変数
	float		m_fJumpForce;				// プレイヤーのジャンプ力
	float		m_fHitPointMAX;				// プレイヤーのHPのMAX値
	float		m_fCurrentHP;				// プレイヤーの現在のHP
//	int			m_nCurrentMapChipNo;		// プレイヤーの現在いるマップチップ番号
//	int			m_nMapchipX, m_nMapchipY;	// マップチップ座標系での、プレイヤーの現在位置
	int			m_nTexNo;					// テクスチャ番号
	bool		m_bUse;						// true:使っている(生存)  false:未使用(死亡)
	bool		m_bDush;					// プレイヤーがダッシュ中かどうか
	bool		m_bOnGround;				// プレイヤーが接地しているかどうか  true:足が地面についている  false:空中にいる
	bool		m_bIsJump;					// プレイヤーがジャンプ中かどうか
	bool		m_bIsMove;					// プレイヤーの動作フラグ   true:動いてる false:停止中
	bool		m_bPoison;					// プレイヤーの毒状態フラグ   true:毒状態 false:毒状態じゃない
};



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void CreatePlayerTexture(void);
void ReleasePlayerTexture(void);
