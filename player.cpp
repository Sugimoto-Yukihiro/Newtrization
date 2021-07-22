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
#define TEXTURE_WIDTH				(MAPCHIP_SIZE_X)	// キャラサイズ	X
#define TEXTURE_HEIGHT				(MAPCHIP_SIZE_Y)	//				Y
//#define TEXTURE_SIZE				D3DXVECTOR2(TEXTURE_WIDTH, TEXTURE_HEIGHT)	// キャラサイズ
#define TEXTURE_SIZE				MAPCHIP_SIZE_DEFAULT	// キャラサイズ

#define TEXTURE_MAX					(3)			// テクスチャの数

#define TEXTURE_PATTERN_DIVIDE_X	(3)			// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y	(1)			// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define ANIM_WAIT					(5)			// アニメーションの切り替わるデフォルトWait値
#define MOVE_VALUE					(10.0f)


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer				*g_VertexBuffer = NULL;				// 頂点情報
static ID3D11ShaderResourceView	*g_Texture[TEXTURE_MAX] = { NULL };	// テクスチャ情報

// テクスチャのファイル名
static char *g_TextureName[] = {
	"data/TEXTURE/player.png",				// TexNo : 0
	"data/TEXTURE/player/player01.png",		// TexNo : 1
	"data/TEXTURE/player/player01_Back_Not_Invisible.png",	// TexNo : 2
};

//static CPlayer	g_aPlayer[PLAYER_MAX];								// プレイヤーインスタンス

//=============================================================================
// コンストラクタ・デストラクタ
//=============================================================================
CPlayer::CPlayer()		// コンストラクタ
{
	Init();
}

CPlayer::~CPlayer()		// デストラクタ
{

}

//=============================================================================
// 初期化処理
//=============================================================================
void CPlayer::Init()
{
	// プレイヤークラスの初期化
	m_bUse = true;
	m_nTexNo = 2;		// ２番目のテクスチャ番号を使う

	//------------------- ベースクラスの初期化
	CTexture::Init();	// テクスチャ
	SetPlayerUseFlag(true);
	SetTextureInf(SCREEN_CENTER, TEXTURE_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, ZERO_VECTOR2);
	SetAnimInf(6, 1, ANIM_WAIT);
//	SetTexRotation(D3DXToRadian(90));	// 左側重力の時

	CGravity::Init();	// 重力処理
	SetPlayerPos(SCREEN_CENTER);
}



//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update()
{
	// このプレイヤーが使われていたら更新処理実行
	if (m_bUse == true)
	{
		// マップチップ情報の取得
		CMapchip Mapchip = *GetGame()->GetMapchip();

		// 移動処理前のプレイヤー座標を保存
		D3DXVECTOR2 OldPosPlayer = GetPlayerPos();

		// アニメーション
		UpdateAnimIndex(0, 5);	// 0-5番目の間をアニメーションする

		// プレイヤーの移動処理（入力処理）
		{
			// プレイヤーの移動値を保存する変数
			D3DXVECTOR2 move = OldPosPlayer;	// 現在のプレイヤーの座標で初期化

			// キー入力で移動
			//if (GetKeyboardPress(DIK_DOWN))
			//{
			//	move.y += MOVE_VALUE;
			//}
			//if (GetKeyboardPress(DIK_UP))
			//{
			//	move.y -= MOVE_VALUE;
			//}
			if (GetKeyboardPress(DIK_RIGHT))
			{
				move.x += MOVE_VALUE;
			}
			else if (GetKeyboardPress(DIK_LEFT))
			{
				move.x -= MOVE_VALUE;
			}

			// ゲームパッドで移動処理
			if (IsButtonPressed(0, BUTTON_DOWN))
			{
				move.y += MOVE_VALUE;
			}
			else if (IsButtonPressed(0, BUTTON_UP))
			{
				move.y -= MOVE_VALUE;
			}
			else if (IsButtonPressed(0, BUTTON_RIGHT))
			{
				move.x += MOVE_VALUE;
			}
			else if (IsButtonPressed(0, BUTTON_LEFT))
			{
				move.x -= MOVE_VALUE;
			}

			// プレイヤーのキー移動後の座標をセット
			SetPlayerPos(move);
		}

		// 重力処理
		{
			// 重力処理実行
			CGravity::Update();	// プレイヤー座標の更新も自動的に行ってる
		}

		// マップチップとの当たり判定をとって、最終的な座標をセット
		{
			// 移動処理後のプレイヤーの座標を保存
			D3DXVECTOR2 CurrentPosPlayer = GetPlayerPos();

			// プレイヤーの半分のサイズを保存
			D3DXVECTOR2 HalfPlayer = GetPlayerSize() * 0.5f;

		//	HitCheckMapchip(*GetGame()->GetMapchip(), &CurrentPosPlayer, OldPosPlayer, GetPlayerSize() * 0.5f);	// 当たり判定実行 ＆ 上側の座標調整

			// プレイヤーの左側の判定
			CurrentPosPlayer.x -= HalfPlayer.x;	// 座標情報をプレイヤーテクスチャの左側へずらす
			HitCheckMapchip(*GetGame()->GetMapchip(), &CurrentPosPlayer, OldPosPlayer);	// 当たり判定実行 ＆ 左側の座標調整
			CurrentPosPlayer.x += HalfPlayer.x;	// ずらした分を元に戻す

			// プレイヤーの右側の判定
			CurrentPosPlayer.x += HalfPlayer.x;	// 座標情報をプレイヤーテクスチャの右側へずらす
			HitCheckMapchip(*GetGame()->GetMapchip(), &CurrentPosPlayer, OldPosPlayer);	// 当たり判定実行 ＆ 右側の座標調整
			CurrentPosPlayer.x -= HalfPlayer.x;	// ずらした分を元に戻す



			// 重力処理を行っている時のみ、上下の判定を行う
			if (GetGravityFlag())
			{
				// プレイヤーの上側の判定
				CurrentPosPlayer.y -= HalfPlayer.y;	// 座標情報をプレイヤーテクスチャの上側へずらす
				HitCheckMapchip(*GetGame()->GetMapchip(), &CurrentPosPlayer, OldPosPlayer);	// 当たり判定実行 ＆ 上側の座標調整
				CurrentPosPlayer.y += HalfPlayer.y;	// ずらした分を元に戻す
	

				// プレイヤーの下側の判定
				CurrentPosPlayer.y += HalfPlayer.y;	// 座標情報をプレイヤーテクスチャの下側へずらす
	
				// 当たり判定実行 ＆ 下側の座標調整
				if (HitCheckMapchip(*GetGame()->GetMapchip(), &CurrentPosPlayer, OldPosPlayer) == -1 )
				{	// 下側に当たっていない ＝ 空中にいるってことだから、重力処理のフラグはそのまま(true)
				//	SetGravityFlag(true);
				}
				else
				{	// 下側に当たっている ＝ 着地しているってことだから、重力処理のフラグを折る
					SetGravityFlag(false);
				}

				CurrentPosPlayer.y -= HalfPlayer.y;	// ずらした分を元に戻す
			}

			// 最終的な座標をセット
			SetPlayerPos(CurrentPosPlayer);
		}

		//=================== スクロール座標の更新
		{
			D3DXVECTOR2 pos;	// 一時的な変数
			pos.x = GetPlayerPos().x - SCROLL_SET_X;	// スクロール座標<x>に値を代入
			pos.x = (pos.x < 0.0f) ? 0.0f : pos.x;		// スクロール座標<x>が負なら「0」にリセット、正の数ならそのまま
			pos.x = (pos.x + SCREEN_WIDTH > Mapchip.GetStageSize().x) ? Mapchip.GetStageSize().x - SCREEN_WIDTH : pos.x;		// 画面右上の点がワールドの端に来たら"STAGE_W"の値にリセット
	
			pos.y = GetPlayerPos().y - SCROLL_SET_Y;	// スクロール座標<y>に値を代入
			pos.y = (pos.y < 0.0f) ? 0.0f : pos.y;		// スクロール座標<y>負なら「0」にリセット、正の数ならそのまま
			pos.y = (pos.y + SCREEN_HEIGHT > Mapchip.GetStageSize().y) ? Mapchip.GetStageSize().y - SCREEN_HEIGHT : pos.y;	// 画面右上の点がワールドの端に来たら"STAGE_H"の値にリセット

			// 座標をセット
			GetGame()->SetScrollPosition(pos);
		}

	}

#ifdef _DEBUG	// デバッグ情報を表示する
	PrintDebugProc("playerAnimIdx : %d\n", GetCurrentAnim());
	PrintDebugProc("Player座標　X:%f Y:%f\n", GetPlayerPos().x, GetPlayerPos().y);
	PrintDebugProc("プレイヤー座標のマップチップ : %d\n", GetGame()->GetMapchip()->GetMapchipNo(GetPlayerPos()));

	char *str = GetDebugStr();
	sprintf(&str[strlen(str)], " PX:%f PY:%f", GetPlayerPos().x, GetPlayerPos().y);

	//PrintDebugProc("Player X:%f Y:%f \n", pos.x, pos.y );
#endif
}



//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw()
{
	PresetDrawPlayer();

	if (m_bUse == true)
	{
		// プレイヤーの表示座標を算出
		SetTexPos( GetPlayerPos() - GetGame()->GetScrollPosition() );	// 表示座標系をセット
	//1	D3DXVECTOR2 worldPos = GetPlayerPos();	// 現在の座標を退避
	//1	SetPlayerPos( GetPlayerPos() - GetGame()->GetScrollPosition() );	// 表示座標系にセット

		// 描画
		DrawTexture(g_VertexBuffer, g_Texture[m_nTexNo]);

	//1	SetPlayerPos(worldPos);	// ワールド座標系に戻す
	}
}



//=============================================================================
// メンバ関数
//=============================================================================


//=============================================================================
// セッター関数
//=============================================================================
// プレイヤーの座標をセット
void CPlayer:: SetPlayerPos(D3DXVECTOR2 Pos)
{
//	SetTexPos(Pos);	// プレイヤーテクスチャの座標 ＝ プレイヤーの座標
	SetGravityObjectPos(Pos);	// ワールド座標系
}

// プレイヤーのuseフラグのセット
void CPlayer::SetPlayerUseFlag(bool Use)
{
	m_bUse = Use;
}

// プレイヤーを殺す処理
void CPlayer::KillPlayer()
{
	// プレイヤーのuseフラグを折る
	SetPlayerUseFlag(false);

	/* プレイヤーが死んだ後に何か処理を行う場合はここに記入 */

}

//=============================================================================
// ゲッター関数
//=============================================================================
// プレイヤーの座標を取得
D3DXVECTOR2 CPlayer::GetPlayerPos()
{
//	return GetTexPos();				// プレイヤーテクスチャの座標 ＝ プレイヤーの座標 ってこと
	return GetGravityObjectPos();	// ワールド座標系
}

// プレイヤーのサイズを取得
D3DXVECTOR2 CPlayer::GetPlayerSize()
{
	return GetTexSize();			// プレイヤーテクスチャのサイズを返す
}

// プレイヤーのuseフラグの取得
bool CPlayer::GetPlayerUseFlag()
{
	return m_bUse;
}




void CreatePlayerTextureAndBuffer()
{
	// テクスチャ生成
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		CreateTexture(g_TextureName[i], &g_Texture[i]);
	}

	// 頂点バッファ生成
	CreateVertexBuffer(&g_VertexBuffer);

}

void ReleasePlayerTextureAndBuffer()
{
	// テクスチャ解放
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		ReleaseTexture(&g_Texture[i], &g_VertexBuffer);
	}

}

void PresetDrawPlayer(void)
{
	// 描画前の処理
	PresetDraw2D(&g_VertexBuffer);
}

