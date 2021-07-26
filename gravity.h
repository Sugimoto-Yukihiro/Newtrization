//=============================================================================
//
// 重力処理 [gravity.h]
// Author : 稲垣佑二郎, 杉本幸宏
//
//=============================================================================
#pragma once

//#include "mapchip.h"	// マップチップ処理

//*****************************************************************************
// マクロ定義
//*****************************************************************************



//*****************************************************************************
// 列挙型
//*****************************************************************************
enum
{
	GRAVITY_DEFAULT, 
	GRAVITY_LEFT,

	GRAVITY_DIRECTION_MAX
};


//*****************************************************************************
// クラス
//*****************************************************************************
class CGravity
{
public:
	CGravity();		// コンストラクタ
	~CGravity();	// デストラクタ

	void Init();	// 初期化
	void Update();	// 更新

	//------------------- セッター関数
	void SetGravityObjectPos(D3DXVECTOR2 Pos);		// 座標のセット
	void SetGravityObjectSize(D3DXVECTOR2 Size);	// 大きさのセット
	void SetGravityObjectDirection(int Direction);	// このオブジェクトの重力の向きをセット
	void SetGravityWait(float GravityWait);			// このオブジェクトにかかる重力の大きさをセット
	void SetGravityFlag(bool Flag);					// 重力処理を行うフラグのセット

//	void SetAnotherForce(float Force);

	//------------------- ゲッター関数
	D3DXVECTOR2 GetGravityObjectPos();	// 座標の取得
	D3DXVECTOR2 GetGravityObjectSize();	// 大きさの取得
	int GetGravityFlameCnt();			// 経過フレーム数の取得
	int GetGravityObjectDirection();	// このオブジェクトの重力の向きをセット
	float GetGravityWait();				// このオブジェクトにかかる重力の大きさをセット
	bool GetGravityFlag();				// 重力処理を行うフラグのセット

//	float GetAnotherForce();

private:
	//------------------- メンバ変数
	D3DXVECTOR2 m_Position;		// 物体の中心座標
	D3DXVECTOR2 m_ObjectSize;	// 物体のサイズ
	int m_nDirection;			// 重力の向き
	float m_GravityWait;		// 重力加速度
//	float m_fForce;				// 重力以外に加わっている力
	int m_nFlameCount;			// 経過時間
	bool m_bFall;				// 重力処理のフラグ
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
