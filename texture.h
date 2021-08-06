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
	void Init();					// メンバ変数の初期化

	//------------------- セッター関数
	void SetAnimInf(int DivX, int DivY, int Wait);
	void SetTexDivideX(int DivX);	// 横の分割数を格納
	void SetTexDivideY(int DivY);	// 縦の分割数を格納
	void SetAnimWait(int Wait);		// アニメーションのWait値をセット

	//------------------- ゲッター関数
	int GetCurrentAnim();			// 現在のアニメーション番号を取得
	int GetTexDivideX();			// 横の分割数を取得
	int GetTexDivideY();			// 縦の分割数を取得
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
	CTexture();		// コンストラクタ
//	~CTexture();		// デストラクタ

	//------------------- メンバ関数
	void DrawTexture(ID3D11ShaderResourceView* TextureData, ID3D11Buffer* VertexBuffer);
	void DrawTexture(ID3D11ShaderResourceView* TextureData);
	void Init();							// メンバ変数の初期化
//	void AddTexPos(D3DXVECTOR2 Pos);		// テクスチャ表示座標をずらす

	//------------------- セッター関数
	void SetTextureInf(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, D3DXCOLOR Color, float Rotation, D3DXVECTOR2 UV);
	void SetTexPos(D3DXVECTOR2 Pos);		// テクスチャの描画位置をセット
	void SetTexSize(D3DXVECTOR2 Size);		// テクスチャのサイズをセット
	void SetTexColor(D3DXCOLOR Color);		// 頂点色のセット
	void SetTexRotation(float Rotaiton);	// 回転値のセット
	void SetTexU(float U);					// テクスチャのUV座標のU値をセット
	void SetTexV(float V);					// テクスチャのUV座標のV値をセット

	//------------------- ゲッター関数
	D3DXVECTOR2 GetTexPos();				// テクスチャの描画位置を取得
	D3DXVECTOR2 GetTexSize();				// テクスチャのサイズを取得

	//------------------- メンバ変数(public)
//	int		m_nTexNo;		// テクスチャ番号		// tecture.cpp内で使ってないからいらん

private:
	//------------------- メンバ変数
//	ID3D11Buffer*				VertexBuffer = NULL;// 頂点情報
//	ID3D11ShaderResourceView*	TextureData;
	D3DXVECTOR2					m_vTexPos;			// テクスチャの描画位置
	D3DXVECTOR2					m_vTexSize;			// テクスチャの 幅＆高さ
	D3DXCOLOR					m_TexColor;			// 頂点色
	float						m_fTexU, m_fTexV;	// UV座標系
	float						m_fTexRotation;		// テクスチャの回転角

};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void SetVertex(float X, float Y, float Width, float Height, float U, float V, float UW, float VH);
void SetSprite(ID3D11Buffer *buf, float X, float Y, float Width, float Height, float U, float V, float UW, float VH);
void SetSpriteColor(ID3D11Buffer *buf, float X, float Y, float Width, float Height, float U, float V, float UW, float VH, D3DXCOLOR color);
void SetSpriteColorRotation(ID3D11Buffer *buf, float X, float Y, float Width, float Height,
	float U, float V, float UW, float VH,
	D3DXCOLOR Color, float Rot);


// テクスチャ情報の生成
void CreateTexture(const char* TextureName, ID3D11ShaderResourceView** TexrureData);
// テクスチャ情報の解放
void ReleaseTexture(ID3D11ShaderResourceView** TexrureData);

// 頂点バッファ生成
void CreateVertexBuffer(ID3D11Buffer** VertexBuffer);	// 任意の頂点バッファを生成
void CreateVertexBuffer(void);							// テクスチャ関数のグローバルの頂点バッファver
// 頂点バッファの解放
void ReleaseVertexBuffer(ID3D11Buffer** VertexBuffer);	// 任意の頂点バッファを解放
void ReleaseVertexBuffer(void);							// テクスチャ関数のグローバルの頂点バッファver


// 描画処理( DrawTexture() ) の前に1回だけ呼び出すおまじない（何回でも呼び出していいけど、処理めっちゃ重くなる）
void PresetDraw2D(ID3D11Buffer** g_VertexBuffer);		// 任意の頂点バッファを使用
void PresetDraw2D(void);								// グローバルの頂点バッファを使用
