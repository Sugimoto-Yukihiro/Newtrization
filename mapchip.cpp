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


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11ShaderResourceView	*g_Texture = { NULL };	// テクスチャ情報

// テクスチャのファイル名
static char *g_TextureName[] = {
	"data/TEXTURE/mapchip/mapchip_sample.png",	// MAPCHIP_STAGE_Sample
	"data/TEXTURE/mapchip/Mapchip.png",			// MAPCHIP_STAGE_Game
};


//=============================================================================
// コンストラクタ・デストラクタ
//=============================================================================
CMapchip::CMapchip()	// コンストラクタ
{
	//------------------- メンバ変数の初期化
	m_vChipSize = MAPCHIP_SIZE_DEFAULT;	// １つのチップの大きさをセット（）
	m_nChipNumX = -1;					// マップチップの列数をセット
	m_nChipNumY = -1;					// マップチップの列数をセット

}

CMapchip::~CMapchip()	// デストラクタ
{

}



//=============================================================================
// 初期化処理
//=============================================================================
void CMapchip::Init(char* pMapFileName, int TexDivX, int TexDivY, D3DXVECTOR2 ChipSize)
{
	//------------------- テクスチャ関連の初期化
	CTexture::Init();
	SetTexDivideX(TexDivX);	// 分割数を指定
	SetTexDivideY(TexDivY);	// 分割数を指定

	//------------------- メンバ変数の初期化
	m_vChipSize = ChipSize;	// １つのチップの大きさ

	// マップチップ配列のセット
	if (pMapFileName == NULL)	// NULLならゼロで初期化
	{
		for (int i = 0; i < MAPCHIP_NUM_MAX; i++) m_MapChipData[i] = 0;
		m_nChipNumX = 0;	// マップチップの列数はゼロ
		m_nChipNumY = 0;	// マップチップの行数はゼロ
	}
	else LoadMapchipData(pMapFileName);	// マップチップデータを読み込み
}



//=============================================================================
// 終了処理
//=============================================================================
void CMapchip::Uninit()	// 全ての変数を０クリア
{
	// マップチップ配列のクリア
	for (int i = 0; i < MAPCHIP_NUM_MAX; i++) m_MapChipData[i] = 0;

	m_vChipSize = ZERO_VECTOR2;	// チップの大きさをクリア
	m_nChipNumX = 0;			// マップチップの列数をクリア
	m_nChipNumY = 0;			// マップチップの行数をクリア

	//------------------- テクスチャクラスの終了処理
	CTexture::Uninit();
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
	// 使用する変数の宣言
	D3DXVECTOR2 ScrollPos;
	float offset_x, offset_y;
	int numx, numy;
	int nDrawChipNumX, nDrawChipNumY;

	// 表示座標の取得("ScrollPos"→スクロール座標)
	ScrollPos = GetGame()->GetScrollPosition();

	numx = (int)(ScrollPos.x / GetMapchipSize().x) - 1;	// スクロール座標より左側（画面外）にあるマップチップ数
	numy = (int)(ScrollPos.y / GetMapchipSize().y) - 1;	// スクロール座標より上側（画面外）にあるマップチップ数

	// マップチップ表示座標の算出
	offset_x = -ScrollPos.x;
	offset_y = -ScrollPos.y;

	// 描画するチップ数を算出
	nDrawChipNumX = SCREEN_WIDTH / (int)GetMapchipSize().x + numx;	// 横方向(x軸)のチップ数
	nDrawChipNumY = SCREEN_HEIGHT / (int)GetMapchipSize().y + numy;	// 縦方向(y軸)のチップ数

	// マップ描画
	for (int y = numy; y < nDrawChipNumY + 3; y++)	// 2は中途半端に出てるやつ
	{
		for (int x = numx; x < nDrawChipNumX + 3; x++)
		{
			// マップの番号を取得
		//	int nChipId = m_MapChipData[(y + numy) * GetMapchipNumX() + (x + numx)];	// 
			int nChipId = m_MapChipData[y * GetMapchipNumX() + x];	// 

			// チップ番号が0番のときは描画しない
			if(nChipId == 0) continue;

			// チップの描画位置を算出
			D3DXVECTOR2 ChipPos;
			ChipPos.y = (float)(offset_y + (GetMapchipSize().y * y));	// 背景の表示座標Y
			ChipPos.x = (float)(offset_x + (GetMapchipSize().x * x));	// 背景の表示座標X

			// 描画
			DrawChip(ChipPos, nChipId);	// 描画座標が中心指定のとき
		}
	}

}

// チップ１枚の描画
void CMapchip::DrawChip(D3DXVECTOR2 Pos, int Num)
{
	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture);

	float tw = 1.0f / GetTexDivideX();	// テクスチャの幅
	float th = 1.0f / GetTexDivideY();	// テクスチャの高さ
	float tx = (float)(Num % GetTexDivideX()) * tw;	// テクスチャの左上X座標
	float ty = (float)(Num / GetTexDivideX()) * th;	// テクスチャの左上Y座標

	// １枚のポリゴンの頂点とテクスチャ座標を設定
	SetVertex(Pos.x, Pos.y, GetMapchipSize().x, GetMapchipSize().y, tx, ty, tw, th);

	// ポリゴン描画
	GetDeviceContext()->Draw(4, 0);
}



//=============================================================================
// メンバ関数
//=============================================================================
//****************************************************
// 説明		： マップチップ配列を、ファイルから読み込んでセット
// 引数		： マップチップのファイル名（char型）
// 戻り値	： 成功(1), 失敗(0)
//****************************************************
int CMapchip::LoadMapchipData(char* pFileName)
{
	// エラーチェック
	if (pFileName == NULL) 0;	// NULLなら失敗を返す
 
	char* pLoad = NULL;	// 読み込んだものを保存するメモリを示すポインタ
	// Csvファイルの、コメント部分を削除した状態のものを読み込み（カンマで区切られた数値データを抽出）
	LoadCsvFile(pFileName, pLoad, 8, ",");

	// カンマ区切りの数値を読み取って代入する
	SetMapChipData(pLoad);

	delete[] pLoad;
	return 1;	// 成功
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
	int nTokenCnt = 0;	// 数値代入したトークンのカウント ＝ マップチップの列数
	int nLinesCnt = 0;	// 行数のカウント
	char* pCopyStr;		// 引数の文字列をコピーしたメモリを示すポインタ
	char* pToken;		// strtok で切り抜いたトークンを示すポインタ

	// 引数の文字列をコピー
	pCopyStr = new char [ strlen(pCsvString) + NULL_SIZE ];	// メモリ確保
	memset(pCopyStr, '\0', strlen(pCsvString) + NULL_SIZE);	// 初期化
	memcpy(pCopyStr, pCsvString, strlen(pCsvString));		// 文字列コピー

	// 先頭から、順に字句を取得する
	pToken = pCopyStr;
	while (pToken = strtok(pToken, ","))
	{
		// 改行コードがあったとき
		if (strrchr(pToken, '\n') != NULL)
		{
			nLinesCnt++;	// マップチップの行数も加算
		}

		m_MapChipData[nTokenCnt] = atoi(pToken);		// 数値代入
		nTokenCnt++;		// マップチップの列数を加算

		pToken = NULL;		// 次の字句を取得するためNULLをセット
	}

	// マップチップの列数をセット
	SetMapchipNumX(nTokenCnt / nLinesCnt);

	// マップチップの行数をセット
	SetMapchipNumY(nLinesCnt);

	// コピーした文字列の解放
	delete[] pCopyStr;

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

// 指定した箇所のマップチップ番号を変更する
void CMapchip::SetMapchipNo(int No, int X, int Y)
{
	m_MapChipData[(Y * m_nChipNumX) + X];	// 番号を格納
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

// マップチップ配列の要素数(一次元)を、座標に変換
D3DXVECTOR2 CMapchip::GetMapchipPosition(int nIdxNo)
{
	// 使用する変数の宣言
//	D3DXVECTOR2 ans;
//	int X, Y;
//
//	X = nIdxNo % m_nChipNumX;	// 列数を算出
//	Y = nIdxNo / m_nChipNumX;	// 列数を算出
//
//	ans.x = m_vChipSize.x * X;	// X座標をセット
//	ans.y = m_vChipSize.y * Y;	// Y座標をセット
//
//	ans.x += m_vChipSize.x * 0.5f;	// チップの半分の長さを足してチップの中心座標にする
//	ans.y += m_vChipSize.y * 0.5f;	// チップの半分の長さを足してチップの中心座標にする
//
//	// チップの中心座標を返す
//	return ans;

	// 最適化版
	return D3DXVECTOR2(	m_vChipSize.x * (nIdxNo % m_nChipNumX) + m_vChipSize.x * 0.5f,
						m_vChipSize.y * (nIdxNo / m_nChipNumX) + m_vChipSize.y * 0.5f );	// チップの中心座標を返す
}

//****************************************************
// 説明		： 指定された座標にあるチップ番号を取得。第2,3引数に帰ってくる最小値は０
// 引数		： 任意の座標, マップチップの要素数(横)を返すポインタ, マップチップの要素数(縦)を返すポインタ
// 戻り値	： 第一引数に指定された箇所のマップチップの番号
//****************************************************
int CMapchip::GetMapchipNo(D3DXVECTOR2 Pos, int* retIdxNumX, int* retIdxNumY)
{
	int nIdxX, nIdxY;	// この関数内で使用する変数の宣言

	nIdxX = (int)(Pos.x / m_vChipSize.x);	// マップチップ座標のxを求める
	nIdxY = (int)(Pos.y / m_vChipSize.y);	// マップチップ座標のyを求める

	// マップチップ座標の X, y それぞれの値を返す
	if (retIdxNumX != NULL) *retIdxNumX = nIdxX;
	if (retIdxNumY != NULL) *retIdxNumY = nIdxY;

	return m_MapChipData[nIdxX + (nIdxY * m_nChipNumX)];	// 求めた座標値から、要素数を求めて、その数値を返す
//	return m_MapChipData[ (int)(Pos.x / m_vChipSize.x) + (int)(Pos.y / m_vChipSize.y) * m_nChipNumX ];	// 高速化

}

// マップチップテクスチャの生成
void CreateMapchipTexture(int MapchipPattarn)
{
	// テクスチャ生成
	CreateTexture(g_TextureName[MapchipPattarn], &g_Texture);
}

// マップチップテクスチャの解放
void ReleaseMapchipTexture(void)
{
	// テクスチャ解放
	ReleaseTexture(&g_Texture);
}
