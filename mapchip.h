//==================================================================
//
// マップチップ処理 [mapchip.h]
// Auther : 杉本幸宏
//
//==================================================================
#pragma once

#include "texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAPCHIP_STATIC				// マップチップ配列を静的管理
//#define MAPCHIP_DYNAMIC			// マップチップ配列を動的管理

#define MAPCHIP_SIZE_DEFAULT	D3DXVECTOR2(64.0f, 64.0f)		// マップチップのデフォルトサイズ

/* "MAPCHIP_HIT_min" ~ "MAPCHIP_HIT_MAX" の番号が当たり判定属性を持つマップチップ */
#define MAPCHIP_HIT_min		(1)		// 当たり判定属性のマップチップ番号の最小値
#define MAPCHIP_HIT_MAX		(9)		// 当たり判定属性のマップチップ番号の最大値

#define MAPCHIP_NUM_MAX_X	(64)	// マップチップの最大列数
#define MAPCHIP_NUM_MAX_Y	(64)	// マップチップの最大行数
#define MAPCHIP_NUM_MAX		(MAPCHIP_NUM_MAX_X * MAPCHIP_NUM_MAX_Y)	// マップチップの最大数（合計）

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
	CMapchip();		// コンストラクタ
	~CMapchip();	// デストラクタ

	//------------------- メンバ関数
//	void Init();	// 初期化
	void Init(char* pMapFileName = NULL);	// 初期化

	void Uninit();	// 終了処理
	void Draw();	// 描画処理
	void Update();	// 更新処理

//	void RotationMapChip(float Angle);		// マップチップステージの回転
	void DrawChip(D3DXVECTOR2 Pos, int Num);	// 1枚のチップの描画
	int LoadMapchipData(char* pFileName);	// マップチップ情報のファイル読み込み

#ifdef MAPCHIP_DYNAMIC
//	int ReleaseMapchip();					// マップチップ情報の解放
#endif // MAPCHIP_DYNAMIC

	//------------------- セッター関数
	int SetMapChipData(const char* pCsvString);	// マップチップ配列を取得

//	void SetMapchipBasePos(D3DXVECTOR2 Pos);	// 描画の基準座標をセット
	void SetMapchipSize(D3DXVECTOR2 Size);		// １つのチップの大きさをセット
	void SetMapchipNumX(int Num);				// マップチップの列数をセット
	void SetMapchipNumY(int Num);				// マップチップの列数をセット
	void SetMapchipNo(int No, int X, int Y);	// 指定した箇所のマップチップ番号を変更する
//	void SetRotationFlag(bool Flag);			// 回転フラグのセット


	//------------------- ゲッター関数
	int* GetMapChipData();				// マップチップ配列を取得
	D3DXVECTOR2 GetStageSize();			// マップ全体の大きさを取得
	D3DXVECTOR2 GetMapchipSize();		// １つのチップの大きさを取得
	int GetMapchipNumX();				// マップチップの列数を取得
	int GetMapchipNumY();				// マップチップの列数を取得
	int GetMapchipNo(int nIdxNo);		// 配列の要素数を指定して、マップチップ番号を取得
									//	 ↓ 帰ってくる数値の最小値は０ ↓
	int GetMapchipNo(D3DXVECTOR2 Pos, int* retIdxNumX = NULL, int* retIdxNumY = NULL);	// 指定された座標にあるチップ番号を取得
//	bool GetRotationFlag();				// 回転フラグの取得

private:
	//------------------- メンバ変数
//	D3DXVECTOR2		m_vChipBasePos;		// 実際に描画するマップチップの基準（スクロール座標）
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
