//==================================================================
//
// マップチップ処理 [mapchip.cpp]
// Auther : 杉本幸宏
//
//==================================================================

#include "main.h"
#include "renderer.h"
#include "mapchip.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_MAX		(1)		// 使用テクスチャの数


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer				*g_VertexBuffer = NULL;				// 頂点情報
static ID3D11ShaderResourceView	*g_Texture[TEXTURE_MAX] = { NULL };	// テクスチャ情報

static char *g_TexturName[] = {
	"data/TEXTURE/player.png",
};


//=============================================================================
// コンストラクタ
//=============================================================================
CMapchip::CMapchip()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CMapchip::~CMapchip()
{

}



//=============================================================================
// 初期化処理
//=============================================================================
void CMapchip::Init()
{


}

void InitMapchip()
{
	// テクスチャ生成
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
void CMapchip::Uninit()
{

}

void UninitMapchip()
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
void CMapchip::Update()
{

}


void UpdateMapchip()
{

}



//=============================================================================
// 描画処理
//=============================================================================
void CMapchip::Draw()
{

}


void DrawMapchip()
{

}



//=============================================================================
// ゲッター関数
//=============================================================================
// 指定された座標にあるチップ番号を取得
int CMapchip::GetMapchipNo(D3DXVECTOR2 Pos)
{
	int cx = (int)Pos.x / m_vChipSize.x;
	int cy = (int)Pos.y / m_vChipSize.y;

	return m_pMapChipData[cx + (cy * m_nChipNumX)];
}

