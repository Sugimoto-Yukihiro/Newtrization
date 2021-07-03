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
	//void DrawTexture(char* TextureName, D3DXVECTOR2 Position, D3DXCOLOR Color, float Rotation);
	void DrawTexture(ID3D11Buffer* VertexBuffer, ID3D11ShaderResourceView* TextureData);

private:
	//------------------- メンバ変数
//	ID3D11Buffer*				VertexBuffer = NULL;				// 頂点情報
//	ID3D11ShaderResourceView*	TextureData;
	D3DXVECTOR2					m_vTexPos;		// テクスチャの描画位置
	D3DXVECTOR2					m_vSize;		// テクスチャの 幅＆高さ
	float						m_fU, m_fV;		// UV座標系
	float						m_fRotation;	// テクスチャの回転角
};

// アニメーションクラス
class CAnimation
{
public:
	//念のためのコンストとデスト
//	CAnimation();
//	~CAnimation();

	//------------------- メンバ関数
//	void ChangeAnimIndex(int& CurrentIndex, int& CurrentAnimFlame, int FlameWait, int MotionStartNum, int UseGraphNum);
	void UpdateAnimIndex(int MotionStartIndex, int MotionEndIndex);

private:
	//------------------- メンバ変数
	int m_nDivideX, m_nDivideY;		// テクスチャの縦横の分割数
	int m_nCurrentAnimIndex;		// 現在のアニメーション番号
	int m_nCurrentFlame;			// 現在のフレーム値
	int m_nAnimWait;				// 画像が切り替わるWait値（単位はフレーム）
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
