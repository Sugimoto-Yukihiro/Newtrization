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
//#define MAPCHIP_MAX		(1)		// 使用テクスチャの数

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer				*g_VertexBuffer = NULL;				// 頂点情報
static ID3D11ShaderResourceView	*g_Texture[MAPCHIP_MAX] = { NULL };	// テクスチャ情報

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void PresetDrawMapchip();	// 描画する前準備

// テクスチャのファイル名
static char *g_TexturName[] = {
	"data/TEXTURE/player.png",		// TexNo : 0
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



//=============================================================================
// 終了処理
//=============================================================================
void CMapchip::Uninit()
{

}



//=============================================================================
// 更新処理
//=============================================================================
void CMapchip::Update()
{

}



//=============================================================================
// 描画処理
//=============================================================================
void CMapchip::Draw()
{
	// 描画する前に呼び出す
	PresetDrawMapchip();

	D3DXVECTOR2 ScrollPos;
	float offset_x, offset_y;
	int numx, numy, nDrawChipNumX, nDrawChipNumY;

	// 表示座標の取得("ScrollPos"→スクロール座標)
//	ScrollPos.x = GetPlayerPos().x - SCROLL_SET_X;	// ここは仮。後で直す！
//	ScrollPos.x = GetPlayerPos().x - SCROLL_SET_X;	// ここは仮。後で直す！
	ScrollPos.x = 0.0f;	// ここは仮。後で直す！
	ScrollPos.x = 0.0f;	// ここは仮。後で直す！

	//------------------- 描画するマップチップの最左のインデックス番号の算出
	numx = (int)(ScrollPos.x / GetMapchipSize().x);		// スクロール座標より左側（画面外）にあるマップチップ数
	numy = (int)(ScrollPos.y / GetMapchipSize().y);		// スクロール座標より上側（画面外）にあるマップチップ数

	// 描画するマップチップの最左の表示座標の算出
	offset_x = (numx * GetMapchipSize().x) - ScrollPos.x;	// 横位置
	offset_y = (numy * GetMapchipSize().y) - ScrollPos.y;	// 縦位置

	// 描画するチップ数を算出
	nDrawChipNumX = SCREEN_WIDTH / (int)GetMapchipSize().x;	// 横方向(x軸)のチップ数
	nDrawChipNumY = SCREEN_HEIGHT / (int)GetMapchipSize().y;	// 縦方向(y軸)のチップ数

	// マップチップを一枚ずつ描画
	for (int iy = numy; iy < (numy + nDrawChipNumY); iy++)
	{
		for (int ix = numx; ix < (numx + nDrawChipNumX); ix++)
		{
			// マップの番号を取得
			int nChipId = m_pMapChipData[ (iy * m_nChipNumX) + ix];

			// チップの描画位置を算出
			D3DXVECTOR2 ChipCenterPos;
			ChipCenterPos.y = (float)(offset_y + (GetMapchipSize().y * iy));		// 背景の表示座標Y
			ChipCenterPos.x = (float)(offset_x + (GetMapchipSize().x  * ix));	// 背景の表示座標X

			ChipCenterPos.y += GetMapchipSize().y * 0.5f;
			ChipCenterPos.x += GetMapchipSize().x * 0.5f;

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



//=============================================================================
// ゲッター関数
//=============================================================================
// 回転フラグのセット
void CMapchip::SetRotationFlag(bool Flag)
{
	m_bRotFlag = Flag;
}

//=============================================================================
// ゲッター関数
//=============================================================================
// マップ全体の大きさを取得
D3DXVECTOR2 CMapchip::GetMapSize()
{
	D3DXVECTOR2 ans;
	ans.x = m_vChipSize.x * m_nChipNumX;	// 幅を格納
	ans.y = m_vChipSize.y * m_nChipNumY;	// 高さを格納

	return ans;
}

// １つのチップの大きさを取得
D3DXVECTOR2 CMapchip::GetMapchipSize()
{
	return m_vChipSize;
}

// マップチップ配列を取得
int* CMapchip::GetMapChipData()
{
	return m_pMapChipData;
}

// マップチップの列数を取得
int CMapchip::GetMapchipNumX()
{
	return m_nChipNumX;
}

// 指定された座標にあるチップ番号を取得
int CMapchip::GetMapchipNo(D3DXVECTOR2 Pos)
{
	int cx = (int)(Pos.x / m_vChipSize.x);
	int cy = (int)(Pos.y / m_vChipSize.y);

	return m_pMapChipData[cx + (cy * m_nChipNumX)];
}

// 回転フラグの取得
bool CMapchip::GetRotationFlag()
{
	return m_bRotFlag;
}







void CreateMapchipTextureAndBuffer()
{
	// テクスチャ生成
	for (int i = 0; i < MAPCHIP_MAX; i++)
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

void ReleaseMapchipTextureAndBuffer()
{
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}

	for (int i = 0; i < MAPCHIP_MAX; i++)
	{
		if (g_Texture[i])
		{
			g_Texture[i]->Release();
			g_Texture[i] = NULL;
		}
	}

}

void PresetDrawMapchip()
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