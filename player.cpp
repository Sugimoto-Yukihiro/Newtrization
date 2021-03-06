//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 立石大智, 杉本幸宏
//
//=============================================================================

#include "main.h"			// メイン
#include "renderer.h"		// レンダリング処理
#include "input.h"			// 入力処理
#include "player.h"			// プレイヤー処理
#include "texture.h"		// テクスチャ描画処理
#include "game.h"			// ゲーム画面
#include "collision.h"		// 衝突判定
#include "debugproc.h"		// デバッグ表示

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//------------------- テクスチャ関連
#define TEXTURE_WIDTH				(MAPCHIP_SIZE_DEFAULT.x)	// キャラサイズ	X
#define TEXTURE_HEIGHT				(MAPCHIP_SIZE_DEFAULT.y * 1.5f)	//				Y
#define TEXTURE_SIZE				D3DXVECTOR2(TEXTURE_WIDTH, TEXTURE_HEIGHT)	// キャラサイズ
#define TEXTURE_MAX					(2)			// 使用するテクスチャの数
//------------------- アニメーション
// アニメーションの分割数
#define TEXTURE_DIVIDE_X			(6)			// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_DIVIDE_Y			(1)			// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X * TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
// アニメーションが切り替わるWait値
#define ANIM_WAIT_DEFAULT			(5)			// デフォルト
#define ANIM_WAIT_DUSH				(2)			// ダッシュ時

//------------------- ステータス
#define HP_DEFAULT					(100.0f)	// HPのデフォルト値

//------------------- 移動関連
#define MOVE_VALUE					(7.0f)		// 基準移動値
#define RATE_DUSH					(2.0f)		// プレイヤーダッシュ時の移動値の倍率
#define JUMP_VALUE					(14.0f)		// プレイヤーのジャンプ力

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11ShaderResourceView	*g_Texture[TEXTURE_MAX] = { NULL };	// テクスチャ情報

// テクスチャのファイル名
static char *g_TextureName[] = {		// ここに新しいファイル名を追加したり、削除した場合は、上の"TEXTURE_MAX"の値も変える！！！
	"data/TEXTURE/player/player01_right.png",	// 右向き
	"data/TEXTURE/player/player01_left.png",	// 左向き

};

CPlayer::CPlayer()	// コンストラクタ
{
	Init();	// 初期化処理を行う
}

CPlayer::~CPlayer()	// デストラクタ
{

}

//=============================================================================
// 初期化処理
//=============================================================================
void CPlayer::Init(char* FireBootsTexName)
{
	//------------------- プレイヤークラスのメンバ変数をデフォルトの値でセット
	m_FireBoots.Init(FireBootsTexName);				// ファイヤーブーツの初期化
	m_Poison.Init(&m_LegPosition, &m_fCurrentHP, POISON_ATTACK_VALUE, POISON_FLAME_WAIT);	// 毒処理の初期化
	m_LegPosition = ZERO_VECTOR2;					// 座標を初期化
	m_fBouyant = ZERO_VECTOR2;						// 浮力を初期化
	m_fJumpForce = 0.0f;							// ジャンプ力を初期化
	m_fHitPointMAX = m_fCurrentHP = HP_DEFAULT;		// プレイヤーのHPをセット
	m_nTexNo = 0;									// 使うテクスチャ番号を指定
	m_bUse = false;									// 未使用
	m_bDush = false;								// ダッシュフラグはfalseで初期化
	m_bIsJump = false;								// ジャンプフラグはfalseで初期化
	m_bIsMove = false;								// 動作フラグはfalseで初期化
	m_bPoison = false;								// 毒状態はfalseで初期化
	m_bLeft = false;								// 右向きで初期化

	//------------------- ベースクラスの初期化
	CTexture::Init(SCREEN_CENTER, TEXTURE_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);	// テクスチャ
	CAnimation::Init(TEXTURE_DIVIDE_X, TEXTURE_DIVIDE_Y, ANIM_WAIT_DEFAULT);				// アニメーション（デフォルトでセット）
	CGravity::Init(SCREEN_CENTER, TEXTURE_SIZE, DEFAULT_GRAVITY_WAIT, GRAVITY_DEFAULT);		// 重力処理
}



//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit()
{
	//------------------- プレイヤークラスのメンバ変数をゼロクリア
	m_FireBoots.Uninit();	// ファイヤーブーツの終了処理
//	m_Poison.Uninit();		// 毒処理の終了処理
//	m_fJumpForce = 0.0f;	// ジャンプ力
//	m_fHitPointMAX = 0.0f;	// プレイヤーのHPのMAX値
//	m_fCurrentHP = 0.0f;	// プレイヤーの現在のHP
//	m_nTexNo = 1;			// 使うテクスチャ番号を指定
//	m_bUse = false;			// 未使用
//	m_bDush = false;		// ダッシュフラグはfalseで初期化
//	m_bIsJump = false;		// ジャンプフラグはfalseで初期化
//	m_bIsMove = false;		// 動作フラグはfalseで初期化
//	m_bPoison = false;		// 毒状態はfalseで初期化

	//------------------- ベースクラスの終了
	CTexture::Uninit();		// テクスチャ
	CAnimation::Uninit();	// アニメーション
	CGravity::Uninit();		// 重力処理
}



//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update(int FalmeCnt)
{
	// このプレイヤーが使われていたら更新処理実行
	if (m_bUse == true)
	{
		CMapchip Mapchip = *GetGame()->GetMapchip();	// マップチップ情報の取得
		D3DXVECTOR2 OldPosPlayer = GetPosition();		// 移動処理前のプレイヤー座標を保存

		// アニメーション
		if (m_bIsMove)	// 動作フラグが立っていたなら実行
		{
			SetAnimWait(ANIM_WAIT_DEFAULT);				// デフォルトのアニメーションWait値をセット
			if(m_bDush) SetAnimWait(ANIM_WAIT_DUSH);	// ダッシュ時のアニメーションWait値をセット

			UpdateAnimIndex(0, 5);	// 0-5番目の間をアニメーションする
		}

		// プレイヤーの移動処理（入力処理）
		InputControllPlayer();
		CollisionMapchip(Mapchip, OldPosPlayer);	// マップチップとの当たり判定をとって、入力処理移動後の座標をセット

		// 重力処理
		OldPosPlayer = GetPosition();	//移動前座標のセット
		CGravity::Update();				// プレイヤー座標の更新も自動的に行ってる

		// ファイヤーブーツ処理
		m_FireBoots.Update(GetGame()->GetMapchip()->GetMapChipSize());

		// マップチップと当たり判定を取って、最終的な座標をセット
		CollisionMapchip(Mapchip, OldPosPlayer);

		// 毒処理
		if (m_bPoison)
		{
			m_Poison.Update();	// 毒処理実行

			// プレイヤーの色を変えて、毒状態とわかりやすくする
			{
				// 現在の色情報を取得
				D3DXCOLOR color = GetTexColor();

				// プレイヤーを赤くする
				color.r = 1.0f;	// 赤
				color.g = 0.0f;	// 緑
				color.b = 0.0f;	// 青

				// 色情報のセット
				SetTexColor(color);
			}


		}
		else
		{
			SetTexColor(DEFAULT_COLOR);	// 色情報をリセット
		}

		//=================== スクロール座標の更新
		{
			D3DXVECTOR2 pos;	// 一時的な変数
			pos.x = GetPosition().x - SCROLL_SET_X;	// スクロール座標<x>に値を代入
			if (pos.x < 0.0f) pos.x = 0.0f;	// スクロール座標<x>が負なら「0」にリセット、正の数ならそのまま
			if (pos.x + SCREEN_WIDTH > Mapchip.GetMapChipSize().x) pos.x = Mapchip.GetMapChipSize().x - SCREEN_WIDTH;	// 画面右上の点がワールドの端に来たら"STAGE_W"の値にリセット
	
			pos.y = GetPosition().y - SCROLL_SET_Y;	// スクロール座標<y>に値を代入
			if (pos.y < 0.0f) pos.y = 0.0f;	// スクロール座標<y>負なら「0」にリセット、正の数ならそのまま
			if (pos.y + SCREEN_HEIGHT > Mapchip.GetMapChipSize().y) pos.y = Mapchip.GetMapChipSize().y - SCREEN_HEIGHT;	// 画面左下の点がワールドの端に来たら"STAGE_H"の値にリセット


			// 座標をセット
			GetGame()->SetScrollPosition(pos);
		}

	}

#ifdef _DEBUG	// デバッグ情報を表示する

//	// プレイヤーのHPをテストで上げ下げしてみる
//	if (GetKeyboardTrigger(DIK_DOWN))
//	{
//		m_fCurrentHP -= 10.0f;
//		if (m_fCurrentHP < 0) m_fCurrentHP = 0.0f;	// ０以下にしないようにする
//	}
//	if ( GetKeyboardTrigger(DIK_UP) )
//	{
//		m_fCurrentHP += 10.0f;
//		if (m_fCurrentHP > m_fHitPointMAX) m_fCurrentHP = m_fHitPointMAX;	// MAX値以上にしないようにする
//	}
//	PrintDebugProc("現在のHP: %f\n", m_fCurrentHP);
#endif
}



//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw(D3DXVECTOR2 ScrollPos)
{
	// このプレイヤーが生きていたら描画
	if (m_bUse == true)
	{
		// プレイヤーの表示座標を算出
		SetTexPos( GetPosition() - ScrollPos );	// 表示座標系をセット

		// プレイヤーの向きによって使用するテクスチャをセット
		if (m_bLeft)
		{
			m_nTexNo = 1;	// 左向き
		}
		else
		{
			m_nTexNo = 0;	// 右向き
		}


		// プレイヤーの描画
		DrawTexture(g_Texture[m_nTexNo]);

		// ファイヤーブーツの描画
		m_FireBoots.Draw(ScrollPos);
	}

}



//=============================================================================
// その他メンバ関数
//=============================================================================
// プレイヤーを殺す処理
void CPlayer::KillPlayer()
{
	// プレイヤーのuseフラグを折る
	SetUseFlag(false);

	/* プレイヤーが死んだ後に何か処理を行う場合はここに記入 */

}



//=============================================================================
// セッター関数
//=============================================================================
// プレイヤーを指定の座標に出現させる
void CPlayer::SetPlayer(D3DXVECTOR2 Pos)
{
	m_bUse = true;		// 使用フラグを true にする
	SetPosition(Pos);	// プレイヤーの座標をセット
}

// プレイヤーの座標をセット
void CPlayer::SetPosition(D3DXVECTOR2 Pos)
{
	SetGravityObjectPos(Pos);	// ワールド座標系

	// メンバ変数の方も変更
	m_LegPosition = Pos;

	// 足の場所に座標値をセット
	if (GetGravityObjectDirection() == GRAVITY_DEFAULT)		m_LegPosition.y += GetSize().y * 0.5f;
	else if (GetGravityObjectDirection() == GRAVITY_LEFT)	m_LegPosition.x -= GetSize().x * 0.5f;
}



//=============================================================================
// メンバ関数【private】
//=============================================================================
// プレイヤーを キーまたはゲームパッド入力 で動かす
void CPlayer::InputControllPlayer()
{
	D3DXVECTOR2 NowPosition = GetPosition();	// 現在の座標を取得
	float fMagnification = 1.0f;	// 移動値の倍率


	// ダッシュ処理
	{
		m_bDush = false;		// ダッシュしていない
		if(KEY_MOVE_PLAYER_DUSH || PAD_MOVE_PLAYER_DUSH)	// ダッシュボタンが押されているか
		{
			if (!m_bIsJump)		// ジャンプ中でなければ実行
			{
				fMagnification = fMagnification * RATE_DUSH;	// ダッシュ時の倍率を適用
				m_bDush = true;		// ダッシュしてた！
			}
		}
	}

	// キー入力
	{
		// 移動処理
		m_bIsMove = false;		// 動いてない
		if (GetGravityObjectDirection() == GRAVITY_DEFAULT)		// デフォルトの重力方向（y軸方向）の時
		{
			if (KEY_MOVE_PLAYER_RIGHT || PAD_MOVE_PLAYER_RIGHT)	// 右方向移動
			{
				NowPosition.x += MOVE_VALUE * fMagnification;	// x軸方向へ移動
				m_bIsMove = true;	// 動いてた！
				m_bLeft = false;	// 右向き
			}
			else if (KEY_MOVE_PLAYER_LEFT || PAD_MOVE_PLAYER_LEFT)	// 左方向移動
			{
				NowPosition.x -= MOVE_VALUE * fMagnification;	// x軸の負の方向へ移動
				m_bIsMove = true;	// 動いてた！
				m_bLeft = true;		// 左向き

			}

		}
		else if (GetGravityObjectDirection() == GRAVITY_LEFT)	// 左向きの重力方向（x軸の負）の時
		{
			if (KEY_MOVE_PLAYER_RIGHT || PAD_MOVE_PLAYER_RIGHT)	// 右方向移動
			{
				NowPosition.y += MOVE_VALUE * fMagnification;	// y軸方向へ移動
				m_bIsMove = true;	// 動いてる
				m_bLeft = false;	// 右向き
			}
			else if (KEY_MOVE_PLAYER_LEFT || PAD_MOVE_PLAYER_LEFT)	// 左方向移動
			{
				NowPosition.y -= MOVE_VALUE * fMagnification;	// y軸の負の方向へ移動
				m_bIsMove = true;	// 動いてる
				m_bLeft = true;		// 左向き

			}

		}

		// ジャンプ処理
		if (m_bOnGround)	// 接地しているときのみ、ジャンプ処理実行
		{
			if (KEY_MOVE_PLAYER_JUMP || PAD_MOVE_PLAYER_JUMP)	// ジャンプ操作のキーまたはボタンが押されたとき
			{
				m_bIsJump = true;			// ジャンプのフラグをtrueにする
				m_fJumpForce = JUMP_VALUE;	// ジャンプ力のセット
			}
		}

		// ファイヤーブーツの起動
		if (!m_bOnGround)	// 接地していない（空中にいる）時に実行する
		{
			if (KEY_ACTIVATE_PLAYER_FIREBOOTS || PAD_ACTIVATE_PLAYER_FIREBOOTS)	// ファイヤーブーツのキーが押されていたら実行
			{
				D3DXVECTOR2 bulletMove;	// バレットの移動量

				// 現在の重力方向によってバレットの移動量をセット
				if (GetGravityObjectDirection() == GRAVITY_DEFAULT) bulletMove = D3DXVECTOR2(0.0f, 1.0f) * FIREBOOTS_BULLET_SPEED;
				else if (GetGravityObjectDirection() == GRAVITY_LEFT) bulletMove = D3DXVECTOR2(-1.0f, 0.0f) * FIREBOOTS_BULLET_SPEED;

				// ファイヤーブーツ起動
				if (m_FireBoots.ActivateFireBoots(m_LegPosition, bulletMove, FIREBOOTS_BULLET_SIZE))
				{	// ファイヤーブーツが起動できた時　→　キャラクターを少しだけ浮かせる
					// 重力処理のリセット
					SetGravityFlag(false);
					SetGravityFlag(true);
					m_fJumpForce *= 0.75f;	// ジャンプ力を半分にする
				}
			}

		}

	}

	// ジャンプ処理実行
	if (m_bIsJump)
	{
		// ジャンプ処理実行
		if (GetGravityObjectDirection() == GRAVITY_DEFAULT)		// 左向きの重力方向（x軸の負）の時
		{
			NowPosition.y -= m_fJumpForce;	// y軸の不の向きにプレイヤーを移動
		}
		else if (GetGravityObjectDirection() == GRAVITY_LEFT)	// 左向きの重力方向（x軸の負）の時
		{
			NowPosition.x += m_fJumpForce;	// x軸の正の向きにプレイヤーを移動
		}
	}


	// プレイヤーのキー移動後の座標をセット
	SetPosition(NowPosition);
}

// マップチップとの当たり判定を取って押し出し処理を行う
void CPlayer::CollisionMapchip(CMapchip Mapchip, D3DXVECTOR2 PlayerOldPos)
{
	// 移動処理後のプレイヤーの座標を保存
	D3DXVECTOR2 CurrentPosPlayer = GetPosition();

	// プレイヤーの半分のサイズを保存
	D3DXVECTOR2 HalfPlayer = GetSize() * 0.5f;

	//============ プレイヤーの左側の判定
	CurrentPosPlayer.x -= HalfPlayer.x;	// 座標情報をプレイヤーテクスチャの左側へずらす
	// 当たり判定実行 ＆ 下側の座標調整
	if (HitCheckMapchip(Mapchip, &CurrentPosPlayer, PlayerOldPos, true, false) == -1)	// 当たっていない時
	{
		// （重力方向が左のとき）左側に当たっていない ＝ 空中にいるってことだから、重力処理のフラグはそのまま(true)
		if (GetGame()->GetGravityDirection() == GRAVITY_LEFT) 
		{	// 空中にいる時の処理
			NotOnGround();
		}
	}
	else
	{	// （重力方向が左のとき）左側に当たっている ＝ 着地しているってことだから、重力処理のフラグを折る
		if (GetGame()->GetGravityDirection() == GRAVITY_LEFT)
		{	// 着地時の処理
			OnGround();
		}
	}
	CurrentPosPlayer.x += HalfPlayer.x;	// ずらした分を元に戻す

	//============ プレイヤーの右側の判定
	CurrentPosPlayer.x += HalfPlayer.x;	// 座標情報をプレイヤーテクスチャの右側へずらす
	HitCheckMapchip(Mapchip, &CurrentPosPlayer, PlayerOldPos, true, false);	// 当たり判定実行 ＆ 右側の座標調整
	CurrentPosPlayer.x -= HalfPlayer.x;	// ずらした分を元に戻す

	//============ プレイヤーの上側の判定
	CurrentPosPlayer.y -= HalfPlayer.y;	// 座標情報をプレイヤーテクスチャの上側へずらす
	HitCheckMapchip(Mapchip, &CurrentPosPlayer, PlayerOldPos, false, true);	// 当たり判定実行 ＆ 上側の座標調整
	CurrentPosPlayer.y += HalfPlayer.y;	// ずらした分を元に戻す

	//============ プレイヤーの下側の判定
	CurrentPosPlayer.y += HalfPlayer.y;	// 座標情報をプレイヤーテクスチャの下側へずらす
	// 当たり判定実行 ＆ 下側の座標調整										ジャンプ力 < 重力値　　のとき、Y方向の座標調整を行う
	if (HitCheckMapchip(Mapchip, &CurrentPosPlayer, PlayerOldPos, false, true ) == -1)	// 当たっていない時
	{	// （重力方向が下のとき）下側に当たっていない ＝ 空中にいるってことだから、重力処理のフラグはそのまま(true)
		if (GetGame()->GetGravityDirection() == GRAVITY_DEFAULT)
		{	// 空中にいる時の処理
			NotOnGround();
		}
	}
	else
	{
		// （重力方向が下のとき）下側に当たっている ＝ 着地しているってことだから、重力処理のフラグを折る
		if (GetGame()->GetGravityDirection() == GRAVITY_DEFAULT)
		{	// 着地時の処理
			OnGround();
		}

	}
	CurrentPosPlayer.y -= HalfPlayer.y;	// ずらした分を元に戻す

	// 最終的な座標をセット
	SetPosition(CurrentPosPlayer);
}

// 着地した時の処理
void CPlayer::OnGround()
{
	m_bOnGround = true;			// 接地してる
	SetGravityFlag(false);		// 重力方向が下向きなら実行
	m_bIsJump = false;			// ジャンプフラグもfalseにする
	m_fJumpForce = 0.0f;		// ジャンプ力を初期化
	m_fBouyant = ZERO_VECTOR2;	// 浮力を初期化

}

// 空中にいる時の処理
void CPlayer::NotOnGround()
{
	m_bOnGround = false;	// 空中にいる
	SetGravityFlag(true);	// 重力処理フラグ "true" にセット
}


// プレイヤーのテクスチャを生成
void CreatePlayerTexture(void)
{
	// テクスチャ生成
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		CreateTexture(g_TextureName[i], &g_Texture[i]);
	}
}

// プレイヤーのテクスチャを解放
void ReleasePlayerTexture(void)
{
	// テクスチャ解放
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		ReleaseTexture(&g_Texture[i]);
	}

}
