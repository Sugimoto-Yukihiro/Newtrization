//=============================================================================
//
// エネミー処理 [enemy.h]
// Author : 稲垣佑二郎, 杉本幸宏
//
//=============================================================================
#pragma once

#include "texture.h"	// テクスチャ描画処理
#include "gravity.h"	// 重力処理

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// enum
//*****************************************************************************
enum
{
	ENEMY_TEX_01,			// エネミーテクスチャ(TexNo：0)
	ENEMY_TEX_LEFT,		// エネミーテクスチャ（右向き）

	ENEMY_TEX_PATTARN_MAX	// リザルト画面で使用されているテクスチャの総数
};


//*****************************************************************************
// クラス
//*****************************************************************************
class CEnemy : public CTexture	//, public CGravity
{
public:
	CEnemy();
	~CEnemy();

	void Init();
	void Update();
	void Draw(D3DXVECTOR2 ScrollPos);
//	void Uninit();

	// 指定の位置にエネミーを置く処理
	bool SetEnemy(D3DXVECTOR2 Pos);	// 引数：このエネミーを置きたい場所

	void KillEnemy();	// このエネミーを殺す処理

	// メンバ変数へのアクセサー関数
	void SetPos(D3DXVECTOR2 Pos) { m_pos = Pos; };
	D3DXVECTOR2 GetPos() { return m_pos; };

	void SetTexNo(int TexNo) { m_texNo = TexNo; };
	bool GetTexNo() { return m_texNo; };

	void SetUse(bool Use) { m_use = Use; };
	bool GetUse() { return m_use; };

private:
	D3DXVECTOR2		m_pos;			// ポリゴンの座標
//	D3DXVECTOR3		m_rot;			// ポリゴンの回転量
//	float			m_w, m_h;		// 幅と高さ
//	float			m_time;			// 線形補間の時間管理用
//	int				m_countAnim;	// アニメーションカウント
//	int				m_patternAnim;	// アニメーションパターンナンバー
	int				m_texNo;		// テクスチャ番号
	bool			m_left;			// true:左へ移動
	bool			m_use;			// true:使っている  false:未使用

	/* 継承しているからこのインスタンスは必要ない */
//	CTexture m_Tex[ENEMY_TEX_PATTARN_MAX];	// 使用テクスチャ(上のenumのパターン数だけ用意)
};



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEnemy(void);
void UninitEnemy(void);
//void UpdateEnemy(void);
//void DrawEnemy(void);

//ENEMY *GetEnemy(void);


