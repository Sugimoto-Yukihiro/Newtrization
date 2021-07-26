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
	// 全てのメンバ変数をゼロの値にセット
	m_Position = ZERO_VECTOR2;
	m_nDirection = GRAVITY_DEFAULT;
	m_GravityWait = DEFAULT_GRAVITY_WAIT;
	m_nFlameCount = 0;
	m_bFall = true;	// 重力処理は"true"をデフォルトにセット
}

//=============================================================================
// 終了処理
//=============================================================================


//=============================================================================
// 更新処理
//=============================================================================
//void CGravity::Update(CMapchip MapchipInf)
void CGravity::Update()
{
	if (!m_bFall) return;	// 重力フラグが立っていなかったら、処理をしない

	int nIdxNumX = 0, nIdxNumY = 0;

	// 経過フレーム数を加算
	m_nFlameCount++;

	// 重力の方向によって処理内容を変える
	if (m_nDirection == GRAVITY_DEFAULT)	// デフォルト（下向き）
	{
		// 変化するのはx座標
		m_Position.y += m_GravityWait * m_nFlameCount;
	}
	else if (m_nDirection == GRAVITY_LEFT)	// 左向き
	{
		// 変化するのはx座標
		m_Position.x -= m_GravityWait * m_nFlameCount;
	}

//	// マップチップとの当たり判定を取る
//	if (HitCheckMapchip(MapchipInf, &nIdxNumX, &nIdxNumY))
//	{	// 当たっていた時の処理
//		// 座標調整
//		m_Position.x = MapchipInf.GetMapchipSize().x * nIdxNumX;
//		m_Position.y = MapchipInf.GetMapchipSize().y * nIdxNumY;
//
//		// フレームカウントリセット
//		m_nFlameCount = 0;
//
//		// 重力処理フラグを折る
//		m_bFall = false;
//	}
}

//=============================================================================
// マップチップとの当たり判定
//=============================================================================
//bool CGravity::HitCheckMapchip(CMapchip MapchipInf, int* retIdxNumX, int* retIdxNumY)
//{
//	//	D3DXVECTOR2 pos1, pos2;
//	D3DXVECTOR2 pos;
//
//	//	pos1 = pos2 = m_Position;	// 中心座標で初期化
//	pos = m_Position;	// 中心座標で初期化
//
//	// マップチップと当たっているか判定
//	switch (m_nDirection)	// 重力の向きによって当たり判定の仕方を変える
//	{
//	case GRAVITY_DEFAULT:	// 下向きのとき
//
//		// posには左下の座標を格納
//		pos.x -= m_ObjectSize.x * 0.5f;
//		pos.y += m_ObjectSize.y * 0.5f;
//
//		for (int yi = 0; yi < 2; yi++)	// とりあえず二回やってみる
//		{
//			for (int xi = 0; xi < (m_ObjectSize.x / MapchipInf.GetMapchipSize().x); xi++)
//			{
//				pos.x += MapchipInf.GetMapchipSize().x * xi;	// 座標の位置を、マップチップのサイズ分だけ右へ
//
//				// 当たり判定チェック
//				if (MapchipInf.GetMapchipNo(pos, retIdxNumX, retIdxNumY) == 1)
//				{
//					return (true);	// 当たっている
//				}
//			}
//		}
//		break;
//
//	case GRAVITY_LEFT:
//
//		break;
//
//	default:
//		break;
//	}
//
//	// 当たっていない
//	return false;
//}



//=============================================================================
// セッター関数
//=============================================================================
void CGravity::SetGravityObjectPos(D3DXVECTOR2 Pos)
{
	m_Position = Pos;
}

void CGravity::SetGravityObjectSize(D3DXVECTOR2 Size)
{
	m_ObjectSize = Size;
}

void CGravity::SetGravityObjectDirection(int Direction)
{
	m_nDirection = Direction;
}

void CGravity::SetGravityWait(float GravityWait)
{
	m_GravityWait = GravityWait;
}

void CGravity::SetGravityFlag(bool Flag)
{
	// フラグが"false"のとき
	if (Flag == false)
	{
		m_nFlameCount = 0;	// フレームカウントをリセット
	}

	m_bFall = Flag;
}

//=============================================================================
// ゲッター関数
//=============================================================================
D3DXVECTOR2 CGravity::GetGravityObjectPos()
{
	return m_Position;
}

D3DXVECTOR2 CGravity::GetGravityObjectSize()
{
	return m_ObjectSize;
}

int CGravity::GetGravityObjectDirection()
{
	return m_nDirection;
}

float CGravity::GetGravityWait()
{
	return m_GravityWait;
}

int CGravity::GetGravityFlameCnt()
{
	return m_nFlameCount;
}

bool CGravity::GetGravityFlag()
{
	return m_bFall;
}
