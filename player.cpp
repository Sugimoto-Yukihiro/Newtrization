//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 立石大智, 杉本幸宏
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "player.h"
#include "sprite.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_WIDTH				(200/2)	// キャラサイズ
#define TEXTURE_HEIGHT				(200/2)	// 
#define TEXTURE_MAX					(1)		// テクスチャの数

#define TEXTURE_PATTERN_DIVIDE_X	(3)		// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y	(1)		// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define ANIM_WAIT					(4)		// アニメーションの切り替わるWait値


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer				*g_VertexBuffer = NULL;				// 頂点情報
static ID3D11ShaderResourceView	*g_Texture[TEXTURE_MAX] = { NULL };	// テクスチャ情報

static char *g_TexturName[] = {
	"data/TEXTURE/player.png",
};

static CPlayer	g_aPlayer[PLAYER_MAX];								// プレイヤーインスタンス

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer()
{
	// プレイヤー構造体の初期化
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		g_aPlayer[i].use = true;
		g_aPlayer[i].w   = TEXTURE_WIDTH;
		g_aPlayer[i].h   = TEXTURE_HEIGHT;
		g_aPlayer[i].pos = D3DXVECTOR3(500.0f, 500.0f, 0.0f);	// 中心点から表示にした
		g_aPlayer[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayer[i].texNo = 0;

		g_aPlayer[i].countAnim = 0;
		g_aPlayer[i].patternAnim = 0;
	}
}

void InitPlayer()
{
	//テクスチャ生成
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		g_Texture[i] = NULL;
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TexturName[i],
			NULL,
			NULL,
			&g_Texture[i],
			NULL);
	}


	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);
}

//=============================================================================
// 終了処理
//=============================================================================
CPlayer::~CPlayer()
{

}

void UninitPlayer()
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


//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update()
{
	if (use == true)	// このプレイヤーが使われている？
	{								// Yes
		// アニメーション  (wait値)
		countAnim++;
		if ((countAnim % ANIM_WAIT) == 0)
		{
			// パターンの切り替え
			patternAnim = (patternAnim + 1) % ANIM_PATTERN_NUM;
		}

		// キー入力で移動 
		if (GetKeyboardPress(DIK_DOWN))
		{
			pos.y += 10.0f;
		}
		else if (GetKeyboardPress(DIK_UP))
		{
			pos.y -= 10.0f;
		}
		if (GetKeyboardPress(DIK_RIGHT))
		{
			pos.x += 10.0f;
		}
		else if (GetKeyboardPress(DIK_LEFT))
		{
			pos.x -= 10.0f;
		}

		// ゲームパッドでで移動処理
		if (IsButtonPressed(0, BUTTON_DOWN))
		{
			pos.y += 2.0f;
		}
		else if (IsButtonPressed(0, BUTTON_UP))
		{
			pos.y -= 2.0f;
		}

		if (IsButtonPressed(0, BUTTON_RIGHT))
		{
			pos.x += 2.0f;
		}
		else if (IsButtonPressed(0, BUTTON_LEFT))
		{
			pos.x -= 2.0f;
		}

	}

#ifdef _DEBUG	// デバッグ情報を表示する
//	char *str = GetDebugStr();
//	sprintf(&str[strlen(str)], " PX:%.2f PY:%.2f", g_aPlayer[0].pos.x, g_aPlayer[0].pos.y);
#endif

}

void UpdatePlayer(void)
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		g_aPlayer[i].Update();
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw()
{
	if (use == true)
		{
			// テクスチャ設定
			GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[texNo]);

			//プレイヤーの位置やテクスチャー座標を反映
			float px = pos.x;	// プレイヤーの表示位置X
			float py = pos.y;	// プレイヤーの表示位置Y
			float pw = w;		// プレイヤーの表示幅
			float ph = h;		// プレイヤーの表示高さ

			float tw = 1.0f / TEXTURE_PATTERN_DIVIDE_X;	// テクスチャの幅
			float th = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;	// テクスチャの高さ
			float tx = (float)(patternAnim % TEXTURE_PATTERN_DIVIDE_X) * tw;	// テクスチャの左上X座標
			float ty = (float)(patternAnim / TEXTURE_PATTERN_DIVIDE_X) * th;	// テクスチャの左上Y座標

			// １枚のポリゴンの頂点とテクスチャ座標を設定
			SetSpriteColorRotation(g_VertexBuffer, px, py, pw, ph, tx, ty, tw, th,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				rot.z);

			// ポリゴン描画
			GetDeviceContext()->Draw(4, 0);
		}
}


void DrawPlayer(void)
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


	for (int i = 0; i < PLAYER_MAX; i++)
	{
		g_aPlayer[i].Draw();
	}
}


//=============================================================================
// プレイヤー構造体の先頭アドレスを取得
//=============================================================================
//PLAYER *GetPlayer(void)
//{
//	return &g_aPlayer[0];
//}
