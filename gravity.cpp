//=============================================================================
//
// 重力処理 [gravity.cpp]
// Author : 稲垣佑二郎, 杉本幸宏
//
//=============================================================================

#include "main.h"
#include "gravity.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define DEFAULT_GRAVITY_WAIT		(0.55f)		// 重力の値(デフォルトの時)
#define LEFT_GRAVITY_WAIT			(0.55f)		// 重力の値(左方向の時)



//=============================================================================
// コンストラクタ・デストラクタ
//=============================================================================
CGravity::CGravity()	// コンストラクタ
{
	Init();	// メンバ変数を初期化する
}

CGravity::~CGravity()	// デストラクタ
{

}



//=============================================================================
// 初期化処理
//=============================================================================
void CGravity::Init()
{
	// 全てのメンバ変数をデフォルトの値にセット
	m_Position = ZERO_VECTOR2;
	m_GravityWait = DEFAULT_GRAVITY_WAIT;
	m_fVerocity = 0.0f;	/* ここベクトルにしたい */
	m_nDirection = GRAVITY_DEFAULT;
	m_nFlameCount = 0;
	m_bFall = true;	// 重力処理は"true"をデフォルトにセット
}



//=============================================================================
// 終了処理
//=============================================================================
void CGravity::Uninit()
{
	// 全てのメンバ変数をゼロの値にセット
	m_Position = ZERO_VECTOR2;
	m_GravityWait = 0.0f;
	m_fVerocity = 0.0f;
	m_nDirection = 0;
	m_nFlameCount = 0;
	m_bFall = true;	// 重力処理は"true"をデフォルトにセット
}



//=============================================================================
// 更新処理
//=============================================================================
void CGravity::Update()
{
	if (!m_bFall) return;	// 重力フラグが立っていなかったら、処理をしない

	int nIdxNumX = 0, nIdxNumY = 0;

	// 経過フレーム数を加算
	m_nFlameCount++;

	// 重力の方向によって処理内容を変える
	if (m_nDirection == GRAVITY_DEFAULT)	// デフォルト（下向き）
	{
		// 変化するのはｙ座標
		m_fVerocity = m_GravityWait * m_nFlameCount;	// 【重力 * 経過時間】で速さを算出
		m_Position.y += m_fVerocity;		// 速さを足す
	}
	else if (m_nDirection == GRAVITY_LEFT)	// 左向き
	{
		// 変化するのはｘ座標
		m_fVerocity = m_GravityWait * m_nFlameCount;	// 【重力 * 経過時間】で速さを算出
		m_Position.x -= m_fVerocity;		// 速さを足す
	}

}



//=============================================================================
// セッター関数
//=============================================================================
// 座標のセット
void CGravity::SetGravityObjectPos(D3DXVECTOR2 Pos)
{
	m_Position = Pos;
}

// 大きさのセット
void CGravity::SetGravityObjectSize(D3DXVECTOR2 Size)
{
	m_ObjectSize = Size;
}

// このオブジェクトにかかる重力の大きさをセット
void CGravity::SetGravityWait(float GravityWait)
{
	m_GravityWait = GravityWait;
}

// このオブジェクトの速さをセット
void CGravity::SetGravitySpeed(float Speed)
{
	m_fVerocity = Speed;	// 速さをセット
}

// このオブジェクトの重力の方向をセット
void CGravity::SetGravityObjectDirection(int Direction)
{
	m_nDirection = Direction;	
}

// 重力処理を行うフラグのセット
void CGravity::SetGravityFlag(bool Flag)
{
	// フラグが"false"のとき
	if (!Flag) m_nFlameCount = 0;	// フレームカウントをリセット
	m_bFall = Flag;	// 重力処理フラグのセット
}

//=============================================================================
// ゲッター関数
//=============================================================================
// 座標の取得
D3DXVECTOR2 CGravity::GetGravityObjectPos()
{
	return m_Position;		// 座標を返す
}

// 大きさの取得
D3DXVECTOR2 CGravity::GetGravityObjectSize()
{
	return m_ObjectSize;	// このオブジェクトの大きさを返す
}

// このオブジェクトにかかる重力の大きさを取得
float CGravity::GetGravityWait()
{
	return m_GravityWait;	// 重力の大きさの変数値を返す
}

// このオブジェクトの速さを取得
float CGravity::GetGravitySpeed()
{
	return m_fVerocity;		// 速度を返す
}

// このオブジェクトの重力の向きを取得
int CGravity::GetGravityObjectDirection()
{
	return m_nDirection;	// 重力方向を返す
}

// 経過時間（フレーム）数の取得
int CGravity::GetGravityFlameCnt()
{
	return m_nFlameCount;	// 経過フレーム数を返す
}

// 重力処理を行うフラグの取得
bool CGravity::GetGravityFlag()
{
	return m_bFall;			// 重力フラグの真偽値を返す
}
