//=============================================================================
//
// リザルト画面処理 [result.h]
// Author : 杉本幸宏
//
//=============================================================================
#pragma once

#include "texture.h"	// テクスチャ
#include "score.h"		// スコア

//*****************************************************************************
// 使用テクスチャの一覧
//*****************************************************************************
enum
{	// ゲームクリア時に使用してるテクスチャ
	GAMECLEAR_TEX_bg,		// 背景
	GAMECLEAR_TEX_logo,		// "Result"のロゴ

	TEXTURE_MAX_CLEAR
};

enum
{	// ゲームオーバー時に使用してるテクスチャ
	GAMEOVER_TEX_bg,		// 背景
	GAMEOVER_TEX_logo,		// "GAMEOVER"のロゴ

	TEXTURE_MAX_GAMEOVER
};

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define RESULT_TEXTURE_MAX		(TEXTURE_MAX_CLEAR)	// 使用するテクスチャの最大数

//------------------- "Result"ロゴ
#define RESULT_LOGO_SIZE		D3DXVECTOR2(700.0f, 200.0f)			// ロゴサイズ
#define RESULT_LOGO_POS			D3DXVECTOR2(480.0f, 150.0f)			// ロゴ位置
#define RESULT_LOGO_COLOR		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)	// ロゴの色

//------------------- スコア表示
#define RESULT_TEX_NAME_SCORE	"data/TEXTURE/score/0829_Score_Number.png"	// スコアのテクスチャ名
#define RESULT_TEX_SIZE_SCORE	D3DXVECTOR2(80.0f, 80.0f)		// スコアの表示サイズ
#define RESULT_TEX_POS_SCORE	D3DXVECTOR2(480.0f + (80.0f * 2.0f), 320.0f)		// スコアの表示位置

//------------------- "GANEOVER"表示
#define RESULT_LOGO_GAMEOVER_SIZE	D3DXVECTOR2(900.0f, 500.0f)			// ロゴサイズ
#define RESULT_LOGO_GAMEOVER_POS	D3DXVECTOR2(480.0f, 320.0f)			// ロゴ位置
#define RESULT_LOGO_GAMEOVER_COLOR	D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f)	// ロゴの色


//*****************************************************************************
// クラス定義
//*****************************************************************************
class CModeResult
{
public:
	void Init();	// 初期化処理
	void Uninit();	// 終了処理
	void Update();	// 更新処理
	void Draw();	// 描画処理

	// リザルトで表示するスコアのセット
	void SetResultScore(int Score) {m_Score.SetScore(Score); };
	void ScoreInit() { m_Score.Init(RESULT_TEX_NAME_SCORE, RESULT_TEX_SIZE_SCORE); } ;

	// ゲームクリアフラグのセット
	void SetCreaFlag(bool Flag) { m_CreaFlag = Flag; };

	// ゲームクリア時に使用するテクスチャの生成・解放
	void CreateTextureGameClear();
	void ReleaseTextureGameClear();

	// ゲームオーバー時に使用するテクスチャの生成・解放
	void CreateTextureGameOver();
	void ReleaseTextureGameOver();

private:
	CTexture m_Texture[RESULT_TEXTURE_MAX];	// テクスチャインスタンス
	CScore m_Score;		// リザルト表示するスコア
	int m_nUseTexNum;	// 使用しているテクスチャの数
	bool m_CreaFlag;	// ゲームクリアのフラグ
};
