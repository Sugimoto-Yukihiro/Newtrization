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
#include "texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_WIDTH				(300.0f)	// キャラサイズ	X
#define TEXTURE_HEIGHT				(100.0f)	//				Y
#define TEXTURE_SIZE				D3DXVECTOR2(TEXTURE_WIDTH, TEXTURE_HEIGHT)	// キャラサイズ

#define TEXTURE_MAX					(1)			// テクスチャの数

#define TEXTURE_PATTERN_DIVIDE_X	(3)			// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y	(1)			// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define ANIM_WAIT					(4)			// アニメーションの切り替わるデフォルトWait値
#define MOVE_VALUE					(10.0f)

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
// コンストラクタ・デストラクタ
//=============================================================================
CPlayer::CPlayer()		// コンストラクタ
{
	// プレイヤークラスの初期化
	m_bUse = true;
	m_nTexNo = 0;
}

CPlayer::~CPlayer()		// デストラクタ
{

}

//=============================================================================
// 初期化処理
//=============================================================================
void CPlayer::Init()
{
	// プレイヤークラスの初期化
	m_bUse = true;
	m_nTexNo = 0;

	//------------------- ベースクラスの初期化
	CTexture::Init();	// CTexture

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

	// プレイヤークラス初期化
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		(g_aPlayer + i)->SetPlayerUseFlag(true);
		(g_aPlayer + i)->SetTextureInf(SCREEN_CENTER, TEXTURE_SIZE, DEFAULT_COLOR, 0.0f, ZERO_VECTOR2);
		(g_aPlayer + i)->SetAnimInf(1, 1, 10);
	}

}

//=============================================================================
// 終了処理
//=============================================================================
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
	if (m_bUse == true)	// このプレイヤーが使われている？
	{					// Yes
		// アニメーション
	//	UpdateAnimIndex(0, 0);	// 

		{
			D3DXVECTOR2 move;	// プレイヤーの値を保存する変数
			move = GetTexPos();	// 現在のプレイヤーの座標で初期化

			// キー入力で移動
			if (GetKeyboardPress(DIK_DOWN))
			{
				move.y += MOVE_VALUE;
			}
			else if (GetKeyboardPress(DIK_UP))
			{
				move.y -= MOVE_VALUE;
			}
			else if (GetKeyboardPress(DIK_RIGHT))
			{
				move.x += MOVE_VALUE;
			}
			else if (GetKeyboardPress(DIK_LEFT))
			{
				move.x -= MOVE_VALUE;
			}

			// ゲームパッドで移動処理
			if (IsButtonPressed(0, BUTTON_DOWN))
			{
				move.y += MOVE_VALUE;
			}
			else if (IsButtonPressed(0, BUTTON_UP))
			{
				move.y -= MOVE_VALUE;
			}
			else if (IsButtonPressed(0, BUTTON_RIGHT))
			{
				move.x += MOVE_VALUE;
			}
			else if (IsButtonPressed(0, BUTTON_LEFT))
			{
				move.x -= MOVE_VALUE;
			}

			// プレイヤーの最終的な座標をセット
			SetTexPos(move);
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
	if (m_bUse == true)
		{
			DrawTexture(g_VertexBuffer, g_Texture[0]);
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

	// プレイヤーの描画
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		g_aPlayer[i].Draw();
	}
}



//=============================================================================
// セッター関数
//=============================================================================
// プレイヤーのuseフラグのセット
void CPlayer::SetPlayerUseFlag(bool Use)
{
	m_bUse = Use;
}

// プレイヤーを殺す処理
void CPlayer::KillPlayer()
{
	// プレイヤーのuseフラグを折る
	SetPlayerUseFlag(false);

	/* プレイヤーが死んだ後に何か処理を行う場合はここに記入 */

}

//=============================================================================
// ゲッター関数
//=============================================================================
// プレイヤーのuseフラグの取得
bool CPlayer::GetPlayerUseFlag()
{
	return m_bUse;
}



//=============================================================================
// プレイヤー構造体の先頭アドレスを取得
//=============================================================================
//PLAYER *GetPlayer(void)
//{
//	return &g_aPlayer[0];
//}
