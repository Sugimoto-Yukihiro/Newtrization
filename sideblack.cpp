//=============================================================================
//
// 画面端を黒くする処理 [sideblack.cpp]
// Author : 杉本幸宏
//
//=============================================================================

#include "main.h"
#include "sideblack.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SIZE_SIDEBLACK		D3DXVECTOR2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT)	// スクリーンの大きさを設定

//*****************************************************************************
// グローバル変数
//*****************************************************************************


//=============================================================================
// コンストラクタ・デストラクタ
//=============================================================================
CSideBlack::CSideBlack()	// コンストラクタ
{

}

CSideBlack::~CSideBlack()	// デストラクタ
{

}



//=============================================================================
// 初期化処理
//=============================================================================
void CSideBlack::Init(char* TextureFileName)
{
	// テクスチャ生成
//	CreateSideBlackTexture();
	CreateTexture(TextureFileName, &m_Texture);	// テクスチャ情報生成

	// テクスチャクラスの初期化処理
	m_SideBlackTexture.Init(ZERO_VECTOR2, SIZE_SIDEBLACK);	// 大きさはスクリーンの幅、描画位置は左上（つまり, x:0.0f y:0.0f）

}



//=============================================================================
// 終了処理
//=============================================================================
void CSideBlack::Uninit()
{
	// テクスチャクラスの終了処理
	m_SideBlackTexture.Uninit();		// 終了処理実行

	// テクスチャ解放
//	ReleaseSideBlackTexture();
	if (ReleaseTexture(m_Texture)) {	// テクスチャ情報解放
		m_Texture = NULL;				// 解放処理が実行されていたら NULLをセット
	}

}


//=============================================================================
// 更新処理
//=============================================================================
void CSideBlack::Update()
{


}



//=============================================================================
// 描画処理
//=============================================================================
void CSideBlack::Draw()
{
	// テクスチャの描画
	m_SideBlackTexture.DrawTextureTopLeft(m_Texture);	// 描画実行
}



//// テクスチャの生成
//void CreateSideBlackTexture(void)
//{
//	// テクスチャ情報を生成
//	CreateTexture(g_TextureName, &g_Texture);	// テクスチャ生成実行
//}
//
//// テクスチャの解放
//void ReleaseSideBlackTexture(void)
//{
//	// 全てのテクスチャ情報を解放
//	ReleaseTexture(&g_Texture);	// テクスチャ解放
//}