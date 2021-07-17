//=============================================================================
//
// タイトル画面処理 [opening.h]
// Author : 立石大智
//
//=============================================================================
#pragma once

#include "texture.h"

// オープニング画面処理の管理方法の選択
//#define GAMEMODE_STRUCT
#define OPENINGMODE_CLASS

// クラス管理
#ifdef OPENINGMODE_CLASS

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CModeOpening
{
public:
	//------------------- メンバ関数
	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	//------------------- メンバ変数
	bool					m_bUse;						// true:使っている  false:未使用
	int						m_nTexNo;					// テクスチャ番号
	float					m_fbeta;
	bool					m_bflag_beta;

	CTexture				m_Logo;
};
#endif // OPENINGMODE_CLASS

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void CreateOpeningTextureAndBuffer(void);
void ReleaseOpeningTextureAndBuffer(void);
void PresetDrawOpening(void);
// 構造体管理
#ifdef OPENINGMODE_STRUCT

#endif // OPENINGMODE_STRUCT
