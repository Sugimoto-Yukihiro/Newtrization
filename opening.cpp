//=============================================================================
//
// タイトル画面処理 [opening.cpp]
// Author : 立石大智
//
//=============================================================================
#include "main.h"
#include "opening.h"

#include "renderer.h"
#include "input.h"		// キー・ゲームパッド入力
#include "fade.h"		// フェード
//#include "sound.h"	// サウンド
#include "texture.h"	// スプライト処理



//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_WIDTH				(SCREEN_WIDTH)	// 背景サイズ
#define TEXTURE_HEIGHT				(SCREEN_HEIGHT)	// 
#define TEXTURE_MAX					(1)				// テクスチャの数

#define TEXTURE_WIDTH_LOGO			(480)			// ロゴサイズ
#define TEXTURE_HEIGHT_LOGO			(80)			// 

#define NEXT_MODE					MODE_TITLE		// 次のモード
#define KEY_MODE_CHANGE				GetKeyboardTrigger(DIK_RETURN)
#define PAD_MODE_CHANGE				IsButtonTriggered(0, BUTTON_START) || IsButtonTriggered(0, BUTTON_B)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer				*g_VertexBuffer = NULL;				// 頂点情報
static ID3D11ShaderResourceView	*g_Texture[TEXTURE_MAX] = { NULL };	// テクスチャ情報

static char *g_TexturName[] = {
	"data/TEXTURE/bg_opening.jpg",
};

//=============================================================================
// 初期化処理
//=============================================================================
void CModeOpening::Init()
{
	// オープニングで使用するテクスチャとバッファを生成
	CreateOpeningTextureAndBuffer();

	m_Logo.Init();	// ロゴの初期化
	
}

//=============================================================================
// 終了処理
//=============================================================================
void CModeOpening::Uninit(void)
{
	// テクスチャとバッファの解放
	ReleaseOpeningTextureAndBuffer();
}

//=============================================================================
// 更新処理
//=============================================================================
void CModeOpening::Update(void)
{
	//------------------- キー・ゲームパットでの入力で次のモードへ
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

	if (m_bflag_beta == true)
	{
		m_fbeta -= 0.02f;
		if (m_fbeta <= 0.0f)
		{
			m_fbeta = 0.0f;
			m_bflag_beta = false;
		}
	}
	else
	{
		m_fbeta += 0.02f;
		if (m_fbeta >= 1.0f)
		{
			m_fbeta = 1.0f;
			m_bflag_beta = true;
		}
	}

#ifdef _DEBUG	// デバッグ情報を表示する
	//char *str = GetDebugStr();
	//sprintf(&str[strlen(str)], " PX:%.2f PY:%.2f", g_Pos.x, g_Pos.y);
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void CModeOpening::Draw(void)
{
	// 描画の前準備
	PresetDrawOpening();

	// テクスチャ描画
	m_Logo.DrawTexture(g_VertexBuffer, g_Texture[0]);

}



void CreateOpeningTextureAndBuffer()
{
	//テクスチャ生成
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		
	}

	// 頂点バッファ生成
	CreateVertexBuffer(&g_VertexBuffer);
}

void ReleaseOpeningTextureAndBuffer()
{
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (g_Texture[i])
		{
			g_Texture[i]->Release();
			g_Texture[i] = NULL;
		}
	}

}

void PresetDrawOpening(void)
{
	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// マトリクス設定
	SetWorldViewProjection2D();

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);
}
