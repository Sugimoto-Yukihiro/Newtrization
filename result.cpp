//=============================================================================
//
// リザルト画面処理 [result.cpp]
// Author : 杉本幸宏
//
//=============================================================================
#include "main.h"
#include "result.h"

#include "fade.h"		// フェード処理
#include "input.h"		// キー・ゲームパッド入力処理
#include "renderer.h"	// レンダリング処理
#include "sound.h"		// サウンド
#include "texture.h"	// スプライト

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NEXT_MODE		MODE_TITLE		// 次のモード

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
//static ID3D11ShaderResourceView	*g_Texture[RESULT_TEXTURE_MAX] = { NULL };	// テクスチャ情報

// 使用テクスチャのファイル名(ゲームクリア時)
static char *g_TextureGameClear[TEXTURE_MAX_CLEAR] = {
	"data/TEXTURE/Result/bg_result.png",	// TexNo：0
	"data/TEXTURE/Result/result_logo.png",	// TexNo：1
};

// 使用テクスチャのファイル名(ゲームオーバー時)
static char *g_TextureGameOver[TEXTURE_MAX_GAMEOVER] = {
	"data/TEXTURE/Result/bg_result.png",	// TexNo：0
	"data/TEXTURE/Result/result_logo.png",	// TexNo：1
};

//=============================================================================
// 初期化処理
//=============================================================================
void CModeResult::Init()
{
	//------------------- メンバインスタンスの初期化
	for (int i = 0; i < RESULT_TEXTURE_MAX; i++)
	{
		m_Texture[i].Init();	// テクスチャ
	}
	m_Score.Init(RESULT_TEX_NAME_SCORE, RESULT_TEX_SIZE_SCORE);	// スコア
	m_CreaFlag = false;	// ゲームオーバーで初期化

	// BGM再生
//	PlaySound(SOUND_LABEL_BGM_sample002);
}



//=============================================================================
// 終了処理
//=============================================================================
void CModeResult::Uninit()
{
	//------------------- メンバインスタンスの終了処理
	for (int i = 0; i < RESULT_TEXTURE_MAX; i++)
	{
		m_Texture[i].Uninit();				// テクスチャの終了処理
		m_Texture[i].ReleaseTextureInf();	// テクスチャの解放
	}
	m_Score.Uninit();	// スコアの終了処理

}

//=============================================================================
// 更新処理
//=============================================================================
void CModeResult::Update()
{
	//------------------- キー・ゲームパットでの入力で次のモードへ
#ifdef KEY_MODE_CHANGE
	if (KEY_MODE_CHANGE)
	{// Enter押したら、ステージを切り替える
		SetFade(FADE_OUT, NEXT_MODE);	// フェードして次のモードへ
	//	SetMode(NEXT_MODE);				// 次のモードにシーン遷移
	}
	// ゲームパッドで入力処理
	else if (PAD_MODE_CHANGE)
	{
		SetFade(FADE_OUT, NEXT_MODE);	// フェードして次のモードへ
	//	SetMode(NEXT_MODE);				// 次のモードにシーン遷移
	}
#endif // KEY_MODE_CHANGE



	/* 以下、各テクスチャごとに更新処理があれば記入 */



}

//=============================================================================
// 描画処理
//=============================================================================
void CModeResult::Draw()
{
	// 描画の前準備
	PresetDraw2D();

	// 全てのテクスチャの描画
	if (m_CreaFlag)
	{	// ゲームクリア時のテクスチャ描画
		for (int i = 0; i < TEXTURE_MAX_CLEAR; i++)
		{
			m_Texture[i].DrawTexture();
		}

	}
	else
	{	// ゲームオーバ時のテクスチャ描画
		for (int i = 0; i < TEXTURE_MAX_GAMEOVER; i++)
		{
			m_Texture[i].DrawTexture();
		}

	}

}


// ゲームクリア時に使用するテクスチャの生成
void CModeResult::CreateTextureGameClear()
{
	// 使用するテクスチャを一括生成
	for (int i = 0; i < TEXTURE_MAX_CLEAR; i++)
	{
		// テクスチャ生成
		m_Texture[i].CreateTextureInf(g_TextureGameClear[i]);
	}

}

// ゲームクリア時に使用するテクスチャの解放
void CModeResult::ReleaseTextureGameClear()
{
	// 使用したテクスチャを一括生成
	for (int i = 0; i < TEXTURE_MAX_CLEAR; i++)
	{
		// テクスチャ解放
		m_Texture[i].ReleaseTextureInf();
	}

}


// ゲームオーバー時に使用するテクスチャの生成
void CModeResult::CreateTextureGameOver()
{
	// 使用するテクスチャを一括生成
	for (int i = 0; i < TEXTURE_MAX_GAMEOVER; i++)
	{
		// テクスチャ生成
		m_Texture[i].CreateTextureInf(g_TextureGameOver[i]);
	}

}

// ゲームオーバー時に使用するテクスチャの解放
void CModeResult::ReleaseTextureGameOver()
{
	// 使用したテクスチャを一括生成
	for (int i = 0; i < TEXTURE_MAX_GAMEOVER; i++)
	{
		// テクスチャ解放
		m_Texture[i].ReleaseTextureInf();
	}

}

