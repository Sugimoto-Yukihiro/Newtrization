//=============================================================================
//
// エネミー処理 [enemy.cpp]
// Author : 稲垣佑二郎, 杉本幸宏
//
//=============================================================================

#include "main.h"
#include "renderer.h"

#include "enemy.h"
#include "game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_WIDTH				(64.0f)	// キャラサイズ
#define TEXTURE_HEIGHT				(64.0f)	// 
//#define TEXTURE_MAX					(1)		// テクスチャの数

#define TEXTURE_PATTERN_DIVIDE_X	(1)		// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y	(1)		// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define ANIM_WAIT					(4)		// アニメーションの切り替わるWait値

#define TEXTURE_SIZE				D3DXVECTOR2(TEXTURE_WIDTH, TEXTURE_HEIGHT)			// サイズ

#define VALUE_MOVE					(4.0f)	// エネミーの移動速度

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11ShaderResourceView	*g_Texture[ENEMY_TEX_PATTARN_MAX] = { NULL };	// テクスチャ情報

static char *g_TextureName[] = {
	"data/TEXTURE/enemy/0813_CHARACTER_警備員.PNG",	// ENEMY_TEX_01
	"data/TEXTURE/enemy/0813_CHARACTER_警備員左.PNG",	// ENEMY_TEX_01
};

//CEnemy g_Enemy[ENEMY_MAX];							// エネミー構造体

// エネミーの線形移動用の移動座標テーブル
//static D3DXVECTOR3 g_MoveTbl[] = {
//	D3DXVECTOR3(0.0f, 0.0f, 0.0f),
//	D3DXVECTOR3(200.0f, 0.0f, 0.0f),
//	D3DXVECTOR3(200.0f, 200.0f, 0.0f),
//};

// エネミーの線形移動用の移動スピードテーブル
//static float g_MoveSpd[] = {
//	0.01f,
//	0.01f,
//	0.01f,
//};


//=============================================================================
// コンストラクタ
//=============================================================================
CEnemy::CEnemy()
{
	Init();	// 初期化する

	//// エネミー構造体の初期化
	//use = true;
	//w = TEXTURE_WIDTH;
	//h = TEXTURE_HEIGHT;
	//pos = D3DXVECTOR3((float)SCREEN_CENTER_X, 300.0f, 0.0f);
	//rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//texNo = 0;

	//countAnim = 0;
	//patternAnim = 0;

	//time = 0.0f;
}

void CEnemy::Init()
{
	// エネミークラスの初期化
	m_use = false;
//	m_w = TEXTURE_WIDTH;
//	m_h = TEXTURE_HEIGHT;
	m_pos = D3DXVECTOR2(0.0f, 0.0f);
//	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_texNo = 0;

//	countAnim = 0;
//	patternAnim = 0;

//	time = 0.0f;


//	for (int i = 0; i < ENEMY_TEX_PATTARN_MAX; i++)
//	{
//		CreateTexture(g_TextureName[i], &g_Texture[i]);
//	}

//	m_Tex[ENEMY_TEX_01].SetTexSize(TEXTURE_SIZE);	// 背景のサイズをセット
//	m_Tex[ENEMY_TEX_01].SetTexPos(SCREEN_CENTER);	// 背景の位置をセット


	// テクスチャの初期化
	CTexture::Init();
	SetTexSize(TEXTURE_SIZE);	// エネミーテクスチャのサイズをセット
	SetTexDivideX(TEXTURE_PATTERN_DIVIDE_X);	// 分割数をセット
	SetTexDivideY(TEXTURE_PATTERN_DIVIDE_Y);	// 分割数をセット

	// 重力の初期化
	//CGravity::Init();
	//SetGravityObjectSize(TEXTURE_SIZE);	// エネミーのサイズをセット
}

// エネミーのテクスチャ一括生成
void InitEnemy(void)
{
//	for (int i = 0; i < ENEMY_MAX; i++)
//	{
//		g_Enemy[i].Init();		// エネミーの数だけ呼び出すマン
//	}

	// テクスチャ生成
	for (int i = 0; i < ENEMY_TEX_PATTARN_MAX; i++)
	{
		CreateTexture(g_TextureName[i], &g_Texture[i]);
	}

}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemy::~CEnemy()
{

}

// エネミーのテクスチャ解放
void UninitEnemy()
{
	for (int i = 0; i < ENEMY_TEX_PATTARN_MAX; i++)
	{
		ReleaseTexture(&g_Texture[i]);	// 解放
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemy::Update(CMapchip Mapchip)
{
	if (m_use == true)	// このエネミーが使われている？
	{					// Yes
		// アニメーション  
	//	SetAnimWait(ANIM_WAIT);				// デフォルトのアニメーションWait値をセット
	//	UpdateAnimIndex(0, 5);				// 0-5番目の間をアニメーションする


		// 移動前のエネミーの座標を取得
		D3DXVECTOR2 OldPosEnemy = m_pos;

		// エネミーの移動AI
		/*
			条件：
				まずは右向きに "VALUE_MOVE"だけ右向きに移動させる。
				エネミーの右端の部分のマップチップ番号を調べて壁判定の番号の時は進行方向を逆（左向き）にする

				壁判定の番号　→　MAPCHIP_HIT_min と MAPCHIP_HIT_MAXの間の数字（つまり1~9番）【game.h 42行目】

				マップチップ番号を調べて、その値が
						" MAPCHIP_HIT_min <= 調べたマップチップ番号 && 調べたマップチップ番号 <= MAPCHIP_HIT_MAX "
							だったら進行方向を逆にする！！
		*/

		// 左向きに動かす
		{

		}

		// 右向きに動かす
		if (m_left == false)		// 左向きフラグが falseのとき（つまり、右向き移動）
		{
			m_pos.x += VALUE_MOVE;	// x軸の方向に動かす（右向き）
		}

		// マップチップの番号を調べる
		{
			/* Mapchip.GetMapchip( 調べたい座標 )　→　マップチップ番号わかる 
				右向きの時は、エネミー右端の座標
				左向きの時は、エネミー左端の座標

				右端の場合、（エネミーの中心座標 + エネミーの幅の半分の大きさ）＝ エネミーの右端
												GetTexSize().x / 2
			*/
	

		}

	}



#ifdef _DEBUG	// デバッグ情報を表示する
	//char *str = GetDebugStr();
	//sprintf(&str[strlen(str)], " EX:%.2f EY:%.2f", g_Enemy[0].Pos.x, g_Enemy[0].Pos.y);
	
#endif

}

//void UpdateEnemy(void)
//{
//	for (int i = 0; i < ENEMY_MAX; i++)
//	{
//		g_Enemy[i].Update();		// エネミーの数だけ呼び出すマン
//	}
//}


//=============================================================================
// 描画処理
//=============================================================================
void CEnemy::Draw(D3DXVECTOR2 ScrollPos)
{
	// 描画の前準備
//	PresetDraw2D();

	if (m_use == true)	// このエネミーが使われている？
	{					// Yes
		// 表示座標に変換
		SetTexPos(m_pos - ScrollPos);

		// エネミーの進行方向によって使用テクスチャを変える
		if (m_left) m_texNo = ENEMY_TEX_LEFT;	// 左向き
		else m_texNo = ENEMY_TEX_01;			// 右向き
		
		// 描画実行
		DrawTexture(g_Texture[m_texNo]);	// texNoのテクスチャを描画
	}

}

//void DrawEnemy(void)
//{
//	for (int i = 0; i < ENEMY_MAX; i++)
//	{
//		g_Enemy[i].Draw();			// エネミーの数だけ呼び出すマン
//	}
//}


// エネミーのセット
bool CEnemy::SetEnemy(D3DXVECTOR2 Pos, bool LeftFlag)
{
	// 既に使用中だったら失敗を返す
	if (m_use) return(false);

	// 使用中の時　→　使用フラグをtrueにしてエネミーを指定座標にセット
	m_pos = Pos;		// 座標セット
	m_left = LeftFlag;	// 動かす向きを指定
	m_use = true;		// 使用フラグをセット

	// 成功を返す
	return (true);
}

void CEnemy::KillEnemy()
{

}


//=============================================================================
// エネミー構造体の先頭アドレスを取得
//=============================================================================
//ENEMY *GetEnemy(void)
//{
//	return &g_Enemy[0];
//}


