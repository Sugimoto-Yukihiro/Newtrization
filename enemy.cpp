//=============================================================================
//
// エネミー処理 [enemy.cpp]
// Author : 稲垣佑二郎
//
//=============================================================================
#include "enemy.h"
#include "texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_WIDTH				(128)	// キャラサイズ
#define TEXTURE_HEIGHT				(192)	// 
#define TEXTURE_MAX					(1)		// テクスチャの数

#define TEXTURE_PATTERN_DIVIDE_X	(6)		// アニメパターンのテクスチャ内分割数（X)
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
	"data/TEXTURE/enemy/enemy01.png",
};

static ENEMY g_Enemy[ENEMY_MAX];							// エネミー構造体

// エネミーの線形移動用の移動座標テーブル
static D3DXVECTOR3 g_MoveTbl[] = {
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	D3DXVECTOR3(200.0f, 0.0f, 0.0f),
	D3DXVECTOR3(200.0f, 200.0f, 0.0f),
};

// エネミーの線形移動用の移動スピードテーブル
static float g_MoveSpd[] = {
	0.01f,
	0.01f,
	0.01f,
};


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy(void)
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


	// エネミー構造体の初期化
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		g_Enemy[i].use   = true;
		g_Enemy[i].w     = TEXTURE_WIDTH;
		g_Enemy[i].h     = TEXTURE_HEIGHT;
		g_Enemy[i].pos   = D3DXVECTOR3(200.0f+i*150, 300.0f, 0.0f);
		g_Enemy[i].rot   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[i].texNo = 0;

		g_Enemy[i].countAnim = 0;
		g_Enemy[i].patternAnim = 0;

		g_Enemy[i].time = 0.0f;

	}
	

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
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
void UpdateEnemy(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].use == true)		// このエネミーが使われている？
		{								// Yes
			// アニメーション  
			g_Enemy[i].countAnim++;
			if ((g_Enemy[i].countAnim % ANIM_WAIT) == 0)
			{
				// パターンの切り替え
				g_Enemy[i].patternAnim = (g_Enemy[i].patternAnim + 1) % ANIM_PATTERN_NUM;
			}

			if (i == 0)
			{	// エネミー０番だけテーブルに従って座標移動（線形移動）
				int nowNo = (int)g_Enemy[i].time;		// 整数分であるテーブルを取り出している
				int maxNo = (sizeof(g_MoveTbl) / sizeof(D3DXVECTOR3));	// 登録テーブル数を数えている
				int nextNo = (nowNo + 1) % maxNo;						// 移動先テーブルの番号を求めている
				D3DXVECTOR3 pos = g_MoveTbl[nextNo] - g_MoveTbl[nowNo];	// XYZ移動量を計算している
				float nowTime = g_Enemy[i].time - nowNo;				// 時間部分である少数を取り出している
				pos *= nowTime;											// 現在の移動量を計算している

				// 計算して求めた移動量を現在の移動テーブルXYZに足している
				g_Enemy[i].pos = g_MoveTbl[nowNo] + pos;

				g_Enemy[i].time += g_MoveSpd[nowNo];					// 時間を進めている
				if ((int)g_Enemy[i].time >= maxNo)						// 登録テーブル最後まで移動したか？
				{
					g_Enemy[i].time -= maxNo;							// ０番目にリセットしつつも少数部分を引き継いでいる
				}

			}
		}
	}



#ifdef _DEBUG	// デバッグ情報を表示する
	//char *str = GetDebugStr();
	//sprintf(&str[strlen(str)], " EX:%.2f EY:%.2f", g_Enemy[0].Pos.x, g_Enemy[0].Pos.y);
	
#endif

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
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

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].use == true)		// このエネミーが使われている？
		{								// Yes
			// テクスチャ設定
			GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[g_Enemy[i].texNo]);

			//エネミーの位置やテクスチャー座標を反映
			float px = g_Enemy[i].pos.x;	// エネミーの表示位置X
			float py = g_Enemy[i].pos.y;	// エネミーの表示位置Y
			float pw = g_Enemy[i].w;		// エネミーの表示幅
			float ph = g_Enemy[i].h;		// エネミーの表示高さ

			float tw = 1.0f / TEXTURE_PATTERN_DIVIDE_X;	// テクスチャの幅
			float th = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;	// テクスチャの高さ
			float tx = (float)(g_Enemy[i].patternAnim % TEXTURE_PATTERN_DIVIDE_X) * tw;	// テクスチャの左上X座標
			float ty = (float)(g_Enemy[i].patternAnim / TEXTURE_PATTERN_DIVIDE_X) * th;	// テクスチャの左上Y座標

			// １枚のポリゴンの頂点とテクスチャ座標を設定
			SetSpriteColorRotation(g_VertexBuffer, px, py, pw, ph, tx, ty, tw, th,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				g_Enemy[i].rot.z);

			// ポリゴン描画
			GetDeviceContext()->Draw(4, 0);
		}
	}

}


//=============================================================================
// エネミー構造体の先頭アドレスを取得
//=============================================================================
ENEMY *GetEnemy(void)
{
	return &g_Enemy[0];
}


