//=============================================================================
//
// UI処理 [userInterface.h]
// Author : 杉本幸宏
//
//=============================================================================
#pragma once

#include "texture.h"

//*****************************************************************************
// enum
//*****************************************************************************
enum
{
/* 左上原点で描画するテクスチャ */
	GAMEUI_TEX_TYPE_HPgage,			// プレイヤーのHPゲージ
	GAMEUI_TEX_TYPE_HPgage_Cover,	// プレイヤーのHPゲージの装飾

/* ここより下は中心原点で描画するテクスチャ */
//	UI_TEX_TYPE_Player_PoisonIcon,	// プレイヤーの毒状態アイコン


	// 使用するテクスチャの数
	GAMEUI_TEX_TYPE_MAX,

	// 左上原点で描画するテクスチャの最大番号（つまり、enumで一番下に書いてあるやつ）
	GAMEUI_TEX_DRAW_TOPLEFT_MAXNO = GAMEUI_TEX_TYPE_HPgage_Cover,
}; // GAME_UI_TEXTURE_TYPE;	// ゲーム画面のUIで使用するテクスチャの種類

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define HP_GAGE_POS_TOPLEFT		D3DXVECTOR2(0.0f, 0.0f)			// HPゲージの描画位置（左上座標）
#define HP_GAGE_WIDTH			275.0f								// HPゲージの横幅
#define HP_GAGE_HEIGHT			23.0f								// HPゲージの縦幅
#define HP_GAGE_SIZE			D3DXVECTOR2(HP_GAGE_WIDTH, HP_GAGE_HEIGHT)	// HPゲージのサイズ
#define HP_GAGE_COLOR			D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)	// HPゲージ本体の超転職

#define HP_GAGE_COVER_WIDTH		300.0f		// HPゲージカバーの横幅
#define HP_GAGE_COVER_HEIGHT	50.0f		// HPゲージカバーの縦幅

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CGameUI	// ユーザーインターフェース クラス
{
public:
	CGameUI();		// コンストラクタ
	~CGameUI();		// デストラクタ

	//------------------- メンバ関数
	void Init();	// 初期化処理
	void Uninit();	// 終了処理
	void Update();	// 更新処理
	void Draw();	// 描画処理

private:
	//------------------- メンバ変数
	CTexture m_GameTexture[GAMEUI_TEX_TYPE_MAX];	// 使用テクスチャ（Game）

};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void CreateGameUITexture(void);		// テクスチャの生成
void ReleaseGameUITexture(void);	// テクスチャの解放
