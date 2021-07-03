//=============================================================================
// スプライト処理 [sprite.cpp]
// Author : 杉本幸宏
//=============================================================================

#include "main.h"
#include "texture.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************



//=============================================================================
// テクスチャ描画関数（DrawTexture）
// 引数 :	テクスチャのファイル名, 描画座標, 頂点色, 回転角
// 説明 :	テクスチャを、引数に指定された値に描画する処理
//=============================================================================
//void CTexture::DrawTexture(D3DXVECTOR2 Position, D3DXVECTOR2 Size, D3DXCOLOR Color, float Rotation)
void CTexture::DrawTexture(ID3D11Buffer* VertexBuffer, ID3D11ShaderResourceView* TextureData)
{
	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, &TextureData);

	//プレイヤーの位置やテクスチャー座標を反映
	float tw = 1.0f / TEXTURE_PATTERN_DIVIDE_X;	// テクスチャの幅
	float th = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;	// テクスチャの高さ
	float tx = (float)(patternAnim % TEXTURE_PATTERN_DIVIDE_X) * tw;	// テクスチャの左上X座標
	float ty = (float)(patternAnim / TEXTURE_PATTERN_DIVIDE_X) * th;	// テクスチャの左上Y座標

	// １枚のポリゴンの頂点とテクスチャ座標を設定
	SetSpriteColorRotation(VertexBuffer, Position.x, Position.y, Size.x, Size.y, tx, ty, tw, th,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		Rotation);

	// ポリゴン描画
	GetDeviceContext()->Draw(4, 0);
}

//=============================================================================
// アニメーション番号の更新関数
// 引数 :	アニメーションの始点番号, アニメーションの終点番号
// 説明 :	アニメーション番号の更新。
//			Wait値と現在のフレーム値を比較して、アニメーション番号の加算を行う。
//=============================================================================
void CAnimation::UpdateAnimIndex(int MotionStartIndex, int MotionEndIndex)
{
	// 1フレーム加算
	m_nCurrentFlame++;

	// 切り替えるフレームになったか判別
	if (m_nCurrentFlame >= m_nAnimWait)
	{
		// アニメーション番号の更新
		m_nCurrentAnimIndex++;

		// 終点番号をオーバーしていた時
		if (m_nCurrentAnimIndex > MotionEndIndex)
		{
			m_nCurrentAnimIndex = MotionStartIndex;	// 始点にセット
		}

		// 経過フレーム数のリセット
		m_nCurrentFlame = 0;
	}

}


//=============================================================================
// 頂点データ設定(2D)
//=============================================================================
void SetVertex(ID3D11Buffer *buf, float X, float Y, float Width, float Height, float U, float V, float UW, float VH)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(buf, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	// 左上を原点として設定するプログラム
	vertex[0].Position = D3DXVECTOR3(X, Y, 0.0f);
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(U, V);

	vertex[1].Position = D3DXVECTOR3(X + Width, Y, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);

	vertex[2].Position = D3DXVECTOR3(X, Y + Height, 0.0f);
	vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);

	vertex[3].Position = D3DXVECTOR3(X + Width, Y + Height, 0.0f);
	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	GetDeviceContext()->Unmap(buf, 0);
}

// テクスチャの配置
void SetSprite(ID3D11Buffer *buf, float X, float Y, float Width, float Height, float U, float V, float UW, float VH)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(buf, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = Width * 0.5f;		// テクスチャの半分の幅   // コンピューターは割り算が苦手
	hh = Height * 0.5f;		// テクスチャの半分の高さ // 掛け算の方が処理が速い

	// 指定された座標を中心に設定するプログラム

	// 頂点０番（左上の頂点）
	vertex[0].Position = D3DXVECTOR3(X - hw, Y - hh, 0.0f);
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(U, V);

	// 頂点１番（右上の頂点）
	vertex[1].Position = D3DXVECTOR3(X + hw, Y - hh, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);

	// 頂点２番（左下の頂点）
	vertex[2].Position = D3DXVECTOR3(X - hw, Y + hh, 0.0f);
	vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);

	// 頂点３番（右下の頂点）
	vertex[3].Position = D3DXVECTOR3(X + hw, Y + hh, 0.0f);
	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	GetDeviceContext()->Unmap(buf, 0);
}

// +色
void SetSpriteColor(ID3D11Buffer *buf, float X, float Y, float Width, float Height,
		float U, float V, float UW, float VH,
		D3DXCOLOR color)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(buf, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = Width * 0.5f;		// コンピューターは割り算が苦手
	hh = Height * 0.5f;		// 掛け算の方が処理が速い

	// 指定された座標を中心に設定するプログラム

	// 頂点０番（左上の頂点）
	vertex[0].Position = D3DXVECTOR3(X - hw, Y - hh, 0.0f);
	vertex[0].Diffuse = color;
	vertex[0].TexCoord = D3DXVECTOR2(U, V);

	// 頂点１番（右上の頂点）
	vertex[1].Position = D3DXVECTOR3(X + hw, Y - hh, 0.0f);
	vertex[1].Diffuse = color;
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);

	// 頂点２番（左下の頂点）
	vertex[2].Position = D3DXVECTOR3(X - hw, Y + hh, 0.0f);
	vertex[2].Diffuse = color;
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);

	// 頂点３番（右下の頂点）
	vertex[3].Position = D3DXVECTOR3(X + hw, Y + hh, 0.0f);
	vertex[3].Diffuse = color;
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	GetDeviceContext()->Unmap(buf, 0);

}

// +色・回転
void SetSpriteColorRotation(ID3D11Buffer *buf, float X, float Y, float Width, float Height,
	float U, float V, float UW, float VH,
	D3DXCOLOR Color, float Rot)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(buf, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = Width * 0.5f;		// コンピューターは割り算が苦手
	hh = Height * 0.5f;		// 掛け算の方が処理が速い

	// 指定された座標を中心に回転するプログラム
	float BaseAngle = atan2f(hh, hw);		// 中心点から頂点に対する角度
	D3DXVECTOR2 temp = D3DXVECTOR2(hw, hh);
	float Radius = D3DXVec2Length(&temp);	// 中心点から頂点に対する距離

	// ここでアフィン変換（sincosのやつ）を使って4頂点を回転させる
	float x = X - cosf(BaseAngle + Rot) * Radius;
	float y = Y - sinf(BaseAngle + Rot) * Radius;
	vertex[0].Position = D3DXVECTOR3(x, y, 0.0f);

	x = X + cosf(BaseAngle - Rot) * Radius;
	y = Y - sinf(BaseAngle - Rot) * Radius;
	vertex[1].Position = D3DXVECTOR3(x, y, 0.0f);

	x = X - cosf(BaseAngle - Rot) * Radius;
	y = Y + sinf(BaseAngle - Rot) * Radius;
	vertex[2].Position = D3DXVECTOR3(x, y, 0.0f);

	x = X + cosf(BaseAngle + Rot) * Radius;
	y = Y + sinf(BaseAngle + Rot) * Radius;
	vertex[3].Position = D3DXVECTOR3(x, y, 0.0f);

	vertex[0].Diffuse = Color;
	vertex[1].Diffuse = Color;
	vertex[2].Diffuse = Color;
	vertex[3].Diffuse = Color;

	vertex[0].TexCoord = D3DXVECTOR2(U, V);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	GetDeviceContext()->Unmap(buf, 0);

}

