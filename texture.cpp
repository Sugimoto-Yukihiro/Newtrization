//=============================================================================
//
// テクスチャ関連処理 [texture.cpp]
// Author : 杉本幸宏
//
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
static ID3D11Buffer		*g_VertexBuffer2D = NULL;	// 頂点情報


//=============================================================================
// コンストラクタ
//=============================================================================
CTexture::CTexture()	// コンストラクタ
{
	Init();		// 初期化処理を行う
}

//=============================================================================
// 初期化処理（CTexture）
//=============================================================================
void CTexture::Init(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, D3DXCOLOR Color, float Rotaiton,
					int TexDivX, int TexDivY, int AnimWait, int IndexNo)
{
	m_vTexPos = Pos;
	m_vTexSize = Size;
	m_TexColor = Color;
	m_fTexRotation = Rotaiton;
	m_fTexU = m_fTexV = 0.0f;

	//------------------- ベースクラスの初期化
	CAnimation::Init(TexDivX, TexDivY, AnimWait, IndexNo);		// CAnimation
}



//=============================================================================
// 終了処理（CTexture）
//=============================================================================
void CTexture::Uninit()	// 全てのメンバ変数を０でクリア
{
	m_vTexPos = ZERO_VECTOR2;
	m_vTexSize = ZERO_VECTOR2;
	m_TexColor = DEFAULT_COLOR;
	m_fTexU = m_fTexV = 0.0f;
	m_fTexRotation = 0.0f;

	//------------------- ベースクラスの終了処理
	CAnimation::Uninit();		// CAnimation
}



//=============================================================================
// テクスチャ描画関数（CTexture）
// 引数 :	テクスチャのファイル名, 頂点座標
// 説明 :	テクスチャを、引数に指定された値に描画する処理
//=============================================================================
void CTexture::DrawTexture(ID3D11ShaderResourceView* pTextureData, ID3D11Buffer* pVertexBuffer)
{
	float tw = 0.0f, th = 0.0f, tU = 0.0f, tV = 0.0f;

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, &pTextureData);

	//------------------- アニメーションも考慮して、UV座標の値を決定する
	// 1つのアニメーションパターンあたりの幅と高さを求める
	tw = 1.0f / (float)GetTexDivideX();							// 幅
	th = 1.0f / (float)GetTexDivideY();							// 高さ
	if (GetCurrentAnim() != 0) tU = (float)(GetCurrentAnim() % GetTexDivideX()) * tw;	// テクスチャの左上X座標
	if (GetCurrentAnim() != 0) tV = (float)(GetCurrentAnim() / GetTexDivideX()) * th;	// テクスチャの左上Y座標

	// １枚のポリゴンの頂点とテクスチャ座標を設定
	SetSpriteColorRotation(pVertexBuffer, m_vTexPos.x, m_vTexPos.y, m_vTexSize.x, m_vTexSize.y, tU, tV, tw, th,
		m_TexColor, m_fTexRotation);

	// ポリゴン描画
	GetDeviceContext()->Draw(4, 0);
}

void CTexture::DrawTexture(ID3D11ShaderResourceView* pTextureData)	// テクスチャ座標のみ
{
	float tw = 0.0f, th = 0.0f, tU = 0.0f, tV = 0.0f;

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, &pTextureData);

	//------------------- アニメーションも考慮して、UV座標の値を決定する
	// 1つのアニメーションパターンあたりの幅と高さを求める
	tw = 1.0f / (float)GetTexDivideX();							// 幅
	th = 1.0f / (float)GetTexDivideY();							// 高さ
	if (GetCurrentAnim() != 0) tU = (float)(GetCurrentAnim() % GetTexDivideX()) * tw;	// テクスチャの左上X座標
	if (GetCurrentAnim() != 0) tV = (float)(GetCurrentAnim() / GetTexDivideX()) * th;	// テクスチャの左上Y座標

	// １枚のポリゴンの頂点とテクスチャ座標を設定
	SetSpriteColorRotation(g_VertexBuffer2D, m_vTexPos.x, m_vTexPos.y, m_vTexSize.x, m_vTexSize.y, tU, tV, tw, th,
		m_TexColor, m_fTexRotation);

	// ポリゴン描画
	GetDeviceContext()->Draw(4, 0);
}

// 左上を原点とした描画
void CTexture::DrawTextureTopLeft(ID3D11ShaderResourceView* pTextureData)	// テクスチャ座標のみ
{
	float tw = 0.0f, th = 0.0f, tU = 0.0f, tV = 0.0f;

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, &pTextureData);

	//------------------- アニメーションも考慮して、UV座標の値を決定する
	// 1つのアニメーションパターンあたりの幅と高さを求める
	tw = 1.0f / (float)GetTexDivideX();							// 幅
	th = 1.0f / (float)GetTexDivideY();							// 高さ
	if (GetCurrentAnim() != 0) tU = (float)(GetCurrentAnim() % GetTexDivideX()) * tw;	// テクスチャの左上X座標
	if (GetCurrentAnim() != 0) tV = (float)(GetCurrentAnim() / GetTexDivideX()) * th;	// テクスチャの左上Y座標

	// １枚のポリゴンの頂点とテクスチャ座標を設定
	SetSpriteColorTopLeft(g_VertexBuffer2D, m_vTexPos.x, m_vTexPos.y, m_vTexSize.x, m_vTexSize.y, tU, tV, tw, th,
		m_TexColor);

	// ポリゴン描画
	GetDeviceContext()->Draw(4, 0);
}


//=============================================================================
// セッター関数（CTexture）
//=============================================================================
//// 全てのメンバ変数を一括で変更する関数
//void CTexture::SetTextureInf(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, D3DXCOLOR Color, float Rotation, D3DXVECTOR2 UV)
//{
//	m_vTexPos = Pos;
//	m_vTexSize = Size;
//	m_TexColor = Color;
//	m_fTexRotation = Rotation;
//	m_fTexU = UV.x;
//	m_fTexV = UV.y;
//}

// テクスチャの描画位置を変更する関数
void CTexture::SetTexPos(D3DXVECTOR2 Pos)
{
	m_vTexPos = Pos;
}

// テクスチャの描画サイズを変更する関数
void CTexture::SetTexSize(D3DXVECTOR2 Size)
{
	m_vTexSize = Size;
}

// テクスチャの頂点色を変更する関数
void CTexture::SetTexColor(D3DXCOLOR Color)
{
	m_TexColor = Color;
}

// テクスチャの回転値を変更する関数
void CTexture::SetTexRotation(float Rotaiton)
{
	m_fTexRotation = Rotaiton;
}

// UV座標のU値を変更する関数
void CTexture::SetTexU(float U)
{
	m_fTexU = U;
}

// UV座標のV値を変更する関数
void CTexture::SetTexV(float V)
{
	m_fTexV = V;
}


//=============================================================================
// ゲッター関数（CTexture）
//=============================================================================
//// テクスチャの描画位置を取得する関数
//D3DXVECTOR2 CTexture::GetTexPos()
//{
//	return m_vTexPos;
//}
//
//// テクスチャのサイズを取得する関数
//D3DXVECTOR2 CTexture::GetTexSize()
//{
//	return m_vTexSize;
//}


// ************************ アニメーションクラス ************************

//=============================================================================
// 初期化処理（CAnimation）
//=============================================================================
void CAnimation::Init(int DivX, int DivY, int Wait, int Index)	// 全てのメンバ変数を０で初期化
{
	m_nDivideX = DivX;				// テクスチャの横の分割数をセット
	m_nDivideY = DivY;				// テクスチャの縦の分割数をセット
	m_nAnimWait = Wait;				// 画像が切り替わるタイミングをセット
	m_nCurrentAnimIndex = Index;	// 画像番号を指定
	m_nCurrentFlame = 0;			// フレームカウントは0
}



//=============================================================================
// 終了処理（CAnimation）
//=============================================================================
void CAnimation::Uninit()	// 全てのメンバ変数を０でクリア
{
	m_nDivideX = m_nDivideY = 0;
	m_nCurrentAnimIndex = 0;
	m_nCurrentFlame = 0;
	m_nAnimWait = 0;
}



//=============================================================================
// アニメーション番号の更新関数（CAnimation）
// 引数 :	アニメーションの始点番号, アニメーションの終点番号
// 説明 :	アニメーション番号の更新。
//			Wait値と現在のフレーム値を比較して、アニメーション番号の加算を行う。
//=============================================================================
void CAnimation::UpdateAnimIndex(int MotionStartIndex, int MotionEndIndex)
{
	// 現在の経過フレームを加算
	m_nCurrentFlame++;

	// 切り替えるフレームになったか判別
	if (m_nCurrentFlame >= m_nAnimWait)
	{
		// アニメーション番号の更新
		m_nCurrentAnimIndex++;

		// 終点番号をオーバーしていた時
		if (m_nCurrentAnimIndex > MotionEndIndex)
		{
			m_nCurrentAnimIndex = MotionStartIndex;	// 始点にリセット
		}

		// 経過フレーム数のリセット
		m_nCurrentFlame = 0;
	}

}



//=============================================================================
// セッター関数（CAnimation）
//=============================================================================
// 横のアニメーションパターン数を格納
void CAnimation::SetTexDivideX(int DivX)
{
	m_nDivideX = DivX;
}

// 縦のアニメーションパターン数を格納
void CAnimation::SetTexDivideY(int DivY)
{
	m_nDivideY = DivY;
}

// Wait値を変更する関数
void CAnimation::SetAnimWait(int Wait)
{
	m_nAnimWait = Wait;
}



//=============================================================================
// ゲッター関数（CAnimation）
//=============================================================================
//int CAnimation::GetCurrentAnim()	// 現在のアニメーション番号を取得する関数
//{
//	return m_nCurrentAnimIndex;
//}
//
//int CAnimation::GetTexDivideX()	// 横方向のアニメーションパターン数を取得する関数
//{
//	return m_nDivideX;
//}
//
//int CAnimation::GetTexDivideY()	// 縦方向のアニメーションパターン数を取得する関数
//{
//	return m_nDivideY;
//}



//=============================================================================
// 頂点データ設定(2D)
//=============================================================================
void SetVertex(float X, float Y, float Width, float Height, float U, float V, float UW, float VH)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer2D, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

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

	GetDeviceContext()->Unmap(g_VertexBuffer2D, 0);
}

// テクスチャの配置
void SetSprite(ID3D11Buffer *buf, float X, float Y, float Width, float Height, float U, float V, float UW, float VH)
{
	// バッファが指定されていなければグローバルのやつを使う
	if (buf == NULL) buf = g_VertexBuffer2D;

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

// +色・左上原点
void SetSpriteColorTopLeft(ID3D11Buffer *buf, float X, float Y, float Width, float Height,
	float U, float V, float UW, float VH,
	D3DXCOLOR Color)
{
	// バッファが指定されていなければグローバルのやつを使う
	if (buf == NULL) buf = g_VertexBuffer2D;

	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(buf, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	// 左上を原点として設定するプログラム
	vertex[0].Position = D3DXVECTOR3(X, Y, 0.0f);
	vertex[0].Diffuse = Color;
	vertex[0].TexCoord = D3DXVECTOR2(U, V);

	vertex[1].Position = D3DXVECTOR3(X + Width, Y, 0.0f);
	vertex[1].Diffuse = Color;
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);

	vertex[2].Position = D3DXVECTOR3(X, Y + Height, 0.0f);
	vertex[2].Diffuse = Color;
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);

	vertex[3].Position = D3DXVECTOR3(X + Width, Y + Height, 0.0f);
	vertex[3].Diffuse = Color;
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	GetDeviceContext()->Unmap(buf, 0);

}



void CreateTexture(const char* TextureName, ID3D11ShaderResourceView** TexrureData)
{
	//テクスチャ生成
	D3DX11CreateShaderResourceViewFromFile(GetDevice(),
		TextureName,
		NULL,
		NULL,
		TexrureData,
		NULL);

}

// 頂点バッファ（2D）の生成
void CreateVertexBuffer(ID3D11Buffer** VertexBuffer)	// 任意の頂点バッファを生成
{
	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;	// 2Dは4頂点
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, VertexBuffer);
}
void CreateVertexBuffer(void)	// グローバルの頂点バッファを生成
{
	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;	// 2Dは4頂点
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer2D);
}

// テクスチャ情報の解放
void ReleaseTexture(ID3D11ShaderResourceView** TextureData)
{
	if (*TextureData)
	{
		TextureData[0]->Release();	// 解放処理実行
		*TextureData = NULL;		// NULLをセット
	}

}
bool ReleaseTexture(ID3D11ShaderResourceView* TextureData)
{
	if (TextureData)	// NULLじゃないなら解放
	{
		TextureData->Release();	// 解放処理実行
		return(true);			// "実行してる"を返す
	}

	return(false);	// 解放処理実行してない
}

// 頂点バッファ（2D）の解放
void ReleaseVertexBuffer(ID3D11Buffer** VertexBuffer)	// 任意の頂点バッファを解放
{
	if (*VertexBuffer)
	{
		VertexBuffer[0]->Release();
		*VertexBuffer = NULL;
	}

}
void ReleaseVertexBuffer(void)	// グローバルの頂点バッファを解放
{
	if (g_VertexBuffer2D)
	{
		g_VertexBuffer2D->Release();
		g_VertexBuffer2D = NULL;
	}

}

// 描画前準備（頂点バッファの設定）
void PresetDraw2D(ID3D11Buffer** VertexBuffer)	// 任意の頂点バッファ
{
	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, VertexBuffer, &stride, &offset);

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
void PresetDraw2D(void)	// グローバルの頂点バッファ
{
	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer2D, &stride, &offset);

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
