//=============================================================================
// 背景処理 [bg.cpp]
// Author : 杉本幸宏
//=============================================================================
#include "main.h"
#include "bg.h"

#include "renderer.h"
#include "texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_NUM			(1)			// 使用テクスチャの数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11ShaderResourceView		*g_Texture[TEXTURE_NUM] = { NULL };			// テクスチャ情報

static int							g_TexNo;					// テクスチャ番号

// テクスチャのファイル名
static char* g_TextureName[] = {
	"data/TEXTURE/bg_game.jpg",
};

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBg(void)
{
	//テクスチャ生成
	for (int i = 0; i < TEXTURE_NUM; i++)
	{
		g_Texture[i] = NULL;
		D3DX11CreateShaderResourceViewFromFile(
			GetDevice(),
			g_TextureName[i],
			NULL,
			NULL,
			&g_Texture[i],
			NULL);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBg(void)
{
	for (int i = 0; i < TEXTURE_NUM; i++)
	{
		// テクスチャの解放
		if (g_Texture[i])
		{
			g_Texture[i]->Release();
			g_Texture[i] = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBg(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBg(void)
{
	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[0]);

	// １枚のポリゴンの頂点とテクスチャ座標を設定
	SetVertex(0.0f, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

	// ポリゴン描画
	GetDeviceContext()->Draw(4, 0);
}
