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
static ID3D11ShaderResourceView	*g_Texture[UI_TEX_TYPE_MAX] = { NULL };	// テクスチャ情報

// テクスチャのファイル名
static char* g_TextureName[] = {
	"data/TEXTURE/UI/HP_gage/gage.png",			// UI_TEX_TYPE_HPgage
	"data/TEXTURE/UI/HP_gage/gage_cover.png",	// UI_TEX_TYPE_HPgage_Cover
//	"data/TEXTURE/player/player01_Back_Not_Invisible.png",	// TexNo : 1

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
	for (int i = 0; i < UI_TEX_TYPE_MAX; i++)
	{
		// 初期化処理実行
		m_Texture[i].Init();	// 一旦ゼロで初期化
	}

	//------------------- テクスチャの情報を個別でセット
	m_Texture[UI_TEX_TYPE_HPgage].SetTexPos(D3DXVECTOR2(HP_GAGE_WIDTH * 0.5f, HP_GAGE_HEIGHT * 0.5f));
	m_Texture[UI_TEX_TYPE_HPgage].SetTexSize( D3DXVECTOR2(HP_GAGE_WIDTH, HP_GAGE_HEIGHT) );
	m_Texture[UI_TEX_TYPE_HPgage].SetTexColor( HP_GAGE_COLOR );

	D3DXVECTOR2 Pos = m_Texture[UI_TEX_TYPE_HPgage].GetTexPos();
	Pos.x *= 0.5f;
		m_Texture[UI_TEX_TYPE_HPgage_Cover].SetTexPos(Pos);
	m_Texture[UI_TEX_TYPE_HPgage_Cover].SetTexSize( D3DXVECTOR2(HP_GAGE_COVER_WIDTH, HP_GAGE_COVER_HEIGHT) );

}



//=============================================================================
// 終了処理
//=============================================================================
void CGameUI::Uninit()
{
	// テクスチャ解放
	ReleaseGameUITexture();

	// テクスチャクラスの終了処理
	for (int i = 0; i < UI_TEX_TYPE_MAX; i++)
	{
		m_Texture[i].Uninit();	// 終了処理実行
	}
}


//=============================================================================
// 更新処理
//=============================================================================
void CGameUI::Update()
{

	// プレイヤーのHPの比率を計算し、ゲージの長さを設定
	{
		CPlayer PlayerInf;
		D3DXVECTOR2 GageSize;	// 現在のゲージのサイズ
		float rate;				// 比率

		PlayerInf = *GetGame()->GetPlayer();	// プレイヤーの情報を取得
		rate = PlayerInf.GetCurrentHP() / PlayerInf.GetHP();	// プレイヤーのHPの比率を取得

		GageSize = m_Texture[UI_TEX_TYPE_HPgage].GetTexSize();	// 現在のゲージの大きさを取得
		GageSize.x = HP_GAGE_WIDTH * rate;		// ゲージの幅を、比率をかけた値にセット

		// 最終的なゲージの大きさをセット
		m_Texture[UI_TEX_TYPE_HPgage].SetTexSize(GageSize);	// セット
	}



}



//=============================================================================
// 描画処理
//=============================================================================
void CGameUI::Draw()
{
	// 全てのテクスチャを描画
	for (int i = 0; i < UI_TEX_TYPE_MAX; i++)
	{
		m_Texture[i].DrawTexture(g_Texture[i]);	// 描画処理実行
	}
}



// テクスチャの生成
void CreateGameUITexture(void)
{
	// 全てのテクスチャ情報を生成
	for (int i = 0; i < UI_TEX_TYPE_MAX; i++)
	{
		CreateTexture(g_TextureName[i], &g_Texture[i]);	// テクスチャ生成
	}
}

// テクスチャの解放
void ReleaseGameUITexture(void)
{
	// 全てのテクスチャ情報を生成
	for (int i = 0; i < UI_TEX_TYPE_MAX; i++)
	{
		ReleaseTexture(&g_Texture[i]);	// テクスチャ解放
	}
}