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

#include "debugproc.h"	// デバッグ表示

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NEXT_MODE				MODE_RESULT		// 次のモード

// マップチップのファイル名
#define GAME_MAP_DATA			"data/MAPCHIP/mapdata32×64.csv"		// マップ情報のファイル名

// クラス管理
#ifdef GAMEMODE_CLASS

//=============================================================================
// 初期化処理
//=============================================================================
void CModeGame::Init()
{
#ifdef _DEBUG
	// ポーズフラグの初期化
	m_bPauseFlag = false;	// "false"（ボーズ無効）で初期化
#endif // _DEBUG

	//	g_ViewPortType_Game = TYPE_FULL_SCREEN;	// ビューポート設定

	// スクロール座標の初期化
	SetScrollPosition(ZERO_VECTOR2);

	// 重力方向の初期化
	m_GravityDirection = GRAVITY_DEFAULT;

	// 重力変更エンジンに触れていません
	m_bIsTouchGrvityChange = false;

	// 背景の初期化
	InitBg();

	// プレイヤーの初期化
	CreatePlayerTextureAndBuffer();	// テクスチャ・頂点バッファ生成
	for(int i =0; i < PLAYER_MAX; i++)
	{
		m_Player[i].Init();	// 初期化処理
	}

	// マップチップの初期化
	CreateMapchipTextureAndBuffer(MAPCHIP_STAGE_Sample);	// テクスチャ・頂点バッファ生成
	m_Mapchip.Init(GAME_MAP_DATA);	// ステージ情報をロード

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
void CModeGame::Uninit(void)
{
	// パーティクルの終了処理
//	UninitParticle();

	// スコアの終了処理
//	UninitScore();

	// 弾の終了処理
//	UninitBullet();

	// マップチップの終了処理
	ReleaseMapchipTextureAndBuffer();	// テクスチャ・頂点バッファ解放

	// エネミーの終了処理
	UninitEnemy();

	// プレイヤーの終了処理
	ReleasePlayerTextureAndBuffer();	// テクスチャ・頂点バッファ解放
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
void CModeGame::Update(void)
{
#ifdef _DEBUG
	// ポーズキーが押されたらフラグを操作する
	if( KEY_PAUSE ) m_bPauseFlag ? false : true;
					// m_bPauseFlagは？  "true"なら"false" に  :  "false"なら"true" に  セットする

	// ポーズフラグがtrueなら処理を行わない。
	if (m_bPauseFlag) return;

	// リスタートのキーが押されたとき
	if (KEY_RESTART_GAMEMODE)
	{
		CModeGame::Uninit();	// ゲームモードの解放
		CModeGame::Init();		// ゲームモードの初期化
	}

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
#endif // _DEBUG


	// 重力方向の変更
	if (KEY_CHANGE_GRAVITY)
	{
		m_GravityDirection = (m_GravityDirection + 1) % GRAVITY_DIRECTION_MAX;
		SetGravityDirection(m_GravityDirection);
	}


	// マップチップの更新処理
	m_Mapchip.Update();

	// プレイヤーの更新処理
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		m_Player[i].Update();
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

#ifdef _DEBUG
	PrintDebugProc("\nスクロール座標 X: %f  Y: %f\n", GetScrollPosition().x, GetScrollPosition().y);

	PrintDebugProc("　　重力の方向:%d ", GetGravityDirection());

	//char *str = GetDebugStr();
	//sprintf(&str[strlen(str)], "　　重力の方向:%d ", GetGravityDirection());
#endif // _DEBUG
}

//=============================================================================
// 描画処理
//=============================================================================
void CModeGame::Draw()
{
	// 背景の描画処理
	DrawBg();

	// マップチップの描画
	m_Mapchip.Draw();

	// テスト画像表示
//	DrawPolygon();

	// エネミーの描画処理
//	DrawEnemy();

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
void CModeGame::CollisionCheck()
{
	// プレイヤーとマップチップの当たり判定
	{
	//	int Num = m_Mapchip.GetMapchipNo(m_Player->GetPlayerPos());	// プレイヤー座標のマップチップを取得

		// プレイヤー座標のマップチップを取得して、その値によって処理を変える
	//	switch (Num)
		switch ( m_Mapchip.GetMapchipNo(m_Player->GetPlayerPos()) )	// プレイヤー座標のマップチップを取得
		{
		// 重力変更エンジンに触れたとき
		case 10:
			// 重力方向の変更
			if (!m_bIsTouchGrvityChange)	// 重力装置に触れていないという数値の時
			{
				/*これ関数化できるな*/
				m_GravityDirection = (m_GravityDirection + 1) % GRAVITY_DIRECTION_MAX;
				SetGravityDirection(m_GravityDirection);
				m_bIsTouchGrvityChange = true;	// 重力装置に触れていますよ
			}
			break;

			// 重力装置に触れていません
			m_bIsTouchGrvityChange = false;	// フラグを"false"にセット

		default:
			break;
		}

	}

}

//****************************************************
// 説明		： マップチップとの当たり判定をとり、座標の調整も行う
// 引数		： マップチップ情報, 現在の座標, 移動前の座標, 座標調整を行うかどうかのフラグ
// 戻り値	： 【当たり】当たったチップの番号　　【外れ】「-1」
//****************************************************
//int HitCheckMapchip(CMapchip Mapchip, D3DXVECTOR2* CurrentPos, D3DXVECTOR2 OldPos, D3DXVECTOR2 HalfObjectSize)
int HitCheckMapchip(CMapchip Mapchip, D3DXVECTOR2* CurrentPos, D3DXVECTOR2 OldPos, bool Flag)
{
	int nCurX, nCurY, nCurNo;
	int nOldX, nOldY, nOldNo;

	// 現在の座標のチップ番号と、マップチップ座標系での位置を求める
	nCurNo = Mapchip.GetMapchipNo(*CurrentPos, &nCurX, &nCurY);	// 移動後の情報
	nOldNo = Mapchip.GetMapchipNo(OldPos, &nOldX, &nOldY);		// 移動前の情報

	// チップと当たっているか判定
	// 移動後の座標にあるマップチップ番号が、当たり判定属性を持っていた時 → 当たっている
	if (MAPCHIP_HIT_min <= nCurNo && nCurNo <= MAPCHIP_HIT_MAX)	// 移動後の座標にあるマップチップ番号が、「MAPCHIP_HIT_min」と「MAPCHIP_HIT_MAX」の間のとき
	{	// マップチップと当たっている時の処理
		//========= 1.座標を調整
		if(Flag)	// 座標調整を行うフラグが立っていたら、座標調整を行う
		{
			// x軸
			if ( (nCurX - nOldX) != 0)
			{
				// まずは、チップ と 移動前座標(プレイヤー) の位置関係を調べる
				int isLeft = (nOldX < nCurX);	// 移動前座標が左側にあるときは「1」になる
	
				if (isLeft)
				{	// 移動前座標が左側の時
				//	CurrentPos->x = (Mapchip.GetMapchipSize().x * nCurX) - HalfObjectSize.x;
					CurrentPos->x = (Mapchip.GetMapchipSize().x * nCurX);			// 座標調整（押し出し処理）

					/* 上の命令だけだと、次ループ時に、isLeft=0判定となり、すりぬけちゃう */
					CurrentPos->x -= 1.0f;		// ↑これ対策の、やりたくないけど応急処置
				}
				else
				{
				//	CurrentPos->x = (Mapchip.GetMapchipSize().x * (nCurX + 1)) + HalfObjectSize.x;
					CurrentPos->x = (Mapchip.GetMapchipSize().x * (nCurX + 1) );	// 座標調整（押し出し処理）
				}
			}

			// y軸
			if ( (nCurY - nOldY) != 0)
			{
				// まずは、チップ と 移動前座標(プレイヤー) の位置関係を調べる
				int isTop = (nOldY < nCurY);	// 移動前座標が上側にあるときは「1」になる

				if (isTop)
				{	// 移動前座標が左側の時
				//	CurrentPos->y = (Mapchip.GetMapchipSize().y * nCurY) - HalfObjectSize.y;
					CurrentPos->y = (Mapchip.GetMapchipSize().y * nCurY);		// 座標調整（押し出し処理）

					/* 上の命令だけだと、次ループ時に、isTop =0 判定となり、すりぬけちゃう */
					CurrentPos->y -= 0.5f;		// ↑これ対策の、やりたくないけど応急処置
				}
				else
				{
				//	CurrentPos->y = (Mapchip.GetMapchipSize().y * (nCurY + 1)) + HalfObjectSize.y;
					CurrentPos->y = (Mapchip.GetMapchipSize().y * (nCurY + 1));	// 座標調整（押し出し処理）
				}
			}
		}

		//========= 2.当たったチップの番号を返す
		return nCurNo;
	}

	// 当たっていない時　→ 「-1」を返す
	return (-1);
}



//=============================================================================
// ゲッター関数
//=============================================================================
// スクロール座標のセット
D3DXVECTOR2 CModeGame::GetScrollPosition()
{
	return m_vScrollPos;
}

// マップチップへのアクセス
CMapchip* CModeGame::GetMapchip()
{
	return &m_Mapchip;	// マップチップの情報を返す
}

// 重力方向の取得
int CModeGame::GetGravityDirection()
{
	return m_GravityDirection;
}

//=============================================================================
// セッター関数
//=============================================================================
// スクロール座標の取得
void CModeGame::SetScrollPosition(D3DXVECTOR2 Pos)
{
	m_vScrollPos = Pos;
}

// ゲーム全体の重力の方向をセット
void CModeGame::SetGravityDirection(int Direction)
{
	// 重力処理クラスを継承している全てのオブジェクトの、重力方向の向きを変更
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (!m_Player->GetPlayerUseFlag()) return;	// プレイヤーが未使用なら行わない
		m_Player[i].SetGravityObjectDirection(Direction);	// プレイヤーの重力方向をセット
	}
	
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
