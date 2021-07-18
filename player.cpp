//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 立石大智, 杉本幸宏
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "player.h"
#include "texture.h"
#include "game.h"

#include "debugproc.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_WIDTH				(128.0f)	// キャラサイズ	X
#define TEXTURE_HEIGHT				(192.0f)	//				Y
#define TEXTURE_SIZE				D3DXVECTOR2(TEXTURE_WIDTH, TEXTURE_HEIGHT)	// キャラサイズ

#define TEXTURE_MAX					(2)			// テクスチャの数

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

static char *g_TextureName[] = {
	"data/TEXTURE/player.png",				// TexNo : 0
	"data/TEXTURE/player/player01.png",		// TexNo : 1
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
	m_nTexNo = 1;

	//------------------- ベースクラスの初期化
	CTexture::Init();	// テクスチャ描画処理
	SetPlayerUseFlag(true);
	SetTextureInf(SCREEN_CENTER, TEXTURE_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, ZERO_VECTOR2);
	SetAnimInf(6, 1, ANIM_WAIT);

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
		// アニメーション
		UpdateAnimIndex(0, 5);	// 

		// プレイヤーの移動処理
		{
			// プレイヤーの移動値を保存する変数
			D3DXVECTOR2 move = GetPlayerPos();	// 現在のプレイヤーの座標で初期化

			// キー入力で移動
			if (GetKeyboardPress(DIK_DOWN))
			{
				move.y += MOVE_VALUE;
			}
			else if (GetKeyboardPress(DIK_UP))
			{
				move.y -= MOVE_VALUE;
			}
			else if (GetKeyboardPress(DIK_RIGHT))
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

			// 重力処理

			CGravity::Update( *GetGame()->GetMapchip() );
		}




		//=================== スクロール座標の更新
		{
			D3DXVECTOR2 pos;	// 一時的な変数
			pos.x = GetPlayerPos().x - SCROLL_SET_X;			// スクロール座標<x>に値を代入
			pos.x = (pos.x < 0.0f) ? 0.0f : pos.x;	// スクロール座標<x>が負なら「0」にリセット、正の数ならそのまま
			pos.x = (pos.x + SCREEN_WIDTH > GetGame()->GetMapchip()->GetStageSize().x) ? GetGame()->GetMapchip()->GetStageSize().x - SCREEN_WIDTH : pos.x;		// 画面右上の点がワールドの端に来たら"STAGE_W"の値にリセット
	
			pos.y = GetPlayerPos().y - SCROLL_SET_Y;			// スクロール座標<y>に値を代入
			pos.y = (pos.y < 0.0f) ? 0.0f : pos.y;	// スクロール座標<y>負なら「0」にリセット、正の数ならそのまま
			pos.y = (pos.y + SCREEN_HEIGHT > GetGame()->GetMapchip()->GetStageSize().y) ? GetGame()->GetMapchip()->GetStageSize().y - SCREEN_HEIGHT : pos.y;	// 画面右上の点がワールドの端に来たら"STAGE_H"の値にリセット

			// 座標をセット
			GetGame()->SetScrollPosition(pos);
		}

	}




	PrintDebugProc("playerAnimIdx : %d\n", GetCurrentAnim());
	PrintDebugProc("Player座標　X:%f Y:%f\n", GetPlayerPos().x, GetPlayerPos().y);
	PrintDebugProc("プレイヤー座標のマップチップ : %d\n", GetGame()->GetMapchip()->GetMapchipNo(GetPlayerPos()));


#ifdef _DEBUG	// デバッグ情報を表示する
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

