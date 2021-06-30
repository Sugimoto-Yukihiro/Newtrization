//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : GP11A132 24 立石大智
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
static ID3D11Buffer				*g_VertexBuffer = NULL;		// 頂点情報
static ID3D11ShaderResourceView	*g_Texture[TEXTURE_MAX] = { NULL };	// テクスチャ情報

static char *g_TexturName[] = {
	"data/TEXTURE/player.png",
};

static PLAYER	g_Player[PLAYER_MAX];						// エネミー構造体


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	ID3D11Device *pDevice = GetDevice();

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


	// プレイヤー構造体の初期化
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		g_Player[i].use = true;
		g_Player[i].w   = TEXTURE_WIDTH;
		g_Player[i].h   = TEXTURE_HEIGHT;
		g_Player[i].pos = D3DXVECTOR3(500.0f, 500.0f, 0.0f);	// 中心点から表示にした
		g_Player[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Player[i].texNo = 0;

		g_Player[i].countAnim = 0;
		g_Player[i].patternAnim = 0;

	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
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
void UpdatePlayer(void)
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (g_Player[i].use == true)	// このプレイヤーが使われている？
		{								// Yes
			// アニメーション  (wait値)
			g_Player[i].countAnim++;
			if ((g_Player[i].countAnim % ANIM_WAIT) == 0)
			{
				// パターンの切り替え
				g_Player[i].patternAnim = (g_Player[i].patternAnim + 1) % ANIM_PATTERN_NUM;
			}

			// キー入力で移動 
			if (GetKeyboardPress(DIK_DOWN))
			{
				g_Player[i].pos.y += 10.0f;
			}
			else if (GetKeyboardPress(DIK_UP))
			{
				g_Player[i].pos.y -= 10.0f;
			}
			if (GetKeyboardPress(DIK_RIGHT))
			{
				g_Player[i].pos.x += 10.0f;
			}
			else if (GetKeyboardPress(DIK_LEFT))
			{
				g_Player[i].pos.x -= 10.0f;
			}

			// ゲームパッドでで移動処理
			if (IsButtonPressed(0, BUTTON_DOWN))
			{
				g_Player[i].pos.y += 2.0f;
			}
			else if (IsButtonPressed(0, BUTTON_UP))
			{
				g_Player[i].pos.y -= 2.0f;
			}

			if (IsButtonPressed(0, BUTTON_RIGHT))
			{
				g_Player[i].pos.x += 2.0f;
			}
			else if (IsButtonPressed(0, BUTTON_LEFT))
			{
				g_Player[i].pos.x -= 2.0f;
			}

			// 弾発射
		    // if (GetKeyboardTrigger(DIK_SPACE))	// トリガーだと単発
			if (GetKeyboardPress(DIK_SPACE))	    // プレスだと連射
			{
				D3DXVECTOR3 pos = g_Player[i].pos;
				//pos.y += g_Player[i].h/2;			// プレイヤーの足元の位置から発射
			//	SetBullet(pos);						// １発目
			}

		}

		//	//プレイヤーを左右に移動
		//	if (player[i].left == true)
		//	{	//左へ移動
		//		player[i].pos.x -= PLAYER_SPEED;

		//		//左端？
		//		float pLeft = player[i].pos.x - (player[i].w / 2);
		//		if (pLeft <= 0.0f)
		//		{
		//			player[i].left = false;//次は右
		//		}
		//	}
		//	else
		//	{	//右へ移動
		//		player[i].pos.x += PLAYER_SPEED;

		//		//左端？
		//		float pRight = player[i].pos.x + (player[i].w / 2);
		//		if (pRight >= SCREEN_WIDTH)
		//		{
		//			player[i].left = true;
		//		}
		//	}

		//	//プレイヤーを左右に移動
		//	if (player[i].down == true)
		//	{	//下へ移動
		//		player[i].pos.y -= PLAYER_SPEED;

		//		//下端？
		//		float pDown = player[i].pos.y - (player[i].h / 2);
		//		if (pDown <= 0.0f)
		//		{
		//			player[i].down = false;//次は上
		//		}
		//	}
		//	else
		//	{	//上へ移動
		//		player[i].pos.y += PLAYER_SPEED;

		//		//上端？
		//		float pUp = player[i].pos.y + (player[i].h / 2);
		//		if (pUp >= SCREEN_HEIGHT)
		//		{
		//			player[i].down = true;
		//		}
		//	}

	}

#ifdef _DEBUG	// デバッグ情報を表示する
//	char *str = GetDebugStr();
//	sprintf(&str[strlen(str)], " PX:%.2f PY:%.2f", g_Player[0].pos.x, g_Player[0].pos.y);
	
#endif

}

//=============================================================================
// 描画処理
//=============================================================================
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
		if (g_Player[i].use == true)		// このプレイヤーが使われている？
		{									// Yes
			// テクスチャ設定
			GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[g_Player[i].texNo]);

			//プレイヤーの位置やテクスチャー座標を反映
			float px = g_Player[i].pos.x;	// プレイヤーの表示位置X
			float py = g_Player[i].pos.y;	// プレイヤーの表示位置Y
			float pw = g_Player[i].w;		// プレイヤーの表示幅
			float ph = g_Player[i].h;		// プレイヤーの表示高さ

			float tw = 1.0f / TEXTURE_PATTERN_DIVIDE_X;	// テクスチャの幅
			float th = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;	// テクスチャの高さ
			float tx = (float)(g_Player[i].patternAnim % TEXTURE_PATTERN_DIVIDE_X) * tw;	// テクスチャの左上X座標
			float ty = (float)(g_Player[i].patternAnim / TEXTURE_PATTERN_DIVIDE_X) * th;	// テクスチャの左上Y座標

			// １枚のポリゴンの頂点とテクスチャ座標を設定
			SetSpriteColorRotation(g_VertexBuffer, px, py, pw, ph, tx, ty, tw, th,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				g_Player[i].rot.z);

			// ポリゴン描画
			GetDeviceContext()->Draw(4, 0);
		}
	}
}


//=============================================================================
// プレイヤーの座標を取得
//=============================================================================
D3DXVECTOR3 GetPlayerPosition(void)
{
	return g_Player[0].pos;
}


//=============================================================================
// プレイヤー構造体の先頭アドレスを取得
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_Player[0];
}
