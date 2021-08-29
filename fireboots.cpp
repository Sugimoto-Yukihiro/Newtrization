//==================================================================
//
// ファイヤーブーツ処理 [fireboots.cpp]
// Auther : 杉本幸宏
//
//==================================================================

#include "main.h"
#include "fireboots.h"

//==================================================================
// コンストラクタ・デストラクタ
//==================================================================
CFireBoots::CFireBoots()	// コンストラクタ
{
	Init();		// 初期化する
}

CFireBoots::~CFireBoots()	// デストラクタ
{
//	Uninit();	// 終了処理をする
}



//==================================================================
// 初期化処理
// 引数：バレットテクスチャのファイル名, バレットテクスチャの横分割数, バレットテクスチャの縦分割数, アニメーションのWait値
//==================================================================
void CFireBoots::Init(char* pBulletTextureName, int TexDivX, int TexDivY, int AnimWait)	// 初期化処理
{
	// バレットの初期化
	for (int i = 0; i < BOOTS_BULLET_NUM; i++)
	{
		m_Bullet[i].Init(pBulletTextureName, TexDivX, TexDivY, AnimWait);
		m_nFlameCnt[i] = 0;	// フレームカウントを初期化
		m_nCoolTime[i] = 0;	// クールタイムを初期化
	}

	// メンバ変数の初期化
	m_nUsedBulletNum = 0;
}



//==================================================================
// 終了処理
//==================================================================
void CFireBoots::Uninit()
{
	// メンバ変数の解放
	m_nUsedBulletNum = 0;

	// バレットの解放
	for (int i = 0; i < BOOTS_BULLET_NUM; i++)
	{
		m_Bullet[i].Uninit();
	}

}



//==================================================================
// 更新処理
//==================================================================
void CFireBoots::Update(D3DXVECTOR2 StageSize)
{
	// バレットの更新
	for (int i = 0; i < BOOTS_BULLET_NUM; i++)
	{
		// このバレットが使われていなかったら終了
		if (!m_Bullet[i].GetUseFlag()) continue;
		m_Bullet[i].Update();	// 更新

		// フレーム数をカウント
		m_nFlameCnt[i]++;

		// ステージ外にいったら、このバレットを解放
		if ((m_Bullet[i].GetPosition().x + (m_Bullet[i].GetSize().x * 0.5f)) < 0.0f ||			// 右端の点が、ステージ左端を超えたら解放
			(m_Bullet[i].GetPosition().x - (m_Bullet[i].GetSize().x * 0.5f)) > StageSize.x ||	// 左端の点が、ステージ右端を超えたら解放
			(m_Bullet[i].GetPosition().y + (m_Bullet[i].GetSize().y * 0.5f)) < 0.0f ||			// 下端の点が、ステージ上端を超えたら解放
			(m_Bullet[i].GetPosition().y - (m_Bullet[i].GetSize().y * 0.5f)) > StageSize.y	)	// 上端の点が、ステージ下端を超えたら解放
		{
			m_Bullet[i].UnsetBullet();	// バレット解放
			m_nFlameCnt[i] = 0;			// 経過フレーム数のリセット
			m_nUsedBulletNum--;			// 使用バレット数の減算
		}

	}

}



//==================================================================
// 描画処理
//==================================================================
void CFireBoots::Draw(D3DXVECTOR2 ScrollPos)
{
	// バレットの描画
	for (int i = 0; i < BOOTS_BULLET_NUM; i++)
	{
		m_Bullet[i].Draw(ScrollPos);	// 描画
	}

}



//==================================================================
// メンバ関数
//==================================================================
/*******************************************************************************
* 関数名	:	
* 引数	:	
* 返り値	:	
* 説明	:	ファイヤーブーツの起動（バレットを下方向に出して、キャラクターを少し浮かせる）
********************************************************************************/
bool CFireBoots::ActivateFireBoots(D3DXVECTOR2 Pos, D3DXVECTOR2 BulletMove, D3DXVECTOR2 BulletSize, float Attack, float HP)
{
	// 発射したバレットの数が、許可数を超えていたら失敗を返す
	if (m_nUsedBulletNum >= BOOTS_BULLET_NUM) return (false);

	// バレットの配置
	for (int i = 0; i < BOOTS_BULLET_NUM; i++)
	{
		// このバレットが使用中なら次のバレットへ
		if (m_Bullet[i].GetUseFlag()) continue;

		// 未使用のバレットをセット
		m_Bullet[i].SetBullet(Pos, BulletSize, BulletMove, Attack, HP);
		m_nUsedBulletNum++;		// 発射したバレットの数を加算

		// 成功を返す
		return (true);
	}

	// バレットをセットできなかったってことだから、失敗を返す
	return (false);
}




//==================================================================
// セッター関数
//==================================================================
///*******************************************************************************
//* 関数名	:	bool CFireBoots::SetFireBoots(D3DXVECTOR2* UserPos)
//* 引数	:	ファイヤーブーツを装着するキャラクタの座標を格納する変数へのポインタ
//* 返り値	:	成功(true) or 失敗(false)
//* 説明	:	ファイヤーブーツを装着する
//********************************************************************************/
//bool CFireBoots::SetFireBoots(D3DXVECTOR2* UserPos)
//{
//	// すでに装着されている状態であれば失敗を返す
//	if (m_pPosition != NULL) return (false);
//
//	// ポインタをセット
//	m_pPosition = UserPos;
//
//	// 成功を返す
//	return (true);
//}
//
///*******************************************************************************
//* 関数名	:	void CFireBoots::UnsetFireBoots()
//* 引数	:	void
//* 返り値	:	成功(true) or 失敗(false)
//* 説明	:	ファイヤーブーツの解除
//********************************************************************************/
//bool CFireBoots::UnsetFireBoots()
//{
//	// すでに解除されている状態であれば失敗を返す
//	if (m_pPosition == NULL) return (false);
//
//	// ポインタにNULLをセット
//	m_pPosition = NULL;
//
//	// 成功を返す
//	return (true);
//}
//
