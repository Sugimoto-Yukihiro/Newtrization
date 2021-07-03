//=============================================================================
//
// テクスチャ関連処理 [texture.h]
// Author : 杉本幸宏
//
//=============================================================================
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
// アニメーションクラス
class CAnimation
{
public:
//	CAnimation();		// コンストラクタ
//	~CAnimation();		// デストラクタ

	//------------------- メンバ関数
	void UpdateAnimIndex(int MotionStartIndex, int MotionEndIndex);
	void Init();

	//------------------- セッター関数
	//void SetCurrentAnim(int CurAnim);	// 現在のアニメーション番号を取得
	void SetDivideX(int DivX);		// 横のアニメーションパターン数を格納
	void SetDivideY(int DivY);		// 縦のアニメーションパターン数を格納
	void SetAnimWait(int Wait);		// アニメーションのWait値をセット

	//------------------- ゲッター関数
	int GetCurrentAnim();			// 現在のアニメーション番号を取得
	int GetDivideX();				// 横のアニメーションパターン数を取得
	int GetDivideY();				// 縦のアニメーションパターン数を取得
//	int GetAnimWait();				// アニメーションのWait値を取得

private:
	//------------------- メンバ変数
	int m_nDivideX, m_nDivideY;		// テクスチャの縦横の分割数
	int m_nCurrentAnimIndex;		// 現在のアニメーション番号
	int m_nCurrentFlame;			// 現在のフレーム値
	int m_nAnimWait;				// 画像が切り替わるWait値（単位はフレーム）
};

// テクスチャクラス
class CTexture : public CAnimation
{
public:
	//------------------- メンバ関数
	void DrawTexture(ID3D11Buffer* VertexBuffer, ID3D11ShaderResourceView* TextureData);
	void Init();

	//------------------- セッター関数
	void SetV(float V);
	void SetU(float U);

	//------------------- ゲッター関数
	D3DXVECTOR2 GetTexPos();
	D3DXVECTOR2 GetTexSize();

private:
	//------------------- メンバ変数
//	ID3D11Buffer*				VertexBuffer = NULL;				// 頂点情報
//	ID3D11ShaderResourceView*	TextureData;
	D3DXVECTOR2					m_vTexPos;		// テクスチャの描画位置
	D3DXVECTOR2					m_vSize;		// テクスチャの 幅＆高さ
	D3DXCOLOR					m_Color;		// 頂点色
	float						m_fU, m_fV;		// UV座標系
	float						m_fRotation;	// テクスチャの回転角
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
