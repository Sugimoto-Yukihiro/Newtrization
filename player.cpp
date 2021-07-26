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
#define TEXTURE_WIDTH				(MAPCHIP_SIZE_DEFAULT.x)		// キャラサイズ	X
#define TEXTURE_HEIGHT				(MAPCHIP_SIZE_DEFAULT.y * 2)	//				Y
#define TEXTURE_SIZE				D3DXVECTOR2(TEXTURE_WIDTH, TEXTURE_HEIGHT)	// キャラサイズ
//#define TEXTURE_SIZE				MAPCHIP_SIZE_DEFAULT	// キャラサイズ
#define TEXTURE_MAX					(3)			// テクスチャの数
//------------------- アニメーション
// アニメーションの分割数
#define TEXTURE_PATTERN_DIVIDE_X	(3)			// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y	(1)			// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
// アニメーションが切り替わるWait値
#define ANIM_WAIT_DEFAULT			(5)			// デフォルト
#define ANIM_WAIT_DUSH				(2)			// ダッシュ時

//------------------- 移動関連
#define MOVE_VALUE					(10.0f)		// 基準移動値
#define RATE_DUSH					(2.0f)		// プレイヤーダッシュ時の移動値の倍率
#define JUMP_VALUE					(14.0f)		// プレイヤーのジャンプ力
	
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer				*g_VertexBuffer = NULL;				// 頂点情報
static ID3D11ShaderResourceView	*g_Texture[TEXTURE_MAX] = { NULL };	// テクスチャ情報

// テクスチャのファイル名
static char *g_TextureName[] = {	// ここに新しいファイル名を追加したり、削除した場合は、上の"TEXTURE_MAX"の値も変える！！！
	"data/TEXTURE/player.png",				// TexNo : 0
	"data/TEXTURE/player/player01.png",		// TexNo : 1
	"data/TEXTURE/player/player01_Back_Not_Invisible.png",	// TexNo : 2
};

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
	m_nTexNo = 2;		// ２番目のテクスチャ番号を使う
	m_bUse = true;		// 使用
	m_bDush = false;	// ダッシュフラグはfalseで初期化
	m_bIsJump = false;	// ジャンプフラグはfalseで初期化
	m_bIsMove = false;	// 動作フラグはfalseで初期化

	//------------------- ベースクラスの初期化
	CTexture::Init();	// テクスチャ
	SetPlayerUseFlag(true);
	SetTextureInf(SCREEN_CENTER, TEXTURE_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, ZERO_VECTOR2);
	SetAnimInf(6, 1, ANIM_WAIT_DEFAULT);	// デフォルトでセット
//	SetTexRotation(D3DXToRadian(90));	// 左側重力の時

	CGravity::Init();	// 重力処理
	SetPlayerPos(SCREEN_CENTER);	// 後々マップチップデータで設定できるようにする
	SetPlayerSize(TEXTURE_SIZE);	// テクスチャのサイズをセット
}



//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update()
{
	// このプレイヤーが使われていたら更新処理実行
	if (m_bUse == true)
	{
		CMapchip Mapchip = *GetGame()->GetMapchip();	// マップチップ情報の取得
		D3DXVECTOR2 OldPosPlayer = GetPlayerPos();		// 移動処理前のプレイヤー座標を保存

		// アニメーション
		if (m_bIsMove)	// 動作フラグが立っていたなら実行
		{
			SetAnimWait(ANIM_WAIT_DEFAULT);				// デフォルトのアニメーションWait値をセット
			if(m_bDush) SetAnimWait(ANIM_WAIT_DUSH);	// ダッシュ時のアニメーションWait値をセット

			UpdateAnimIndex(0, 5);	// 0-5番目の間をアニメーションする
		}


		// プレイヤーの移動処理（入力処理）
		ControllPlayerInput(GetPlayerPos());
		CollisionMapchip(Mapchip, OldPosPlayer);	// マップチップとの当たり判定をとって、最終的な座標をセット

		// 重力処理
		OldPosPlayer = GetPlayerPos();				//移動前座標のセット
		CGravity::Update();							// プレイヤー座標の更新も自動的に行ってる
		CollisionMapchip(Mapchip, OldPosPlayer);	// マップチップと当たり判定を取って座標調整

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
// セッター関数
//=============================================================================
// プレイヤーの座標をセット
void CPlayer:: SetPlayerPos(D3DXVECTOR2 Pos)
{
//	SetTexPos(Pos);	// プレイヤーテクスチャの座標 ＝ プレイヤーの座標
	SetGravityObjectPos(Pos);	// ワールド座標系
}

// プレイヤーのサイズを取得
void CPlayer::SetPlayerSize(D3DXVECTOR2 Size)
{
	return SetGravityObjectSize(Size);	// プレイヤーのサイズを返す
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
//	return GetTexSize();			// プレイヤーテクスチャのサイズを返す
	return GetGravityObjectSize();	// プレイヤーのサイズを返す
}

// プレイヤーのuseフラグの取得
bool CPlayer::GetPlayerUseFlag()
{
	return m_bUse;
}



//=============================================================================
// メンバ関数(private)
//=============================================================================
// プレイヤーを キーまたはゲームパッド入力 で動かす
void CPlayer::ControllPlayerInput(D3DXVECTOR2 NowPosition)
{
	// 移動値の倍率
	float fMagnification = 1.0f;

	m_bDush = false;		// ダッシュしていない
	if(KEY_MOVE_PLAYER_DUSH || PAD_MOVE_PLAYER_DUSH)	// ダッシュボタンが押されているか
	{	
		fMagnification = fMagnification * RATE_DUSH;	// ダッシュ時の倍率を適用
		m_bDush = true;		// ダッシュしてた！
	}

	// キー入力で移動
	m_bIsMove = false;			// 動いてない
	if (GetGravityObjectDirection() == GRAVITY_DEFAULT)		// デフォルトの重力方向（y軸方向）の時
	{
		if (KEY_MOVE_PLAYER_RIGHT || PAD_MOVE_PLAYER_RIGHT)	// 右方向移動
		{
			NowPosition.x += MOVE_VALUE * fMagnification;	// x軸方向へ移動
			m_bIsMove = true;	// 動いてた！
		}
		else if (KEY_MOVE_PLAYER_LEFT || PAD_MOVE_PLAYER_LEFT)	// 左方向移動
		{
			NowPosition.x -= MOVE_VALUE * fMagnification;	// x軸の負の方向へ移動
			m_bIsMove = true;	// 動いてた！
		}

		// ジャンプ処理
		if (KEY_MOVE_PLAYER_JUMP || PAD_MOVE_PLAYER_JUMP)	// ジャンプ操作のキーまたはボタンが押されたとき
		{
			m_bIsJump = true;	// ジャンプのフラグをtrueにする
		//	NowPosition.y -= JUMP_VALUE;
		}

		// ジャンプ処理実行
		if (m_bIsJump) NowPosition.y -= JUMP_VALUE;
	}
	else if (GetGravityObjectDirection() == GRAVITY_LEFT)	// 左向きの重力方向（x軸の負）の時
	{
		if (KEY_MOVE_PLAYER_RIGHT || PAD_MOVE_PLAYER_RIGHT)	// 右方向移動
		{
			NowPosition.y += MOVE_VALUE * fMagnification;	// y軸方向へ移動
			m_bIsMove = true;	// 動いてる
		}
		else if (KEY_MOVE_PLAYER_LEFT || PAD_MOVE_PLAYER_LEFT)	// 左方向移動
		{
			NowPosition.y -= MOVE_VALUE * fMagnification;	// y軸の負の方向へ移動
			m_bIsMove = true;	// 動いてる
		}

		// ジャンプ処理
		if (KEY_MOVE_PLAYER_JUMP || PAD_MOVE_PLAYER_JUMP)
		{
			m_bIsJump = true;	// ジャンプのフラグをtrueにする
		//	NowPosition.x += JUMP_VALUE;
		}

		// ジャンプ処理実行
		if (m_bIsJump) NowPosition.x += JUMP_VALUE;
	}

	// プレイヤーのキー移動後の座標をセット
	SetPlayerPos(NowPosition);
}

// マップチップとの当たり判定を取って押し出し処理を行う
void CPlayer::CollisionMapchip(CMapchip Mapchip, D3DXVECTOR2 PlayerOldPos)
{
	// 移動処理後のプレイヤーの座標を保存
	D3DXVECTOR2 CurrentPosPlayer = GetPlayerPos();

	// プレイヤーの半分のサイズを保存
	D3DXVECTOR2 HalfPlayer = GetPlayerSize() * 0.5f;

	//============ プレイヤーの左側の判定
	CurrentPosPlayer.x -= HalfPlayer.x;	// 座標情報をプレイヤーテクスチャの左側へずらす
	// 当たり判定実行 ＆ 下側の座標調整
	if (HitCheckMapchip(Mapchip, &CurrentPosPlayer, PlayerOldPos) == -1)	// 当たっていない時
	{
		// 左側に当たっていない ＝ 空中にいるってことだから、重力処理のフラグはそのまま(true)
		if (GetGame()->GetGravityDirection() == GRAVITY_LEFT) SetGravityFlag(true);	// 重力方向が左向きなら実行
	}
	else
	{	// 左側に当たっている ＝ 着地しているってことだから、重力処理のフラグを折る
		if (GetGame()->GetGravityDirection() == GRAVITY_LEFT) SetGravityFlag(false);// 重力方向が右向きなら実行
		m_bIsJump = false;	// ジャンプフラグもfalseにする
	}
	CurrentPosPlayer.x += HalfPlayer.x;	// ずらした分を元に戻す

	//============ プレイヤーの右側の判定
	CurrentPosPlayer.x += HalfPlayer.x;	// 座標情報をプレイヤーテクスチャの右側へずらす
	HitCheckMapchip(Mapchip, &CurrentPosPlayer, PlayerOldPos);	// 当たり判定実行 ＆ 右側の座標調整
	CurrentPosPlayer.x -= HalfPlayer.x;	// ずらした分を元に戻す

	//============ プレイヤーの上側の判定
	CurrentPosPlayer.y -= HalfPlayer.y;	// 座標情報をプレイヤーテクスチャの上側へずらす
	HitCheckMapchip(Mapchip, &CurrentPosPlayer, PlayerOldPos);	// 当たり判定実行 ＆ 上側の座標調整
	CurrentPosPlayer.y += HalfPlayer.y;	// ずらした分を元に戻す

	//============ プレイヤーの下側の判定
	CurrentPosPlayer.y += HalfPlayer.y;	// 座標情報をプレイヤーテクスチャの下側へずらす
	// 当たり判定実行 ＆ 下側の座標調整
	if (HitCheckMapchip(Mapchip, &CurrentPosPlayer, PlayerOldPos) == -1)	// 当たっていない時
	{	// 下側に当たっていない ＝ 空中にいるってことだから、重力処理のフラグはそのまま(true)
		if (GetGame()->GetGravityDirection() == GRAVITY_DEFAULT) SetGravityFlag(true);
	}
	else
	{
		// 下側に当たっている ＝ 着地しているってことだから、重力処理のフラグを折る
		if (GetGame()->GetGravityDirection() == GRAVITY_DEFAULT) SetGravityFlag(false);
		m_bIsJump = false;	// ジャンプフラグもfalseにする
	}
	CurrentPosPlayer.y -= HalfPlayer.y;	// ずらした分を元に戻す

	// 最終的な座標をセット
	SetPlayerPos(CurrentPosPlayer);
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

