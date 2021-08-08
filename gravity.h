//=============================================================================
//
// 重力処理 [gravity.h]
// Author : 稲垣佑二郎, 杉本幸宏
//
//=============================================================================
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// 列挙型
//*****************************************************************************
enum
{
	GRAVITY_DEFAULT,		// 重力下向き
	GRAVITY_LEFT,			// 重力左向き

	GRAVITY_DIRECTION_MAX	// 総パターン数
};


//*****************************************************************************
// クラス
//*****************************************************************************
class CGravity
{
public:
	CGravity();		// コンストラクタ
	~CGravity();	// デストラクタ

	void Init(D3DXVECTOR2 Pos = D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2 Size = D3DXVECTOR2(0.0f, 0.0f), float GravWait = 0.0f, int Direction = 0);	// 初期化
	void Uninit();	// 終了処理
	void Update();	// 更新

	//------------------- セッター関数
	void SetGravityObjectPos(D3DXVECTOR2 Pos);		// 座標のセット
	void SetGravityObjectSize(D3DXVECTOR2 Size);	// 大きさのセット
	void SetGravityWait(float GravityWait);			// このオブジェクトにかかる重力の大きさをセット
	void SetGravitySpeed(float Speed);				// このオブジェクトの速さをセット
	void SetGravityObjectDirection(int Direction);	// このオブジェクトの重力の方向をセット
	void SetGravityFlag(bool Flag);					// 重力処理を行うフラグのセット

	//------------------- ゲッター関数
	D3DXVECTOR2	GetGravityObjectPos();			// 座標の取得
	D3DXVECTOR2	GetGravityObjectSize();			// 大きさの取得
	float		GetGravityWait();				// このオブジェクトにかかる重力の大きさを取得
	float		GetGravitySpeed();				// このオブジェクトの速さを取得
	int			GetGravityObjectDirection();	// このオブジェクトの重力の向きを取得
	int			GetGravityFlameCnt();			// 経過時間（フレーム）数の取得
	bool		GetGravityFlag();				// 重力処理を行うフラグの取得

private:
	//------------------- メンバ変数
	D3DXVECTOR2	m_Position;		// 物体の中心座標
	D3DXVECTOR2	m_ObjectSize;	// 物体のサイズ
	float		m_GravityWait;	// 重力の大きさ
	float		m_fVerocity;	// 【重力大きさ * 経過時間】 によって得られる、この物体の速度
	int			m_nDirection;	// 重力の向き
	int			m_nFlameCount;	// 経過時間（単位はフレーム）
	bool		m_bFall;		// 重力処理のフラグ
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
