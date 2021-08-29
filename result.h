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
// マクロ定義
//*****************************************************************************
#define TEXTURE_MAX_CLEAR		(4)
#define TEXTURE_MAX_GAMEOVER	(3)
#define RESULT_TEXTURE_MAX		TEXTURE_MAX_CLEAR

#define RESULT_TEX_NAME_SCORE	"data/TEXTURE/score/number.png"	// スコアのテクスチャ名
#define RESULT_TEX_SIZE_SCORE	D3DXVECTOR2(35.0f, 35.0f)		// スコアの表示サイズ
#define RESULT_TEX_POS_SCORE	SCREEN_CENTER					// スコアの表示位置

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
	bool m_CreaFlag;	// ゲームクリアのフラグ
};
