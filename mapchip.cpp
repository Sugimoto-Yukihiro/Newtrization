//==================================================================
//
// マップチップ処理 [mapchip.cpp]
// Auther : 杉本幸宏
//
//==================================================================

#include "main.h"
#include "renderer.h"
#include "mapchip.h"	// マップチップ
#include "game.h"		// ゲーム画面

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
	D3DXVECTOR2 ScrollPos;
	float offset_x, offset_y;
	int numx, numy, nDrawChipNumX, nDrawChipNumY;

	// 表示座標の取得("ScrollPos"→スクロール座標)
	ScrollPos = GetScrollPos();

	// 描画するマップチップの最左の表示座標の算出
	offset_x = numx * m_vChipSize.x - ScrollPos->x;	// 横位置
	offset_y = numy * m_vChipSize.y - ScrollPos->y;	// 縦位置


	//------------------- 描画するマップチップの最左のインデックス番号の算出
	numx = (int)ScrollPos->x / m_vChipSize.x;		// スクロール座標より左側（画面外）にあるマップチップ数
	numy = (int)ScrollPos->y / m_vChipSize.y;		// スクロール座標より上側（画面外）にあるマップチップ数

	// 描画するチップ数を算出
	nDrawChipNumX = SCREEN_WIDTH / m_vChipSize.x;	// 横方向(x軸)のチップ数
	nDrawChipNumY = SCREEN_HEIGHT / m_vChipSize.y;	// 縦方向(y軸)のチップ数

	// マップチップを一枚ずつ描画
	for (int iy = numy; iy < (numy + nDrawChipNumY); iy++)
	{
		for (int ix = numx; ix < (numx + nDrawChipNumX); ix++)
		{
			// マップの番号を取得
			int nChipId = m_pMapChipData[ (iy * m_nChipNumX) + ix];

			// チップの描画位置を算出
			D3DXVECTOR2 ChipCenterPos;
			ChipCenterPos.y = (float)(offset_y + (m_vChipSize.y * iy));		// 背景の表示座標Y
			ChipCenterPos.x = (float)(offset_x + (m_vChipSize.x  * ix));	// 背景の表示座標X

			ChipCenterPos.y += m_vChipSize.y * 0.5f;
			ChipCenterPos.x += m_vChipSize.x * 0.5f;

			// 描画
			DrawTexture(g_VertexBuffer, g_Texture[m_nTexNo]);	// 描画座標が中心指定のとき

		//	// 当たり判定処理のチップの場合 → 当たり判定のマップチップ変数を用意
		//	for (int i = 0; i < WALL_NUM_PATTARN; i++)
		//	{
		//		if (chip_id == WallNum[i])
		//		{
		//			// 座標を表示座標からワールド座標に変換
		//			VECTOR worldPos = ChipCenterPos;
		//			worldPos.ix += ScrollPos->ix;
		//			worldPos.y += ScrollPos->y;
		//			SetMapChipData(worldPos, chip_id, y, ix);	// マップチップ変数に情報を代入
		//		}
		//	}

		}
	}

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

