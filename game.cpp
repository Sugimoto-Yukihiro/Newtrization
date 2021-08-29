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
//#include "camera.h"		// カメラ処理
#include "collision.h"	// 衝突判定
#include "fade.h"		// フェード
#include "input.h"		// キー・ゲームパッド入力処理
#include "sound.h"		// サウンド

#include "debugproc.h"	// デバッグ表示

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NEXT_MODE		MODE_RESULT		// 次のモード

//*****************************************************************************
// グローバル変数
//*****************************************************************************



//=============================================================================
// 初期化処理
//=============================================================================
void CModeGame::Init()
{
	//------------------- メンバ変数の初期化
	m_vScrollPos = ZERO_VECTOR2;			// スクロール座標の初期化
	m_GravityDirection = GRAVITY_DEFAULT;	// 重力方向の初期化
	m_bIsTouchGrvityChange = false;			// "false"（エンジンに触れていない）で初期化
	m_nFlameCnt = 0;						// 経過フレーム数を初期化
#ifdef _DEBUG
	// ポーズフラグの初期化
	m_bPauseFlag = false;		// "false"（ボーズ無効）で初期化
	m_bMapchipDebug = false;	// "false"（マップチップのデバッグ表示無効）で初期化
#endif // _DEBUG

	//------------------- 以降、ゲームモードクラス内のインスタンスの初期化
	// 背景の初期化
	InitBg();

	// UIの初期化
	m_GameUI.Init();

	// プレイヤーの初期化
	CreatePlayerTexture();	// テクスチャ・頂点バッファ生成
	m_Player.Init(FIREBOOTS_BULLET_TEXNAME);	// 初期化処理実行

	// マップチップの初期化
	m_Mapchip.Init(TEXTURE_NAME_MAPCHIP, NULL, MAPCHIP_TEXTURE_DIVIDE_X, MAPCHIP_TEXTURE_DIVIDE_Y, MAPCHIP_SIZE_DEFAULT);		// 初期化処理実行
#ifdef _DEBUG
	// デバッグ表示用マップチップの初期化
	m_DebugMapchip.Init(TEXTURE_NAME_MAPCHIP_DEBUG, NULL, MAPCHIP_DEBUG_TEXTURE_DIVIDE_X, MAPCHIP_DEBUG_TEXTURE_DIVIDE_Y, MAPCHIP_SIZE_DEFAULT);		// 初期化処理実行
#endif // _DEBUG

	// エネミーの初期化
	InitEnemy();	// テクスチャ生成
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		m_Enemy[i].Init();		// エネミーの数だけ呼び出すマン
	}

	// 弾の初期化
//	InitBullet();

	// スコアの初期化
	m_Score.Init(SCORE_TEX_NAME, SCORE_DRAW_SIZE);

	// 画面端の初期化
	m_SideBlack.Init(TEXTURE_NAME_SIDEBLACK);

	// 浮力加速の初期化
	for (int i = 0; i < FURYOKU_MAX; i++)
	{
		// 初期化
		m_FloatForceArea[i].Init(FURYOKU_TEX_NAME);
	}

	// オブジェクトの配置 & マップチップのセット
	PutAllObject(GAME_MAP_DATA_1);



	//------------------- プレイヤーの位置が決まったから、スクロール座標をセット
	{
		D3DXVECTOR2 pos = ZERO_VECTOR2;	// 一時的な変数
		pos.x = m_Player.GetPosition().x - SCROLL_SET_X;	// スクロール座標<x>に値を代入
		pos.x = (pos.x < 0.0f) ? 0.0f : pos.x;	// スクロール座標<x>が負なら「0」にリセット、正の数ならそのまま
		pos.x = (pos.x + SCREEN_WIDTH > m_Mapchip.GetMapChipSize().x) ? m_Mapchip.GetMapChipSize().x - SCREEN_WIDTH : pos.x;	// 画面右上の点がワールドの端に来たら"STAGE_W"の値にリセット

		pos.y = m_Player.GetPosition().y - SCROLL_SET_Y;	// スクロール座標<y>に値を代入
		pos.y = (pos.y < 0.0f) ? 0.0f : pos.y;	// スクロール座標<y>負なら「0」にリセット、正の数ならそのまま
		pos.y = (pos.y + SCREEN_HEIGHT > m_Mapchip.GetMapChipSize().y) ? m_Mapchip.GetMapChipSize().y - SCREEN_HEIGHT : pos.y;	// 画面右上の点がワールドの端に来たら"STAGE_H"の値にリセット

		// 座標をセット
		m_vScrollPos = pos;
	}

	// BGM再生
//	PlaySound(SOUND_LABEL_BGM_sample001);
}



//=============================================================================
// 終了処理
//=============================================================================
void CModeGame::Uninit(void)
{
	// BGM停止
//	StopSound();

	// 浮力加速エリアの終了処理
	for (int i = 0; i < FURYOKU_MAX; i++)
	{
		m_FloatForceArea[i].Uninit();	// 終了
	}

	// 画面端の終了処理
	m_SideBlack.Uninit();

	// スコアの終了処理
	m_Score.Uninit();

	// 弾の終了処理
//	UninitBullet();

#ifdef _DEBUG
	// デバッグ表示用マップチップの終了処理
	m_DebugMapchip.Uninit();
#endif // _DEBUG

	// マップチップの終了処理
	m_Mapchip.Uninit();		// 終了処理実行

	// エネミーの終了処理
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		m_Enemy[i].Uninit();		// エネミーの数だけ呼び出すマン
	}
	UninitEnemy();

	// プレイヤーの終了処理
	ReleasePlayerTexture();	// テクスチャ解放
	m_Player.Uninit();		// 終了処理実行

	// UIの終了処理
	m_GameUI.Uninit();

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
	if( KEY_PAUSE ) m_bPauseFlag = (m_bPauseFlag) ? false : true;
								//  m_bPauseFlagは？  "true"なら"false" に  :  "false"なら"true" に  セットする
	// ポーズフラグがtrueなら処理を行わない。
	if (m_bPauseFlag) return;

	// マップチップのデバッグ表示キーが押されたとき
	if (KEY_MAPCHIP_DEBUG) m_bMapchipDebug = (m_bMapchipDebug) ? false : true;

	// リスタートのキーが押されたとき
	if (KEY_RESTART_GAMEMODE)
	{
		CModeGame::Uninit();	// ゲームモードの解放
		CModeGame::Init();		// ゲームモードの初期化
	}
	// 重力方向の変更
	if (KEY_CHANGE_GRAVITY)
	{
		m_GravityDirection = (m_GravityDirection + 1) % GRAVITY_DIRECTION_MAX;
		ChangeGravityDirection(m_GravityDirection);
	}
#endif // _DEBUG

#ifdef KEY_MODE_CHANGE
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
#endif // KEY_MODE_CHANGE

	// 経過フレーム数をカウント
	m_nFlameCnt++;

	// マップチップの更新処理
	m_Mapchip.Update();

#ifdef _DEBUG
	// デバッグ表示用マップチップの更新処理
	if (m_bMapchipDebug) m_DebugMapchip.Update();
#endif // _DEBUG


	// プレイヤーの更新処理
	m_Player.Update();	// プレイヤーの更新処理実行

	// エネミーの更新処理
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		m_Enemy[i].Update(m_Mapchip);		// エネミーの数だけ呼び出すマン
	}

	// 画面端の更新処理
	m_SideBlack.Update();

	// 浮力加速の更新処理
	for (int i = 0; i < FURYOKU_MAX; i++)
	{
		m_FloatForceArea[i].Update();
	}

	//-------------------  当たり判定処理
	CollisionCheck();

	/* 当たり判定の結果によって内容が変わる更新処理はこれ以降に記載する！ */

	// スコアの更新処理
	m_Score.Update(m_nFlameCnt);

	// 背景の更新処理
	UpdateBg();

	// UIの更新処理
	m_GameUI.Update();

	// プレイヤーのHPが0以下になったら終了
	if (m_Player.GetCurrentHP() < 0.0f) SetFade(FADE_OUT, NEXT_MODE);

}



//=============================================================================
// 描画処理
//=============================================================================
void CModeGame::Draw()
{
	// 描画前の準備処理実行
	PresetDraw2D();

	// 背景の描画処理
	DrawBg();

	// 浮力加速エリアの描画処理
	for (int i = 0; i < FURYOKU_MAX; i++)
	{
		m_FloatForceArea[i].Draw(m_vScrollPos);
	}

	// マップチップの描画処理
	m_Mapchip.Draw(m_vScrollPos);

#ifdef _DEBUG
	// デバッグ表示用マップチップ描画処理
	if (m_bMapchipDebug) m_DebugMapchip.Draw(m_vScrollPos);
#endif // _DEBUG

	// エネミーの描画処理
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		m_Enemy[i].Draw(m_vScrollPos);		// エネミーの数だけ呼び出すマン
	}


	// プレイヤーの描画処理
	m_Player.Draw(m_vScrollPos);

	// スコアの描画処理
//	DrawScore();

	// 画面端の描画
	m_SideBlack.Draw();	// UIの前に描画する

	// UIの描画処理
	m_GameUI.Draw();

	// スコアの描画
	m_Score.Draw(SCORE_DRAW_POS_RIGHT);
}



//=============================================================================
// 当たり判定処理
//=============================================================================
void CModeGame::CollisionCheck()
{
	// プレイヤーとマップチップの当たり判定
	{
		// プレイヤー座標のマップチップ番号を取得
		int nChip_Id = m_Mapchip.GetMapchipNo(m_Player.GetLegPos());

		// その番号によって処理を変える
		if (MAPCHIP_POISON_min <= nChip_Id && nChip_Id <= MAPCHIP_POISON_MAX)
		{	// 【毒判定のマップチップ番号に当たっていた時】
			m_Player.SetPoisonFlag(true);	// 毒状態をtrueにする
		}
		else if (MAPCHIP_CANGE_GRAVITY_min <= nChip_Id && nChip_Id <= MAPCHIP_CANGE_GRAVITY_MAX)
		{	// 【重力変更判定】
			// 重力方向の変更
			if (!m_bIsTouchGrvityChange)	// 初めて重力装置に触れた時の一回だけ行う
			{
				m_GravityDirection = (m_GravityDirection + 1) % GRAVITY_DIRECTION_MAX;	// 重力の方向を変更
				ChangeGravityDirection(m_GravityDirection);	// 重力方向セット

				m_bIsTouchGrvityChange = true;	// 重力装置に触れていますよ
			}

		}
		else if (MAPCHIP_GOAL_min <= nChip_Id && nChip_Id <= MAPCHIP_GOAL_MAX)
		{	// 【ゴール判定】
			RequestGameClear(m_Score.GetScore());	// ゲームクリア
		}
		else
		{	// 【なにも当たっていない時】
			m_bIsTouchGrvityChange = false;	// フラグを"false"にセット
			m_Player.SetPoisonFlag(false);	// 毒状態をfalseにする
		}

	}

	// プレイヤーと浮力加速エリアの当たり判定
	{
		bool Hit = false;
		for (int i = 0; i < FURYOKU_MAX, !Hit; i++)
		{
			// 未使用なら行わない
			if (!m_FloatForceArea[i].GetUseFlag()) return;

			// プレイヤーの現在の座標を取得
			D3DXVECTOR2 PlayerPos = m_Player.GetPosition();

			// 当たり判定実行
			if (m_FloatForceArea[i].HitCheck(&PlayerPos, m_Player.GetSize() * 0.5f))
			{	// 当たっていた時
				// 重力処理フラグを折る
				m_Player.SetGravityFlag(false);
				m_Player.SetBouyant(m_FloatForceArea[i].GetForceValue() * m_FloatForceArea[i].GetDirection());	// 浮力をセット
				Hit = true;	// 当たっている
			}

			// 浮力移動後の座標をセット
			m_Player.SetPosition(PlayerPos);
		}

		// どれも当たっていない時
		if (!Hit)
		{
			// プレイヤーの現在の座標を取得
			D3DXVECTOR2 PlayerPos = m_Player.GetPosition();

			// 浮力移動させる
			PlayerPos += m_Player.GetBouyant();

			// 浮力移動後の座標をセット
			m_Player.SetPosition(PlayerPos);
		}

	}


}

//****************************************************
// 説明		： ゲーム全体の重力の方向をセット
// 引数		： 重力方向
// 戻り値	： void
//****************************************************
void CModeGame::ChangeGravityDirection(int Direction)
{
	/* 重力処理クラスを継承している全てのオブジェクトの、重力方向の向きを変更 */
	// プレイヤー
	{
		m_Player.SetGravityObjectDirection(Direction);	// プレイヤーの重力方向をセット
		m_Player.SetSize(D3DXVECTOR2(m_Player.GetSize().y, m_Player.GetSize().x));	// サイズ値を入れ替え

		// 変わった方向によって処理変える
		if (m_GravityDirection == GRAVITY_LEFT)			// 左向きへ変わった時の処理
		{
			m_Player.SetTexRotation(D3DXToRadian(0));	// 回転値をいったんリセット
			m_Player.SetTexRotation(D3DXToRadian(90));	// プレイヤーテクスチャを90°回転
		}
		else if (m_GravityDirection == GRAVITY_DEFAULT)	// デフォルトへ変わった時の処理
		{
			m_Player.SetTexRotation(D3DXToRadian(0));	// 回転値をリセット
		}

	}



}


//****************************************************
// 説明		： マップチップとの当たり判定をとり、座標の調整も行う
// 引数		： マップチップ情報, 現在の座標, 移動前の座標, 座標調整を行うかどうかのフラグ(X軸), 座標調整を行うかどうかのフラグ(Y軸)
// 戻り値	： 【当たり】当たったチップの番号　　【外れ】「-1」
//****************************************************
int HitCheckMapchip(CMapchip Mapchip, D3DXVECTOR2* CurrentPos, D3DXVECTOR2 OldPos, bool FlagX, bool FlagY)
{
	// この関数内で使用する変数の宣言

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
		{
			// x軸
			if ( (nCurX - nOldX) != 0 && FlagX)	// 差がないときは調整する必要がない
			{
				// まずは、チップ と 移動前座標(プレイヤー) の位置関係を調べる
				int isLeft = (nOldX < nCurX);	// 移動前座標が左側にあるときは「1」になる
	
				if (isLeft)
				{	// 移動前座標が左側の時
					CurrentPos->x = (Mapchip.GetChipSize().x * nCurX);			// 座標調整（押し出し処理）

					/* 上の命令だけだと、次ループ時に、isLeft = 0判定となり、すりぬけちゃう */
					CurrentPos->x -= 0.5f;		// ↑これ対策の、やりたくないけど応急処置
				}
				else
				{
					CurrentPos->x = (Mapchip.GetChipSize().x * (nCurX + 1) );	// 座標調整（押し出し処理）
				}
			}

			// y軸
			if ( (nCurY - nOldY) != 0 && FlagY)	// 差がないときは調整する必要がない
			{
				// まずは、チップ と 移動前座標(プレイヤー) の位置関係を調べる
				int isTop = (nOldY < nCurY);	// 移動前座標が上側にあるときは「1」になる

				if (isTop)
				{	// 移動前座標が上側の時
					CurrentPos->y = (Mapchip.GetChipSize().y * nCurY);		// 座標調整（押し出し処理）

					/* 上の命令だけだと、次ループ時に、isTop = 0 判定となり、すりぬけちゃう */
					CurrentPos->y -= 0.5f;		// ↑これ対策の、やりたくないけど応急処置
				}
				else
				{
					CurrentPos->y = (Mapchip.GetChipSize().y * (nCurY + 1));	// 座標調整（押し出し処理）
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
// オブジェクトの配置処理
//=============================================================================
/*******************************************************************************
関数名	:	int PutAllObject(const char* pCsvStr)
引数		:	マップ配列の先頭アドレス
戻り値	:	成功→1		失敗→0
説明		:	全てのオブジェクトのセット
			【マップチップデータもここでセットしている】
			【注意】この関数を呼び出す前に、全てのオブジェクトの初期化処理を行うこと！
*******************************************************************************/
int CModeGame::PutAllObject(const char* pCsvMapFile)
{
	// この関数内で使用する変数の宣言
	char* pLoadedMapData = NULL;	// マップ情報のCsvファイルの読み込み先
	char* p = NULL;					// strtok_s用のポインタ
	char* pToken = NULL;			// strtok_sで抽出したトークンを示すポインタ
	int nTokenCnt = 0;				// 格納したトークンの数をカウントする変数（＝ マップチップ配列の要素数）

	// Csvファイルの、コメント部分を削除した状態のものを読み込み（カンマで区切られた数値データを抽出）
//	if ( LoadCsvFile(pCsvMapFile, pLoadedMapData, 8, ",") < 0)	// 負数が返されたら、読み込み失敗
	if ( LoadCsvFile(pCsvMapFile, &pLoadedMapData, true) < 0)	// 負数が返されたら、読み込み失敗
	{	// csvファイルのロード失敗時（エラーチェック）
		return 0;	// 失敗を返す
	}

	// マップチップデータをセット
	m_Mapchip.SetMapChipData(pLoadedMapData);
#ifdef _DEBUG
	m_DebugMapchip.SetMapChipData(pLoadedMapData);	// デバッグ表示用マップチップ
#endif // _DEBUG


	// 全てのオブジェクトをセット
	{
		pToken = strtok_s(pLoadedMapData, ",", &p);			// カンマに挟まれた文字列を抽出
		do
		{
			// オブジェクトの設置記号が見つかったときの処理
			if (strrchr(pToken, PLAYER_SYMBOL) != NULL)		// プレイヤーの設置記号が存在するか調べる
			{
				// プレイヤーを設置
				m_Player.SetPlayer( m_Mapchip.GetMapchipPosition(nTokenCnt) );	// 'P'の存在するチップの中心にプレイヤーをセット
			}
			else if (strrchr(pToken, ENEMY_SYMBOL) != NULL)	// エネミーの設置記号が存在するか調べる
			{
				// エネミーを設置
				PutEnemy(m_Mapchip.GetMapchipPosition(nTokenCnt));	// 'E'の存在するチップの中心に浮力加速エリアをセット
			}
			else if (strrchr(pToken, FURYOKU_SYMBOL) != NULL)	// 浮力加速の設置記号が存在するか調べる
			{
				// 浮力加速エリアを設置
				PutFloatForceArea( m_Mapchip.GetMapchipPosition(nTokenCnt) );	// 'F'の存在するチップの中心に浮力加速エリアをセット
			}
			else {	// 何もない時

			}

			// トークン数（現在のマップチップ配列の要素数）のカウント
			nTokenCnt++;

			// 次の文字列のブロックを格納
			pToken = strtok_s(NULL, ",", &p);
		} while (pToken != NULL);	// 見つからなくなるまで繰り返し
	}

	return 1;	// 成功を返す
}

// 全てのオブジェクトのセット
//void CModeGame::PutAllObject(char* MapDataFile, int chipTexDivX, int chipTexDivY)
//{
//	char* pLoad = NULL;	// 読み込み先
//	// Csvファイルの、コメント部分を削除した状態のものを読み込み（カンマで区切られた数値データを抽出）
//	LoadCsvFile(MapDataFile, pLoad, 8, ",");	// csvファイルのロード
//	m_Mapchip.SetMapChipData(pLoad);			// マップチップデータをセット
//
//	// プレイヤーやエネミー等も配置
//	PutPlayer(pLoad);	// プレイヤーを配置
////	PutEnemy(pLoad);	// エネミーを配置
//
//}

// csvのマップデータから、プレイヤーを配置する
//void CModeGame::PutPlayer(const char* csvMapData, char Symbol)
//{
//	int X, Y;	// マップチップ座標系での,　プレイヤーの位置
//	const char* SymbolPlace = NULL;
//	SymbolPlace = strrchr(csvMapData, Symbol);	// プレイヤーのシンボルがあるか調査
//}



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

// マップチップへのアクセス
CPlayer* CModeGame::GetPlayer()
{
	return &m_Player;	// プレイヤーの情報を返す
}

// 重力方向の取得
int CModeGame::GetGravityDirection()
{
	return m_GravityDirection;	// ゲーム全体の重力方向の情報を返す
}

//=============================================================================
// セッター関数
//=============================================================================
// スクロール座標の取得
void CModeGame::SetScrollPosition(D3DXVECTOR2 Pos)
{
	m_vScrollPos = Pos;
}

//=============================================================================
// メンバ関数（private）
//=============================================================================
bool CModeGame::PutFloatForceArea(D3DXVECTOR2 Pos)
{
	bool bRet = false;	// 戻り値

	for (int i = 0; i < FURYOKU_MAX; i++)
	{
		// 浮力エリアのセット
		if (m_FloatForceArea[i].SetFloatForceErea(Pos, m_Mapchip.GetChipSize(), FURYOKU_DIRECTION, FURYOKU_FORCE, FURYOKU_TEX_COLOR))
		{	// セットできた時
			bRet = true;	// 成功をセット
			break;			// このループから抜ける
		}
	}

	// セットできた時 → true
	// できなかった時 → false
	return bRet;
}

bool CModeGame::PutEnemy(D3DXVECTOR2 Pos)
{
	bool bRet = false;	// 戻り値

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		// エネミーのセット
		if ( m_Enemy[i].SetEnemy(Pos, false) )
		{	// セットできた時
			bRet = true;	// 成功をセット
			break;			// このループから抜ける
		}
	}

	// セットできた時 → true
	// できなかった時 → false
	return bRet;
}
