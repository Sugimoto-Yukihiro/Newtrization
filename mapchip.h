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

#define MAPCHIP_NUM_MAX_X	(64)	// マップチップの最大列数
#define MAPCHIP_NUM_MAX_Y	(64)	// マップチップの最大行数
#define MAPCHIP_NUM_MAX		(MAPCHIP_NUM_MAX_X * MAPCHIP_NUM_MAX_Y)	// マップチップの最大数（合計）

enum
{
	STAGE_NONE = -1,

	MAPCHIP_STAGE_Sample,	// サンプルの画像
	MAPCHIP_STAGE_Game,		// ゲームのマップチップ
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
	// 初期化（引数に何も指定しなくても動く）
	void Init(char* pMapFileName = NULL, int TexDivX = 0, int TexDivY = 0, D3DXVECTOR2 Size = MAPCHIP_SIZE_DEFAULT);

	void Uninit();	// 終了処理
	void Draw();	// 描画処理
	void Update();	// 更新処理

	int LoadMapchipData(char* pFileName);		// マップチップ情報のファイル読み込み
	void DrawChip(D3DXVECTOR2 Pos, int Num);	// 1枚のチップの描画
//	void RotationMapChip(float Angle);			// マップチップステージの回転

#ifdef MAPCHIP_DYNAMIC
//	int ReleaseMapchip();					// マップチップ情報の解放
#endif // MAPCHIP_DYNAMIC

	//------------------- セッター関数
	int SetMapChipData(const char* pCsvString);	// マップチップ配列を取得
	void SetMapchipSize(D3DXVECTOR2 Size);		// １つのチップの大きさをセット
	void SetMapchipNumX(int Num);				// マップチップの列数をセット
	void SetMapchipNumY(int Num);				// マップチップの列数をセット
	void SetMapchipNo(int No, int X, int Y);	// 指定した箇所のマップチップ番号を変更する
//	void SetRotationFlag(bool Flag);			// 回転フラグのセット


	//------------------- ゲッター関数
	D3DXVECTOR2 GetStageSize();			// マップ全体の大きさを取得
	D3DXVECTOR2 GetMapchipSize();		// １つのチップの大きさを取得
	D3DXVECTOR2 GetMapchipPosition(int nIdxNo);	// マップチップ配列の要素数(一次元)を、D3DXVECTOR2 で取得。返ってくるのはチップの中心座標


	int* GetMapChipData() { return m_MapChipData; };	// マップチップ配列を取得
	int GetMapchipNumX() { return m_nChipNumX; };		// マップチップの列数を取得
	int GetMapchipNumY() { return m_nChipNumY; };		// マップチップの列数を取得
	int GetMapchipNo(int nIdxNo) { return m_MapChipData[nIdxNo]; } ;		// 配列の要素数を指定して、マップチップ番号を取得
									//	 ↓ 返ってくる数値の最小値は０ ↓
	int GetMapchipNo(D3DXVECTOR2 Pos, int* retIdxNumX = NULL, int* retIdxNumY = NULL);	// 指定された座標にあるチップ番号を取得
//	bool GetRotationFlag() { return m_bRotFlag; } ;		// 回転フラグの取得

private:
	//------------------- メンバ変数
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
void CreateMapchipTexture(int MapchipPattarn);	// マップチップテクスチャの生成
void ReleaseMapchipTexture(void);				// マップチップテクスチャの解放


//*****************************************************************************
// グローバル変数
//*****************************************************************************
