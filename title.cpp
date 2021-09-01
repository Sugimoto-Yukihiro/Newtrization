//=============================================================================
//
// タイトル画面処理 [title.cpp]
// Author : 杉本幸宏
//
//=============================================================================
#include "main.h"
#include "title.h"

#include "renderer.h"
#include "input.h"		// キー・ゲームパッド入力
#include "fade.h"		// フェード
#include "sound.h"		// サウンド

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NEXT_MODE					MODE_GAME		// 次のモード

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static char *g_TextureName[] = {
	"data/TEXTURE/BG/0830_BG_1.png",		// 背景
	"data/TEXTURE/Title/0829_Logo.png",		// ロゴ
};

//=============================================================================
// 初期化処理
//=============================================================================
void CModeTitle::Init()
{
	// テクスチャを一括生成
	for (int i = 0; i < TITLE_TEX_MAX; i++)
	{
		m_Texture[i].Init();	// 初期化
		m_Texture[i].CreateTextureInf(g_TextureName[i]);	// テクスチャ生成
	}

	// テクスチャインスタンスのパラメータをセット
	SetTitleTexInf();

	// BGM再生
	PlaySound(SOUND_LABEL_BGM_title_01);

}

//=============================================================================
// 終了処理
//=============================================================================
void CModeTitle::Uninit()
{
	// サウンド停止
	StopSound();

	// テクスチャを一括解放
	for (int i = 0; i < TITLE_TEX_MAX; i++)
	{
		m_Texture[i].ReleaseTextureInf();	// テクスチャ解放
		m_Texture[i].Uninit();	// 終了処理
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void CModeTitle::Update()
{
	//------------------- キー・ゲームパットでの入力で次のモードへ
#ifdef KEY_MODE_CHANGE
	if (KEY_MODE_CHANGE || PAD_MODE_CHANGE)
	{
		SetFade(FADE_OUT, NEXT_MODE);			// フェードして次のモードへ
	//	SetMode(NEXT_MODE);						// 次のモードにシーン遷移
		PlaySound(SOUND_LABEL_SE_scenemove);	// 効果音再生
	}
#endif // KEY_MODE_CHANGE


}

//=============================================================================
// 描画処理
//=============================================================================
void CModeTitle::Draw()
{
	// 2Dの描画前準備
	PresetDraw2D();

	// テクスチャを一括描画
	for (int i = 0; i < TITLE_TEX_MAX; i++)
	{
		m_Texture[i].DrawTexture();
	}

}

// テクスチャのサイズ・描画位置・色を個別で設定
void CModeTitle::SetTitleTexInf()
{
	//------------------- 背景
	m_Texture[TITLE_TEX_bg].SetTexSize(SCREEN_SIZE);		// サイズをセット
	m_Texture[TITLE_TEX_bg].SetTexPos(SCREEN_CENTER);		// 描画位置をセット
	m_Texture[TITLE_TEX_bg].SetTexColor(TITLE_BG_COLOR);	// 頂点色をセット

	//------------------- ロゴ
	m_Texture[TITLE_TEX_logo].SetTexSize(TITLE_LOGO_SIZE);		// サイズをセット
	m_Texture[TITLE_TEX_logo].SetTexPos(TITLE_LOGO_POS);		// 描画位置をセット
	m_Texture[TITLE_TEX_logo].SetTexColor(TITLE_LOGO_COLOR);	// 頂点色をセット

}

