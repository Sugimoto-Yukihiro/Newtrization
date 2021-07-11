//==================================================================
//
// マップチップ処理 [mapchip.h]
// Auther : 杉本幸宏
//
//==================================================================
#pragma once

#include "texture.h"


#define MAPCHIP_STATIC		// マップチップ情報を静的管理
//#define MAPCHIP_DYNAMIC		// マップチップ情報を動的管理

#define MAPCHIP_NUM_MAX_X	(64)
#define MAPCHIP_NUM_MAX_Y	(64)
#define MAPCHIP_NUM_MAX		(MAPCHIP_NUM_MAX_X * MAPCHIP_NUM_MAX_Y)

enum
{
	STAGE_NONE = -1,

	MAPCHIP_STAGE_Sample,
//	STAGE_Tutorial,

	MAPCHIP_PATTARN_MAX
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
//	void RotationMapChip(float Angle);		// マップチップステージの回転
	void DrawChip(D3DXVECTOR2 Pos, int Num);	// チップの描画

	int LoadMapchipData(char* pFileName);	// マップチップ情報のファイル読み込み


#ifdef MAPCHIP_DYNAMIC
//	int ReleaseMapchip();					// マップチップ情報の解放
#endif // MAPCHIP_DYNAMIC

	//------------------- セッター関数
	int SetMapChipData(const char* pCsvString);	// マップチップ配列を取得

	void SetMapchipBasePos(D3DXVECTOR2 Pos);
	void SetMapchipSize(D3DXVECTOR2 Size);	// １つのチップの大きさを取得
	void SetMapchipNumX(int Num);				// マップチップの列数を取得
	void SetMapchipNumY(int Num);				// マップチップの列数を取得
//	void SetRotationFlag(bool Flag);			// 回転フラグのセット


	//------------------- ゲッター関数
	int* GetMapChipData();				// マップチップ配列を取得
	D3DXVECTOR2 GetStageSize();			// マップ全体の大きさを取得

	D3DXVECTOR2 GetMapchipSize();		// １つのチップの大きさを取得
	int GetMapchipNumX();				// マップチップの列数を取得
	int GetMapchipNumY();				// マップチップの列数を取得
	int GetMapchipNo(D3DXVECTOR2 Pos);	// 指定された座標にあるチップ番号を取得
//	bool GetRotationFlag();				// 回転フラグの取得

private:
	//------------------- メンバ変数
	D3DXVECTOR2		m_vChipBasePos;		// 実際に描画するマップチップの基準（スクロール座標）
	D3DXVECTOR2		m_vChipSize;		// １つのチップの大きさ

#ifdef MAPCHIP_STATIC
	int				m_MapChipData[MAPCHIP_NUM_MAX];	// マップチップ情報
#endif // MAPCHIP_STATIC

#ifdef MAPCHIP_DYNAMIC
	int*			m_MapChipData;		// マップチップ情報
#endif // MAPCHIP_DYNAMIC

	int				m_nChipNumX;		// マップチップの列数
	int				m_nChipNumY;		// マップチップの行数
//	bool			m_bRotFlag;			// ステージの回転フラグ

};



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void CreateMapchipTextureAndBuffer(int MapchipPattarn);
void ReleaseMapchipTextureAndBuffer();


//*****************************************************************************
// グローバル変数
//*****************************************************************************
#ifdef _DEBUG
static char* pTestMapChipData = {
	"1,2,3\n2,2,2\n3,3,3\n12,22,32\n22,22,22"
};
#endif // _DEBUG
