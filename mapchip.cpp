//==================================================================
//
// マップチップ処理 [mapchip.cpp]
// Auther : 杉本幸宏
//
//==================================================================

#include "main.h"
#include "renderer.h"
#include "mapchip.h"	// マップチップ
#include "game.h"		// ゲーム画面


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAPCHIP_SIZE_DEFAULT	D3DXVECTOR2(64.0f, 64.0f)		// マップチップのデフォルトサイズ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void PresetDrawMapchip();	// 描画する前準備

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer				*g_VertexBuffer = NULL;						// 頂点情報
static ID3D11ShaderResourceView	*g_Texture = { NULL };	// テクスチャ情報

// テクスチャのファイル名
static char *g_TextureName[] = {
	"data/TEXTURE/mapchip/mapchip_sample.png",		// MAPCHIP_STAGE_Sample
};


//=============================================================================
// コンストラクタ・デストラクタ
//=============================================================================
CMapchip::CMapchip()	// コンストラクタ
{
	//------------------- メンバ変数の初期化
//	SetMapchipBasePos(ZERO_VECTOR2);
	SetMapchipSize(MAPCHIP_SIZE_DEFAULT);	// １つのチップの大きさをセット
	SetMapchipNumX(-1);				// マップチップの列数をセット
	SetMapchipNumY(-1);				// マップチップの列数をセット

}

CMapchip::~CMapchip()	// デストラクタ
{

}



//=============================================================================
// 初期化処理
//=============================================================================
void CMapchip::Init()
{
	//------------------- メンバ変数の初期化
	m_nChipNumX = 1;	// マップチップの列数
	m_nChipNumY = 1;	// マップチップの行数

	//------------------- テクスチャ関連の初期化
	SetTexDivideX(4);
	SetTexDivideY(4);


	// マップチップ配列のセット
//	SetMapChipData(pTestMapChipData);
	LoadMapchipData("data/MAPCHIP/mapdata1.01.csv");
//	LoadMapchipData("data/MAPCHIP/mapdata1.02.csv");
}



//=============================================================================
// 終了処理
//=============================================================================
void CMapchip::Uninit()
{

}



//=============================================================================
// 更新処理
//=============================================================================
void CMapchip::Update()
{
	// 描画の基準座標を更新
//	SetBasePos(ScrollPosition);
}



//=============================================================================
// 描画処理
//=============================================================================
void CMapchip::Draw()
{
	// 描画する前に呼び出す
	PresetDrawMapchip();

	D3DXVECTOR2 ScrollPos;
	float offset_x, offset_y;
	int numx, numy;
	int nDrawChipNumX, nDrawChipNumY;

	// 表示座標の取得("ScrollPos"→スクロール座標)
	ScrollPos = GetGame()->GetScrollPosition();

	numx = (int)(ScrollPos.x / GetMapchipSize().x) - 1;	// スクロール座標より左側（画面外）にあるマップチップ数
	numy = (int)(ScrollPos.y / GetMapchipSize().y) - 1;	// スクロール座標より上側（画面外）にあるマップチップ数

	// マップチップ表示座標の算出
//	offset_x = GetMapchipSize().x - ScrollPos.x;
	offset_x = -ScrollPos.x;
//	offset_y = GetMapchipSize().y - ScrollPos.y;
	offset_y = -ScrollPos.y;

	// 描画するチップ数を算出
	nDrawChipNumX = SCREEN_WIDTH / (int)GetMapchipSize().x + numx;		// 横方向(x軸)のチップ数
	nDrawChipNumY = SCREEN_HEIGHT / (int)GetMapchipSize().y + numy;	// 縦方向(y軸)のチップ数

	// マップ描画
	for (int y = numy; y < nDrawChipNumY + 2; y++)
	{
		for (int x = numx; x < nDrawChipNumX + 2; x++)
		{
			// マップの番号を取得
		//	int nChipId = m_MapChipData[(y + numy) * GetMapchipNumX() + (x + numx)];	// 
			int nChipId = m_MapChipData[y * GetMapchipNumX() + x];	// 

			if(nChipId == 0) continue;

			// チップの描画位置を算出
			D3DXVECTOR2 ChipCenterPos;
			ChipCenterPos.y = (float)(offset_y + (GetMapchipSize().y * y));	// 背景の表示座標Y
			ChipCenterPos.x = (float)(offset_x + (GetMapchipSize().x * x));	// 背景の表示座標X

			ChipCenterPos.y += GetMapchipSize().y * 0.5f;	// 中心座標にする
			ChipCenterPos.x += GetMapchipSize().x * 0.5f;	// 中心座標にする

			// 描画
			DrawChip(ChipCenterPos, nChipId);	// 描画座標が中心指定のとき
		}
	}








	////------------------- 描画するマップチップの最左のインデックス番号の算出
	//numx = (int)(ScrollPos.x / GetMapchipSize().x);		// スクロール座標より左側（画面外）にあるマップチップ数
	//numy = (int)(ScrollPos.y / GetMapchipSize().y);		// スクロール座標より上側（画面外）にあるマップチップ数

	//// 描画するマップチップの最左の表示座標の算出
	//offset_x = (numx * GetMapchipSize().x) - ScrollPos.x;	// 横位置
	//offset_y = (numy * GetMapchipSize().y) - ScrollPos.y;	// 縦位置

	//// 描画するチップ数を算出
	//nDrawChipNumX = SCREEN_WIDTH / (int)GetMapchipSize().x;		// 横方向(x軸)のチップ数
	//nDrawChipNumY = SCREEN_HEIGHT / (int)GetMapchipSize().y;	// 縦方向(y軸)のチップ数

	//// マップチップを一枚ずつ必要分だけ描画
	//for (iy = numy; iy < (numy + nDrawChipNumY); iy++)
	//{
	//	for (ix = numx; ix < (numx + nDrawChipNumX); ix++)
	//	{
	//		// マップの番号を取得
	//		int nChipId = m_MapChipData[ (iy * m_nChipNumX) + ix];

	//		// チップ番号が０なら描画しない
	//		if(nChipId == 0) continue;

	//		// チップの描画位置を算出
	//		D3DXVECTOR2 ChipCenterPos;
	//		ChipCenterPos.y = (float)(offset_y + (GetMapchipSize().y * iy));	// 背景の表示座標Y
	//		ChipCenterPos.x = (float)(offset_x + (GetMapchipSize().x  * ix));	// 背景の表示座標X

	//		ChipCenterPos.y += GetMapchipSize().y * 0.5f;	// 中心座標にする
	//		ChipCenterPos.x += GetMapchipSize().x * 0.5f;	// 中心座標にする

	//		// 描画
	//		DrawChip(ChipCenterPos, nChipId);	// 描画座標が中心指定のとき

	//	//	// 当たり判定処理のチップの場合 → 当たり判定のマップチップ変数を用意
	//	//	for (int i = 0; i < WALL_NUM_PATTARN; i++)
	//	//	{
	//	//		if (chip_id == WallNum[i])
	//	//		{
	//	//			// 座標を表示座標からワールド座標に変換
	//	//			VECTOR worldPos = ChipCenterPos;
	//	//			worldPos.ix += ScrollPos->ix;
	//	//			worldPos.y += ScrollPos->y;
	//	//			SetMapChipData(worldPos, chip_id, y, ix);	// マップチップ変数に情報を代入
	//	//		}
	//	//	}

	//	}
	//}

}

// チップの描画
void CMapchip::DrawChip(D3DXVECTOR2 Pos, int Num)
{
	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture);

	float tw = 1.0f / GetTexDivideX();	// テクスチャの幅
	float th = 1.0f / GetTexDivideY();	// テクスチャの高さ
	float tx = (float)(Num % GetTexDivideX()) * tw;	// テクスチャの左上X座標
	float ty = (float)(Num / GetTexDivideX()) * th;	// テクスチャの左上Y座標

	// １枚のポリゴンの頂点とテクスチャ座標を設定
	SetSprite(g_VertexBuffer, Pos.x, Pos.y, GetMapchipSize().x, GetMapchipSize().y, tx, ty, tw, th);

	// ポリゴン描画
	GetDeviceContext()->Draw(4, 0);
}


//=============================================================================
// セッター関数
//=============================================================================
//****************************************************
// 説明		： マップチップ配列のセット
// 引数		： マップチップの情報（char型）
// 戻り値	： 成功(1), 失敗(0)
//****************************************************
int CMapchip::SetMapChipData(const char* pCsvString)
{
	int nTokenCnt = 0;
	int nLinesCnt = 0;
	char* pCopyStr;
//	char* pLinesStr;
	char* pToken;

	// 引数の文字列をコピー
	pCopyStr = new char [ strlen(pCsvString) + NULL_SIZE ];	// メモリ確保
	memset(pCopyStr, '\0', strlen(pCsvString) + NULL_SIZE);	// 初期化
	memcpy(pCopyStr, pCsvString, strlen(pCsvString));		// 文字列コピー

	// 先頭から、順に字句を取得する
//	strtok(pCopyStr, ",");	// 先頭の字句
	pToken = pCopyStr;
	while (pToken = strtok(pToken, ","))
	{
		if (strrchr(pToken, '\n') != NULL)	// 改行コードがあったとき
		{
			// 先頭の１文字のみを抽出
			char singleWord[2] = { "\0" };
			strncat(singleWord, pToken, 1);

			m_MapChipData[nTokenCnt] = atoi(singleWord);	// 数値代入
			nTokenCnt++;	// マップチップの列数を加算
			nLinesCnt++;	// マップチップの行数も加算
		}
		else
		{
			m_MapChipData[nTokenCnt] = atoi(pToken);		// 数値代入
			nTokenCnt++;	// マップチップの列数を加算
		}

		pToken = NULL;		// 次の字句を取得するためNULLをセット
	}

	// マップチップの列数をセット
	SetMapchipNumX(nTokenCnt / nLinesCnt);

	// マップチップの行数をセット
	SetMapchipNumY(nLinesCnt);


	// マップチップの列数を算出
//	SetMapchipNumX( (SerchWordOffset(pCsvString, '\n') + 1) / 2 );	// カンマの文字数分を引く
//
//	// 一行目の文字列を取得
////	pLinesStr = strtok(pCopyStr, "\n");
//	pLinesStr = pCopyStr;
//	do
//	{
//		char* pBuf = new char [ strlen(pLinesStr) + NULL_SIZE ];
//		strcpy(pBuf, pLinesStr);	// 文字列コピー
//
//		// カンマに区切られた先頭の文字を取得
//		pToken = strtok(pBuf, ",");		/* これが２行目以降読み取れない原因…!?　→　strtokはstatic変数を使用しているから！ */
//		nTokenCnt = 0;	// カウントリセット
//		do
//		{
//			// トークンが数値であるか判断
//		//	if (isdigit(pToken))
//			{
//				m_MapChipData[nTokenCnt] = atoi(pToken);	// 数値代入
//
//				// トークン数のカウント
//			//	nTokenCnt++;
//			}
//
//			// 次の字句を取得
//			pToken = strtok(NULL, ",");
//		} while (pToken != NULL);	// 字句が見つからなくなるまで繰り返し
//
//		// カウントしたトークン数を、列数を保存するメンバ変数へ代入
//	//	if (nTokenCnt > GetMapchipNumX()) SetMapchipNumX(nTokenCnt);
//
//		// 確保したヒープ領域のメモリを解放
//		delete[] pBuf;
//
//		// 行数のカウント
//		nLinesCnt++;
//
//		// 次の行の文字列を取得
//	//	pLinesStr = strtok(NULL, "\n");
//		pLinesStr += nTokenCnt;
//	} while (pLinesStr != NULL);
//
//	// カウントした行数を、マップチップの行数を保存するメンバ変数へ代入
//	SetMapchipNumY(nLinesCnt);


	// コピーした文字列の解放
	delete[] pCopyStr;

	return 0;	// 成功
}

// マップチップ配列を、ファイルから読み込んでセット
//****************************************************
// 引数		： マップチップのファイル名（char型）
// 戻り値	： 成功(1), 失敗(0)
//****************************************************
int CMapchip::LoadMapchipData(char* pFileName)
{
	char* pLoad = NULL;
	LoadCsvFile(pFileName, pLoad, 8, ",");	// 読み込み

	SetMapChipData(pLoad);

	delete[] pLoad;
	return 0;	// 成功
}

// 描画の基準座標をセット
//void CMapchip::SetMapchipBasePos(D3DXVECTOR2 Pos)
//{
//	m_vChipBasePos = Pos;
//}

// １つのチップの大きさをセット
void CMapchip::SetMapchipSize(D3DXVECTOR2 Size)
{
	m_vChipSize = Size;
}

// マップチップの列数をセット
void CMapchip::SetMapchipNumX(int Num)
{
	m_nChipNumX = Num;
}

// マップチップの列数をセット
void CMapchip::SetMapchipNumY(int Num)
{
	m_nChipNumY = Num;
}

// 回転フラグのセット
//void CMapchip::SetRotationFlag(bool Flag)
//{
//	m_bRotFlag = Flag;
//}

//=============================================================================
// ゲッター関数
//=============================================================================
// マップ全体の大きさを取得
D3DXVECTOR2 CMapchip::GetStageSize()
{
	D3DXVECTOR2 ans;
	ans.x = m_vChipSize.x * m_nChipNumX;	// 幅を格納
	ans.y = m_vChipSize.y * m_nChipNumY;	// 高さを格納

	return ans;
}

// １つのチップの大きさを取得
D3DXVECTOR2 CMapchip::GetMapchipSize()
{
	return m_vChipSize;
}

// マップチップ配列を取得
int* CMapchip::GetMapChipData()
{
	return m_MapChipData;
}

// マップチップの列数を取得
int CMapchip::GetMapchipNumX()
{
	return m_nChipNumX;
}

// マップチップの行数を取得
int CMapchip::GetMapchipNumY()
{
	return m_nChipNumY;
}

//****************************************************
// 説明		： 指定された座標にあるチップ番号を取得
// 引数		： 任意の座標, マップチップの要素数(横)を返すポインタ, マップチップの要素数(縦)を返すポインタ
// 戻り値	： 第一引数に指定された箇所のマップチップの番号
//****************************************************
int CMapchip::GetMapchipNo(D3DXVECTOR2 Pos, int* retIdxNumX, int* retIdxNumY)
{
	int cx = (int)(Pos.x / m_vChipSize.x);
	int cy = (int)(Pos.y / m_vChipSize.y);

	return m_MapChipData[cx + (cy * m_nChipNumX)];
}

// 回転フラグの取得
//bool CMapchip::GetRotationFlag()
//{
//	return m_bRotFlag;
//}







void CreateMapchipTextureAndBuffer(int MapchipPattarn)
{
	// テクスチャ生成
	CreateTexture(g_TextureName[MapchipPattarn], &g_Texture);

	// 頂点バッファ生成
	CreateVertexBuffer(&g_VertexBuffer);

}

void ReleaseMapchipTextureAndBuffer()
{
	ReleaseTexture(&g_Texture, &g_VertexBuffer);
}

void PresetDrawMapchip()
{
	PresetDraw2D(&g_VertexBuffer);
}