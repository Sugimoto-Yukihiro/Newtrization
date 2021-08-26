//==================================================================
//
// 浮力加速処理 [floatforce.cpp]
// Auther : 杉本幸宏
//
//==================================================================

#include "main.h"		// メイン
#include "floatforce.h"	// 浮力処理ヘッダー
#include "collision.h"	// 当たり判定

//==================================================================
// コンストラクタ・デストラクタ
//==================================================================
CFloatForce::CFloatForce()	// コンストラクタ
{
	Init();	// メンバ変数の初期化のみ
}

CFloatForce::~CFloatForce()	// デストラクタ
{

}

//==================================================================
// 初期化処理
//==================================================================
void CFloatForce::Init(char* TextureName)
{
	//------------------- メンバ変数の初期化
	m_Area = ZERO_VECTOR2;
	m_CenterPos = ZERO_VECTOR2;
	m_Direction = ZERO_VECTOR2;
	m_Force = 0.0f;
	m_bUse = false;		// 未使用で初期化

	// テクスチャの初期化
	m_Texture.Init();
	if (TextureName) m_Texture.CreateTextureInf(TextureName);	// テクスチャ情報の生成
}

//==================================================================
// 終了処理
//==================================================================
void CFloatForce::Uninit()
{
	//------------------- メンバ変数の終了処理
//	m_Area = ZERO_VECTOR2;
//	m_CenterPos = ZERO_VECTOR2;
//	m_Direction = ZERO_VECTOR2;
//	m_Force = 0.0f;
//	m_bUse = false;

	// テクスチャの終了処理
	m_Texture.Uninit();
	m_Texture.ReleaseTextureInf();
}

//==================================================================
// 更新処理
//==================================================================
void CFloatForce::Update()
{

}

//==================================================================
// 描画処理
//==================================================================
void CFloatForce::Draw(D3DXVECTOR2 ScrollPos)
{
	// 描画位置を算出
	m_Texture.SetTexPos(m_CenterPos - ScrollPos);	// 表示座標系にセット

	// テクスチャ描画
	m_Texture.DrawTexture();
}


//****************************************************
// 関数名	：void AddFloatForce(D3DXVECTOR2 *Pos);
// 説明		：浮力を対象オブジェクトに加えて、移動させる
// 引数		：対象オブジェクトの座標
// 戻り値	：void
//****************************************************
void CFloatForce::AddFloatForce(D3DXVECTOR2 *Pos)
{
	// 浮力を加える
	*Pos += m_Direction * m_Force;	// 与える力＝（方向）*（力の大きさ）
}

//****************************************************
// 関数名	：bool HitCheck(D3DXVECTOR2 *Pos, D3DXVECTOR2 Size);
// 説明		：引数に指定されたオブジェクトとの当たり判定（矩形）を行って、
//				当たっていたらそのオブジェクトに浮力を加える
// 引数		：対象オブジェクトの中心座標, 対象オブジェクトのサイズ
// 戻り値	：当たっている（true） or 当たっていない（false）
//****************************************************
bool CFloatForce::HitCheck(D3DXVECTOR2 *Pos, D3DXVECTOR2 Size)
{
	// 当たり判定実行
	if ( CollisionBB(*Pos, m_CenterPos,
					Size, m_Area) )
	{	// 当たっていた時の処理
		// 浮力を加える
		AddFloatForce(Pos);

		// 当たっている
		return(true);
	}

	// 当たっていない
	return(false);
}


//==================================================================
// セッター関数
//==================================================================
bool CFloatForce::SetFloatForceErea(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, D3DXVECTOR2 Dir, float Force, D3DXCOLOR Color)	// 浮力加速エリアのセット
{
	// 使用中なら false を返す
	if (m_bUse) return(false);

	m_Area = Size;					// 範囲をセット
	m_Texture.SetTexSize(m_Area);	// テクスチャの大きさもセット
	m_CenterPos = Pos;				// 中心座標をセット
	m_Direction = Dir;				// 方向をセット
	m_Force = Force;				// 力をセット
	m_bUse = true;					// 使用中にする

	// 色を設定
	m_Texture.SetTexColor(Color);

	// 成功を返す
	return(true);
}

void CFloatForce::SetDirection(D3DXVECTOR2 Dir)	// 浮力の方向をセット
{
	// 念のためノーマライズしてセットする
	D3DXVec2Normalize(&m_Direction, &Dir);
}
