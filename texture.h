//=============================================================================
// テクスチャ関連処理 [texture.h]
// Author : 杉本幸宏
//=============================================================================
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTexture
{
public:
	void SetV(float V);
	void SetU(float U);
	void DrawTexture(char* TextureName, D3DXVECTOR2 Position, D3DXCOLOR Color, float Rotation);

private:
	//------------------- メンバ変数
	ID3D11Buffer*				g_VertexBuffer = NULL;				// 頂点情報
	ID3D11ShaderResourceView*	TextureData;
	D3DXVECTOR2					m_vTexPos;		// テクスチャの描画位置
	D3DXVECTOR2					m_vSize;		// テクスチャの 幅＆高さ
	float						m_fU, m_fV;		// UV座標系
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void SetVertex(ID3D11Buffer *buf, float X, float Y, float Width, float Height, float U, float V, float UW, float VH);

void SetSprite(ID3D11Buffer *buf, float X, float Y, float Width, float Height, float U, float V, float UW, float VH);

void SetSpriteColor(ID3D11Buffer *buf, float X, float Y, float Width, float Height, float U, float V, float UW, float VH, D3DXCOLOR color);

void SetSpriteColorRotation(ID3D11Buffer *buf, float X, float Y, float Width, float Height,
	float U, float V, float UW, float VH,
	D3DXCOLOR Color, float Rot);
