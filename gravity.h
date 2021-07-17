//=============================================================================
//
// 重力処理 [gravity.h]
// Author : 稲垣佑二郎, 杉本幸宏
//
//=============================================================================
#pragma once

#include "mapchip.h"	// マップチップ処理

//*****************************************************************************
// マクロ定義
//*****************************************************************************



//*****************************************************************************
// 列挙型
//*****************************************************************************
enum DIRECTION
{
	GRAVITY_DEFAULT, 
	GRAVITY_LEFT
};


//*****************************************************************************
// クラス
//*****************************************************************************
class CGravity
{
public:
	CGravity();		// コンストラクタ
	~CGravity();	// デストラクタ

	void Init();
	void Update(CMapchip MapchipInf);
//	void Uninit();

	bool HitCheckMapchip(CMapchip MapchipInf, int* retIdxNumX, int* retIdxNumY);	// マップチップとの当たり判定を取る

	//------------------- セッター関数
	void SetGravityObjectPos(D3DXVECTOR2 Pos);
	void SetGravityObjectSize(D3DXVECTOR2 Size);
	void SetGravityObjectDirection(DIRECTION Direction);
	void SetGravityWait(float GravityWait);
	void SetGravityFlag(bool Flag);

	//------------------- ゲッター関数
	D3DXVECTOR2 GetGravityObjectPos();
	D3DXVECTOR2 GetGravityObjectSize();
	DIRECTION GetGravityObjectDirection();
	float GetGravityWait();
	int GetGravityFlameCnt();
	bool GetGravityFlag();

private:
	D3DXVECTOR2 m_Position;		// 物体の中心座標
	D3DXVECTOR2 m_ObjectSize;	// 物体のサイズ
	DIRECTION m_nDirection;		// 重力の向き
	float m_GravityWait;		// 重力加速度
	int m_nFlameCount;			// 経過時間
	bool m_bFall;				// 重力処理のフラグ
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
