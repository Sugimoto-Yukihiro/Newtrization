//=============================================================================
//
// 毒処理 [poison.h]
// Author : 杉本幸宏
//
//=============================================================================
#pragma once

#include "mapchip.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPoison
{
public:
	CPoison();	// コンストラクタ
	~CPoison();	// デストラクタ

	// 初期化
//	void Init(CMapchip* Mapchip = NULL, D3DXVECTOR2* myLegPos = NULL, float* myHP = NULL, float Attack = 0.0f);
	void Init(D3DXVECTOR2* myLegPos = NULL, float* myHP = NULL, float Attack = 0.0f, int Wait = 0);
	void Uninit();	// 終了処理
	void Update();	// 更新処理
//	void Draw();	// 描画処理

	//------------------- メンバ関数

	//------------------- セッター関数
	void SetFlameWait(int Flame) { m_nFlameWait = Flame; };	// 何フレームおきに体力を削るかセット

	//------------------- ゲッター関数
	int GetFlameWait() { return m_nFlameCnt; };	// 体力を削るタイミングを取得

private:
//	CMapchip*		m_pMapchipInf;	// 今使用しているマップチップの情報
	D3DXVECTOR2*	m_pLegPosition;	// キャラクタの足の座標
	float*			m_pHitPointInf;	// キャラクタのHPを管理しているメモリへのポインタ
	float			m_fAttack;		// 毒の攻撃力
	int				m_nFlameCnt;	// 経過時間のカウント（単位はフレーム）
	int				m_nFlameWait;	// 体力を削るタイミング
};
