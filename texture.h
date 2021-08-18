//=============================================================================
//
// テクスチャ関連処理 [texture.h]
// Author : 杉本幸宏
//
//=============================================================================
#pragma once

//#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE
#define ANIMATION


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
	void UpdateAnimIndex(int MotionStartIndex, int MotionEndIndex);			// アニメーション
	void Init(int DivX = 1, int DivY = 1, int Wait = 0, int Index = 0);		// メンバ変数の初期化
	void Uninit();		// 終了処理

	//------------------- セッター関数
	void SetTexDivideX(int DivX) { m_nDivideX = DivX; };	// 横の分割数を格納
	void SetTexDivideY(int DivY) { m_nDivideY = DivY; };	// 縦の分割数を格納
	void SetAnimWait(int Wait) { m_nAnimWait = Wait; };		// アニメーションのWait値をセット

	//------------------- ゲッター関数
	int GetTexDivideX() { return m_nDivideX; };				// 横の分割数を取得
	int GetTexDivideY() { return m_nDivideY; };				// 縦の分割数を取得
	int GetAnimWait() { return m_nAnimWait; };				// アニメーションのWait値を取得
	int GetCurrentAnim() { return m_nCurrentAnimIndex; };	// 現在のアニメーション番号を取得

private:
	//------------------- メンバ変数
	int m_nDivideX, m_nDivideY;		// テクスチャの縦横の分割数
	int m_nAnimWait;				// 画像が切り替わるWait値（単位はフレーム）
	int m_nCurrentAnimIndex;		// 現在のアニメーション番号
	int m_nCurrentFlame;			// 現在のフレーム値
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
	void DrawTextureTopLeft(ID3D11ShaderResourceView* TextureData);	// 回転は反映されない！

	// 完全オートver（ただし、これを使う場合にはあらかじめ下の"CreateTextureInf"を呼び出す必要がある）
	void DrawTexture();
	void DrawTextureTopLeft();

	// メンバ変数のテクスチャ情報を生成
	void CreateTextureInf(char* TextureFileName);

	// メンバ変数のテクスチャ情報を解放
	void ReleaseTextureInf();

	// 初期化処理
	void Init(D3DXVECTOR2 Pos = D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2 Size = D3DXVECTOR2(0.0f, 0.0f), D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), float Rotaiton = 0.0f,	// テクスチャ
		int TexDivX = 1, int TexDivY = 1, int AnimWait = 0, int IndexNo = 0);	// アニメーション
	// 終了処理
	void Uninit();

	//------------------- セッター関数
	//void SetTextureInf(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, D3DXCOLOR Color, float Rotation, D3DXVECTOR2 UV);
	void SetTexPos(D3DXVECTOR2 Pos) { m_vTexPos = Pos; } ;				// テクスチャの描画位置をセット
	void SetTexSize(D3DXVECTOR2 Size) { m_vTexSize = Size; };			// テクスチャのサイズをセット
	void SetTexColor(D3DXCOLOR Color) { m_TexColor = Color; };			// 頂点色のセット
	void SetTexRotation(float Rotaiton) { m_fTexRotation = Rotaiton; };	// 回転値のセット
	void SetTexU(float U) { m_fTexU = U; };								// テクスチャのUV座標のU値をセット
	void SetTexV(float V) { m_fTexV = V; };								// テクスチャのUV座標のV値をセット

	//------------------- ゲッター関数
	D3DXVECTOR2 GetTexPos() { return m_vTexPos; };		// テクスチャの描画位置を取得
	D3DXVECTOR2 GetTexSize() { return m_vTexSize; };	// テクスチャのサイズを取得
	D3DXCOLOR GetTexColor() { return m_TexColor; };		// テクスチャの色を取得
	float GetTexRotation() { return m_fTexRotation; };	// テクスチャの回転角を取得

private:
	//------------------- メンバ変数
//	ID3D11Buffer*				VertexBuffer = NULL;// 頂点情報
	ID3D11ShaderResourceView*	m_TextureData;		// テクスチャ情報
	D3DXVECTOR2					m_vTexPos;			// テクスチャの描画位置
	D3DXVECTOR2					m_vTexSize;			// テクスチャの 幅＆高さ
	D3DXCOLOR					m_TexColor;			// 頂点色
	float						m_fTexRotation;		// テクスチャの回転角
	float						m_fTexU, m_fTexV;	// UV座標系(テクスチャ関数の内部的に処理してる)

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
void SetSpriteColorTopLeft(ID3D11Buffer *buf, float X, float Y, float Width, float Height,
	float U, float V, float UW, float VH,
	D3DXCOLOR Color);


// テクスチャ情報の生成
void CreateTexture(const char* TextureName, ID3D11ShaderResourceView** TexrureData);

// テクスチャ情報の解放
void ReleaseTexture(ID3D11ShaderResourceView** TexrureData);	// (解放したあと、NULLがセットされる)
bool ReleaseTexture(ID3D11ShaderResourceView* TextureData);		// 解放処理実行されたときはtrue, されてないときはfalse (解放したあと、NULLはセットされない)


// 頂点バッファ生成
void CreateVertexBuffer(ID3D11Buffer** VertexBuffer);	// 任意の頂点バッファを生成
void CreateVertexBuffer(void);							// テクスチャ関数のグローバルの頂点バッファver

// 頂点バッファの解放
void ReleaseVertexBuffer(ID3D11Buffer** VertexBuffer);	// 任意の頂点バッファを解放
void ReleaseVertexBuffer(void);							// テクスチャ関数のグローバルの頂点バッファver


// 描画処理( DrawTexture() ) の前に1回だけ呼び出すおまじない（何回でも呼び出していいけど、処理めっちゃ重くなる）
void PresetDraw2D(ID3D11Buffer** g_VertexBuffer);		// 任意の頂点バッファを使用
void PresetDraw2D(void);								// グローバルの頂点バッファを使用
