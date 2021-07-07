//==================================================================
//
// マップチップ処理 [mapchip.h]
// Auther : 杉本幸宏
//
//==================================================================
#pragma once

#include "texture.h"

enum
{
	STAGE_NONE = -1,

	MAPCHIP_STAGE_Sample,
//	STAGE_Tutorial,

	MAPCHIP_MAX
};

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CMapchip : public CTexture
{
public:
	CMapchip();			// コンストラクタ
	~CMapchip();		// デストラクタ

	//------------------- メンバ関数
	void Init();		// 初期化
	void Uninit();		// 終了処理
	void Draw();		// 描画処理
	void Update();		// 更新処理

	int LoadMapchip(char* pChipFileName);	// マップチップ情報の読み込み
	int ReleaseMapchip();					// マップチップ情報の解放
	void RotationMapChip(float Angle);		// マップチップステージの回転

	//------------------- セッター関数
//	void SetMapchipPos(D3DXVECTOR2 Pos);
//	void SetMapchipNum(int Num);
	void SetRotationFlag(bool Flag);	// 回転フラグのセット

	//------------------- ゲッター関数
//	D3DXVECTOR2 GetMapchipPos();
	D3DXVECTOR2 GetMapSize();			// マップ全体の大きさを取得
	D3DXVECTOR2 GetMapchipSize();		// １つのチップの大きさを取得
	int* GetMapChipData();				// マップチップ配列を取得
	int GetMapchipNumX();				// マップチップの列数を取得
	int GetMapchipNo(D3DXVECTOR2 Pos);	// 指定された座標にあるチップ番号を取得
	bool GetRotationFlag();				// 回転フラグの取得

private:
	//------------------- メンバ変数
//	D3DXVECTOR2		m_vMChipPosition;	// 座標
	D3DXVECTOR2		m_vChipSize;		// １つのチップの大きさ
	int*			m_pMapChipData;		// マップチップ情報
	int				m_nChipNumX;		// マップチップの列数
	int				m_nChipNumY;		// マップチップの行数
	int				m_nChipNo;			// マップチップの番号
	bool			m_bRotFlag;			// ステージの回転フラグ
//	bool			m_bUse;				// このマップチップ変数が使われているか

};


//*****************************************************************************
// プロトタイプ定義
//*****************************************************************************
void InitMapchip();
void UninitMapchip();
void UpdateMapchip();
void DrawMapchip();