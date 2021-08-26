//==================================================================
//
// 浮力加速処理 [floatforce.h]
// Auther : 杉本幸宏
//
//==================================================================
#pragma once

#include "texture.h"	// テクスチャ描画処理

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CFloatForce		// 浮力加速クラス
{
public:
	CFloatForce();		// コンストラクタ
	~CFloatForce();	// デストラクタ

	void Init(char* TextureName = NULL);	// 初期化処理
	void Uninit();	// 終了処理
	void Update();	// 更新処理
	void Draw(D3DXVECTOR2 ScrollPos);	// 描画処理

	void AddFloatForce(D3DXVECTOR2 *Pos);				// 浮力を加えて移動させる
	bool HitCheck(D3DXVECTOR2 *Pos, D3DXVECTOR2 Size);	// 当たり判定

	//------------------- セッター関数
	bool SetFloatForceErea(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, D3DXVECTOR2 Dir, float Force, D3DXCOLOR Color);	// 浮力加速エリアのセット

	void SetAreaSize(D3DXVECTOR2 Size) { m_Area = Size; };		// エリアの大きさを取得
	void SetDirection(D3DXVECTOR2 Dir);							// 浮力の方向を取得
	void SetCenterPos(D3DXVECTOR2 Pos) { m_CenterPos = Pos; };	// エリアの位置を取得
	void SetForceValue(float Force) { m_Force = Force; };		// 浮力の大きさを取得
	void SetUseFlag(bool Flag) { m_bUse = Flag; };				// 使用フラグの取得

	//------------------- ゲッター関数
	D3DXVECTOR2	GetAreaSize() { return m_Area; };		// エリアの大きさを取得
	D3DXVECTOR2	GetCenterPos() { return m_CenterPos; };	// エリアの位置を取得
	D3DXVECTOR2	GetDirection() { return m_Direction; };	// 浮力の方向を取得
	float		GetForceValue() { return m_Force; };	// 浮力の大きさを取得
	bool		GetUseFlag() { return m_bUse; };		// 使用フラグの取得

private:
	//------------------- メンバ変数
	CTexture		m_Texture;		// エリアの描画
	D3DXVECTOR2		m_Area;			// 浮力加速エリア
	D3DXVECTOR2		m_CenterPos;	// 浮力加速エリアの中心点
	D3DXVECTOR2		m_Direction;	// 浮力の方向（単位ベクトル）
	float			m_Force;		// 浮力の大きさ
	bool			m_bUse;			// これを使用しているか
};

