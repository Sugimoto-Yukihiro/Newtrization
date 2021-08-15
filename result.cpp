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
//#include "sound.h"	// サウンド
#include "texture.h"		// スプライト
//#include "score.h"	// スコア

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NEXT_MODE					MODE_TITLE		// 次のモード

#define TEXTURE_SIZE_BG				D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT)	// 背景サイズ

#define TEXTURE_WIDTH_LOGO			(480)			// ロゴサイズ
#define TEXTURE_HEIGHT_LOGO			(80)			// 

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11ShaderResourceView	*g_Texture[RESULT_TEX_PATTARN_MAX] = { NULL };	// テクスチャ情報

static char *g_TexturName[] = {	// 使用テクスチャのファイル名
	/* 【重要】ここの順番は、ヘッダーに記載されてるenumの順番と揃えること！！！！！ */
	"data/TEXTURE/bg_result.png",	// TexNo：0
	"data/TEXTURE/logo_result.png",	// TexNo：1
};



//=============================================================================
// 初期化処理
//=============================================================================
void CModeResult::Init()
{
	//------------------- テクスチャ生成
	for (int i = 0; i < RESULT_TEX_PATTARN_MAX; i++)
	{
		CreateTexture(g_TexturName[i], &g_Texture[i]);	// 生成
	}

	//------------------- メンバ変数の初期化
	m_Tex[RESULT_TEX_Bg].SetTexSize( TEXTURE_SIZE_BG );	// 背景のサイズをセット
	m_Tex[RESULT_TEX_Bg].SetTexPos( SCREEN_CENTER );	// 背景のサイズをセット

	// BGM再生
//	PlaySound(SOUND_LABEL_BGM_sample002);
}



//=============================================================================
// 終了処理
//=============================================================================
void CModeResult::Uninit()
{
	//------------------- Init()で生成したテクスチャを解放
	for (int i = 0; i < RESULT_TEX_PATTARN_MAX; i++)
	{
		ReleaseTexture(&g_Texture[i]);	// 解放
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



}

//=============================================================================
// 描画処理
//=============================================================================
void CModeResult::Draw()
{
	// 描画の前準備
	PresetDraw2D();

	// 全てのテクスチャの描画
	for (int i = 0; i < RESULT_TEX_PATTARN_MAX; i++)
	{
		m_Tex[i].DrawTexture(g_Texture[i]);	// 描画実行
	}

}

