//=============================================================================
//
// ゲーム画面処理 [game.cpp]
// Author : 杉本幸宏
//
//=============================================================================
#include "main.h"
#include "renderer.h"	// レンダリング処理
#include "game.h"

#include "bg.h"			// 背景
//#include "bullet.h"	// バレット
#include "camera.h"		// カメラ処理
#include "collision.h"	// 衝突判定
#include "enemy.h"		// エネミー
#include "fade.h"		// フェード
#include "input.h"		// キー・ゲームパッド入力処理
//#include "particle.h"	// パーティクル

//#include "score.h"	// スコア
#include "sound.h"		// サウンド

//#include "debugproc.h"	// デバッグ表示

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NEXT_MODE					MODE_RESULT		// 次のモード
#define KEY_MODE_CHANGE				GetKeyboardTrigger(DIK_RETURN)
#define PAD_MODE_CHANGE				IsButtonTriggered(0, BUTTON_START) || IsButtonTriggered(0, BUTTON_B)


// クラス管理
#ifdef GAMEMODE_CLASS
//=============================================================================
// 初期化処理
//=============================================================================
void CGameMode::Init()
{
	//	g_ViewPortType_Game = TYPE_FULL_SCREEN;	// ビューポート設定

#ifdef _DEBUG
	// ポーズフラグの初期化
	SetPauseFlag(false);
#endif // _DEBUG

	// スクロール座標の初期化
	SetScrollPosition(ZERO_VECTOR2);

	// 背景の初期化処理
	InitBg();

	// プレイヤーの初期化
	CreatePlayerTextureAndBuffer();
	for(int i =0; i < PLAYER_MAX; i++)
	{
		(m_Player + i)->Init();
	}

	// エネミーの初期化
	InitEnemy();

	// 弾の初期化
//	InitBullet();

	// スコアの初期化
//	InitScore();

	// パーティクルの初期化
//	InitParticle();

	// BGM再生
//	PlaySound(SOUND_LABEL_BGM_sample001);
}

//=============================================================================
// 終了処理
//=============================================================================
void CGameMode::Uninit(void)
{
	// パーティクルの終了処理
//	UninitParticle();

	// スコアの終了処理
//	UninitScore();

	// 弾の終了処理
//	UninitBullet();

	// エネミーの終了処理
	UninitEnemy();

	// プレイヤーの終了処理
	ReleasePlayerTextureAndBuffer();
//	for (int i = 0; i < PLAYER_MAX; i++)
//	{
//		(m_Player + i)->Uninit();
//	}

	// 背景の終了処理
	UninitBg();

}

//=============================================================================
// 更新処理
//=============================================================================
void CGameMode::Update(void)
{
	//------------------- キー・ゲームパットでの入力で次のモードへ
	if (KEY_MODE_CHANGE)
	{// Enter押したら、ステージを切り替える
		SetFade(FADE_OUT, NEXT_MODE);	// フェードして次のモードへ
	//	SetMode(NEXT_MODE);				// 次のモードにシーン遷移
	}
	// ゲームパッドで入力処理
	else if (PAD_MODE_CHANGE)
	{
		SetFade(FADE_OUT, NEXT_MODE);	// フェードして次のモードへ
	//	SetMode(NEXT_MODE);				// 次のモードにシーン遷移
	}

#ifdef _DEBUG
	// ポーズフラグがtrueなら処理を行わない。
	if ( GetPauseFlag() ) return;
#endif // _DEBUG

	// プレイヤーの更新処理
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		(m_Player + i)->Update();
	}

	// エネミーの更新処理
	UpdateEnemy();

	// 弾の更新処理
//	UpdateBullet();

	// パーティクルの更新処理
//	UpdateParticle();

	// 当たり判定処理
	CollisionCheck();

	// スコアの更新処理
//	UpdateScore();

	// 背景の更新処理
	UpdateBg();
}

//=============================================================================
// 描画処理
//=============================================================================
void CGameMode::Draw()
{
	// 背景の描画処理
	DrawBg();

	// テスト画像表示
//	DrawPolygon();

	// エネミーの描画処理
	DrawEnemy();

	// プレイヤーの描画処理
	for(int i = 0; i < PLAYER_MAX; i++)
	{
		(m_Player + i)->Draw();
	}


	// 弾の描画処理
//	DrawBullet();

	// パーティクルの描画処理
//	DrawParticle();

	// スコアの描画処理
//	DrawScore();
}



//=============================================================================
// 当たり判定処理
//=============================================================================
void CGameMode::CollisionCheck()
{

}



//=============================================================================
// ゲッター関数
//=============================================================================
// スクロール座標の取得
void CGameMode::SetScrollPosition(D3DXVECTOR2 Pos)
{
	m_vScrollPos = Pos;
}

#ifdef _DEBUG
// ポーズフラグの取得
bool CGameMode::GetPauseFlag()
{
	return m_bPauseFlag;
}
#endif // _DEBUG



//=============================================================================
// セッター関数
//=============================================================================
// スクロール座標のセット
D3DXVECTOR2 CGameMode::GetScrollPosition()
{
	return m_vScrollPos;
}

// ポーズフラグのセット
void CGameMode::SetPauseFlag(bool Flag)
{
	m_bPauseFlag = Flag;
}

#endif // GAMEMODE_CLASS





// 構造体管理
#ifdef GAMEMODE_STRUCT
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void CheckHit(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
//static int	g_ViewPortType_Game = TYPE_FULL_SCREEN;

static bool	g_bPauseFlag = false;				// ポーズON/OFF
static D3DXVECTOR2 g_vScrollPos = ZERO_VECTOR2;	// スクロール座標

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGame(void)
{
//	g_ViewPortType_Game = TYPE_FULL_SCREEN;

	// スクロール座標の初期化
	g_vScrollPos = ZERO_VECTOR2;

	// 背景の初期化処理
	InitBg();

	// プレイヤーの初期化
	InitPlayer();

	// エネミーの初期化
	InitEnemy();

	// 弾の初期化
//	InitBullet();

	// スコアの初期化
//	InitScore();

	// パーティクルの初期化
//	InitParticle();

	// BGM再生
//	PlaySound(SOUND_LABEL_BGM_sample001);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGame(void)
{
	// パーティクルの終了処理
//	UninitParticle();

	// スコアの終了処理
//	UninitScore();

	// 弾の終了処理
//	UninitBullet();

	// エネミーの終了処理
	UninitEnemy();

	// プレイヤーの終了処理
	UninitPlayer();

	// 背景の終了処理
	UninitBg();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame(void)
{
	//------------------- キー・ゲームパットでの入力で次のモードへ
	if (KEY_MODE_CHANGE)
	{// Enter押したら、ステージを切り替える
		SetFade(FADE_OUT, NEXT_MODE);	// フェードして次のモードへ
	//	SetMode(NEXT_MODE);				// 次のモードにシーン遷移
	}
	// ゲームパッドで入力処理
	else if (PAD_MODE_CHANGE)
	{
		SetFade(FADE_OUT, NEXT_MODE);	// フェードして次のモードへ
	//	SetMode(NEXT_MODE);				// 次のモードにシーン遷移
	}

	// ポーズフラグがtrueなら処理を行わない。
	if(g_bPauseFlag == true) return;

	// プレイヤーの更新処理
	UpdatePlayer();

	// エネミーの更新処理
	UpdateEnemy();

	// 弾の更新処理
//	UpdateBullet();

	// パーティクルの更新処理
//	UpdateParticle();

	// 当たり判定処理
	CheckHit();

	// スコアの更新処理
//	UpdateScore();

	// 背景の更新処理
	UpdateBg();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGame(void)
{
	// 背景の描画処理
	DrawBg();

	// テスト画像表示
//	DrawPolygon();

	// エネミーの描画処理
	DrawEnemy();

	// プレイヤーの描画処理
	DrawPlayer();

	// 弾の描画処理
//	DrawBullet();

	// パーティクルの描画処理
//	DrawParticle();

	// スコアの描画処理
//	DrawScore();
}

//=============================================================================
// 当たり判定処理
//=============================================================================
void CheckHit(void)
{
	//ENEMY *enemy = GetEnemy();		// エネミーのポインターを初期化
	//PLAYER *player = GetPlayer();	// プレイヤーのポインターを初期化
	//BULLET *bullet = GetBullet();	// 弾のポインターを初期化

	// 敵とプレイヤーキャラ
	//for (int i = 0; i < MAX_ENEMY; i++)
	//{
	//	//敵の有効フラグをチェックする
	//	if (enemy[i].use == false)
	//		continue;

	//	//BCの当たり判定
	//	if (CollisionBC(GetPlayer()->pos, enemy[i].pos,
	//		player->rsize, enemy[i].rsize))
	//	{
	//		// 敵キャラクターは倒される
	//		enemy[i].use = false;
	//		ReleaseShadow(enemy[i].shadowIdx);
	//	}
	//}

	// プレイヤーの弾と敵
	//for (int i = 0; i < MAX_BULLET; i++)
	//{
	//	//弾の有効フラグをチェックする
	//	if (bullet[i].use == false)
	//		continue;

	//	// 敵と当たってるか調べる
	//	for (int j = 0; j < MAX_ENEMY; j++)
	//	{
	//		//敵の有効フラグをチェックする
	//		if (enemy[j].use == false)
	//			continue;

	//		//BCの当たり判定
	//		if (CollisionBC(bullet[i].pos, enemy[j].pos,
	//			bullet[i].fWidth, enemy[j].rsize))
	//		{
	//			// 当たったから未使用に戻す
	//			bullet[i].use = false;
	//			ReleaseShadow(bullet[i].shadowIdx);

	//			// 敵キャラクターは倒される
	//			enemy[j].use = false;
	//			ReleaseShadow(enemy[j].shadowIdx);

	//			// スコアを足す
	//			AddScore(10);
	//		}
	//	}

	//}


	// エネミーが全部死亡したら状態遷移
	//int enemy_count = 0;
	//for (int i = 0; i < MAX_ENEMY; i++)
	//{
	//	if (enemy[i].use == false) continue;
	//	enemy_count++;
	//}

	// エネミーが０匹？
	//if (enemy_count == 0)
	//{
	//	SetFade(FADE_OUT, MODE_RESULT);
	//}

}



//=============================================================================
// ゲッター関数
//=============================================================================
// スクロール座標の取得
void SetScrollPosition(D3DXVECTOR2 Pos)
{
	g_vScrollPos = Pos;
}



//=============================================================================
// セッター関数
//=============================================================================
// スクロール座標のセット
D3DXVECTOR2* GetScrollPosition()
{
	return &g_vScrollPos;
}

#endif // GAMEMODE_STRUCT
