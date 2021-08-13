//=============================================================================
//
// UI処理 [userInterface.cpp]
// Author : 杉本幸宏
//
//=============================================================================

#include "main.h"
#include "userInterface.h"

#include "game.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
#define CASE_DRAW_TOPLEFT	case GAMEUI_TEX_TYPE_HPgage: case GAMEUI_TEX_TYPE_HPgage_Cover:		// 左上原点で描画するテクスチャの種類

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11ShaderResourceView	*g_Texture[GAMEUI_TEX_TYPE_MAX] = { NULL };	// テクスチャ情報

// テクスチャのファイル名
static char* g_TextureName[] = {
	"data/TEXTURE/UI/HP_gage/gage.png",			// GAMEUI_TEX_TYPE_HPgage
	"data/TEXTURE/UI/HP_gage/gage_cover.png",	// GAMEUI_TEX_TYPE_HPgage_Cover
};

//=============================================================================
// コンストラクタ・デストラクタ
//=============================================================================
CGameUI::CGameUI()	// コンストラクタ
{

}

CGameUI::~CGameUI()	// デストラクタ
{

}



//=============================================================================
// 初期化処理
//=============================================================================
void CGameUI::Init()
{
	// テクスチャ生成
	CreateGameUITexture();

	// テクスチャクラスの初期化処理
	for (int i = 0; i < GAMEUI_TEX_TYPE_MAX; i++)
	{
		// 初期化処理実行
		m_GameTexture[i].Init();	// 一旦ゼロで初期化
	}

	//------------------- テクスチャの情報を個別でセット
	m_GameTexture[GAMEUI_TEX_TYPE_HPgage].SetTexPos( HP_GAGE_POS_TOPLEFT );	// 描画位置をセット（左上）
	m_GameTexture[GAMEUI_TEX_TYPE_HPgage].SetTexSize( HP_GAGE_SIZE );		// サイズをセット
	m_GameTexture[GAMEUI_TEX_TYPE_HPgage].SetTexColor( HP_GAGE_COLOR );		// 色をセット

	m_GameTexture[GAMEUI_TEX_TYPE_HPgage_Cover].SetTexPos( HP_GAGE_POS_TOPLEFT );	// 描画位置をセット（左上）
	m_GameTexture[GAMEUI_TEX_TYPE_HPgage_Cover].SetTexSize( HP_GAGE_SIZE );			// サイズをセット
}



//=============================================================================
// 終了処理
//=============================================================================
void CGameUI::Uninit()
{
	// テクスチャ解放
	ReleaseGameUITexture();

	// テクスチャクラスの終了処理
	for (int i = 0; i < GAMEUI_TEX_TYPE_MAX; i++)
	{
		m_GameTexture[i].Uninit();	// 終了処理実行
	}
}


//=============================================================================
// 更新処理
//=============================================================================
void CGameUI::Update()
{

	// プレイヤーのHPの比率を計算し、描画するゲージの幅をセット
	{
		CPlayer PlayerInf;		// 現在のプレイヤーの情報を保存するインスタンス
		D3DXVECTOR2 GageSize;	// 現在のゲージのサイズ
		float rate;				// 比率

		PlayerInf = *GetGame()->GetPlayer();					// プレイヤーの情報を取得
		rate = PlayerInf.GetCurrentHP() / PlayerInf.GetHP();	// プレイヤーのHPの比率を取得

		GageSize = m_GameTexture[GAMEUI_TEX_TYPE_HPgage].GetTexSize();	// 現在のゲージの大きさを取得
		GageSize.x = HP_GAGE_WIDTH * rate;						// ゲージの幅を、比率をかけた値にセット

		// 最終的なゲージの大きさをセット
		m_GameTexture[GAMEUI_TEX_TYPE_HPgage].SetTexSize(GageSize);	// セット
	}



}



//=============================================================================
// 描画処理
//=============================================================================
void CGameUI::Draw()
{
	// 全てのテクスチャを描画
	for (int i = 0; i < GAMEUI_TEX_TYPE_MAX; i++)	// ゲーム画面
	{
		// 左上と中心のどちらを原点で描画するかによって処理を変える
		if (i <= GAMEUI_TEX_DRAW_TOPLEFT_MAXNO)	m_GameTexture[i].DrawTextureTopLeft(g_Texture[i]);	// 描画処理実行（左上原点）
		else m_GameTexture[i].DrawTexture(g_Texture[i]);	// 描画処理実行（中心原点）
	}
}



// テクスチャの生成
void CreateGameUITexture(void)
{
	// 全てのテクスチャ情報を生成
	for (int i = 0; i < GAMEUI_TEX_TYPE_MAX; i++)
	{
		CreateTexture(g_TextureName[i], &g_Texture[i]);	// テクスチャ生成
	}
}

// テクスチャの解放
void ReleaseGameUITexture(void)
{
	// 全てのテクスチャ情報を生成
	for (int i = 0; i < GAMEUI_TEX_TYPE_MAX; i++)
	{
		ReleaseTexture(&g_Texture[i]);	// テクスチャ解放
	}
}