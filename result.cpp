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
	"data/TEXTURE/Result/bg_result.png",
	"data/TEXTURE/Result/0829_Result.png",
};

// 使用テクスチャのファイル名(ゲームオーバー時)
static char *g_TextureGameOver[TEXTURE_MAX_GAMEOVER] = {
	"data/TEXTURE/fade_black.png",	// 背景
	"data/TEXTURE/Result/0829_GameOver.png",
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

//	m_Score.Init(RESULT_TEX_NAME_SCORE, RESULT_TEX_SIZE_SCORE);	// スコアの初期化

	// ゲームのクリア状態によって処理を変える
	if (m_CreaFlag)
	{	// ゲームクリア
		CreateTextureGameClear();					// 使用するテクスチャを生成
		PlaySound(SOUND_LABEL_BGM_result_CLEAR);	// ゲームクリア時のBGM再生
	}
	else
	{	// ゲームオーバー
		CreateTextureGameOver();					// 使用するテクスチャを生成
		PlaySound(SOUND_LABEL_BGM_result_FAILED);	// ゲームオーバー時のBGM再生
	}

}



//=============================================================================
// 終了処理
//=============================================================================
void CModeResult::Uninit()
{
	// サウンド停止
	StopSound();

	//------------------- メンバインスタンスの終了処理
	// スコアの終了処理
	m_Score.Uninit();

	// テクスチャの終了処理
	for (int i = 0; i < RESULT_TEXTURE_MAX; i++)
	{
		m_Texture[i].Uninit();				// テクスチャの終了処理
		m_Texture[i].ReleaseTextureInf();	// テクスチャの解放
	}

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

#ifdef _DEBUG
	
#endif // _DEBUG


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

		// スコアの表示
		m_Score.Draw(RESULT_TEX_POS_SCORE);
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

	// 個別にサイズ・位置を指定
	//------------------- 背景
	m_Texture[GAMECLEAR_TEX_bg].SetTexSize(SCREEN_SIZE);	// 大きさはスクリーンの大きさ
	m_Texture[GAMECLEAR_TEX_bg].SetTexPos(SCREEN_CENTER);	// 座標はスクリーンの中心

	//------------------- ロゴ("Result")
	m_Texture[GAMECLEAR_TEX_logo].SetTexSize(RESULT_LOGO_SIZE);		// 大きさはスクリーンの大きさ
	m_Texture[GAMECLEAR_TEX_logo].SetTexPos(RESULT_LOGO_POS);		// 座標はスクリーンの中心
	m_Texture[GAMECLEAR_TEX_logo].SetTexColor(RESULT_LOGO_COLOR);	// 色を指定

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

	// 個別にサイズ・位置を指定
	//------------------- 背景
	m_Texture[GAMECLEAR_TEX_bg].SetTexSize( SCREEN_SIZE );	// 大きさはスクリーンの大きさ
	m_Texture[GAMECLEAR_TEX_bg].SetTexPos( SCREEN_CENTER );	// 座標はスクリーンの中心

	//------------------- ロゴ("GANEOVER")
	m_Texture[GAMEOVER_TEX_logo].SetTexSize(RESULT_LOGO_GAMEOVER_SIZE);	// 大きさはスクリーンの大きさ
	m_Texture[GAMEOVER_TEX_logo].SetTexPos(RESULT_LOGO_GAMEOVER_POS);		// 座標はスクリーンの中心
	m_Texture[GAMEOVER_TEX_logo].SetTexColor(RESULT_LOGO_GAMEOVER_COLOR);	// 色を指定

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

