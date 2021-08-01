//=============================================================================
//
// Mainヘッダー [main.h]
// Author : 杉本幸宏
//
//=============================================================================
#pragma once


#pragma warning(push)
#pragma warning(disable:4005)

#define _CRT_SECURE_NO_WARNINGS			// scanf のwarning防止
#include <stdio.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800		// 警告対処
#include "dinput.h"
#include "mmsystem.h"

#pragma warning(pop)


//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#pragma comment (lib, "d3d11.lib")		
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "d3dx11.lib")	
#pragma comment (lib, "d3dx9.lib")	
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")

// 各モードのインクルード
#include "opening.h"	// オープニング
#include "game.h"		// ゲーム


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH	(960)				// ウインドウの幅
#define SCREEN_HEIGHT	(540)				// ウインドウの高さ
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)	// ウインドウの中心Ｘ座標
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)	// ウインドウの中心Ｙ座標
#define SCREEN_CENTER	D3DXVECTOR2((float)SCREEN_CENTER_X, (float)SCREEN_CENTER_Y)	// ウィンドウの中心座標

#define NUM_VERTEX		(4)					// 頂点数

#define FPS_RATE		(60)				// FPS値（1秒ごとに描画・更新処理を行う回数）
#define NULL_SIZE		(1)
#define ZERO_VECTOR2	D3DXVECTOR2(0.0f, 0.0f)
#define DEFAULT_COLOR	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)

//*****************************************************************************
// enum
//*****************************************************************************
typedef enum
{
	MODE_NONE = -1,		// モード無し

	MODE_OPENING = 0,	// オープニング画面
	MODE_TITLE,			// タイトル画面
	MODE_TUTORIAL,		// ゲーム説明画面
	MODE_GAME,			// ゲーム画面
	MODE_RESULT,		// リザルト画面

	MODE_MAX
} MODE;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CMode
{
public:
	CMode();	// コンストラクタ
	~CMode();	// デストラクタ

	//------------------- メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();

	//------------------- ゲッター関数
	MODE GetMode();

	//------------------- セッター関数
	void SetMode(MODE mode);

	//------------------- 各モードのインスタンス
	CModeGame m_GameMode;		// ゲーム画面
	CModeOpening m_OpeningMode; // オープニング画面

private:
	MODE m_Mode;	// モードの状態を格納する変数
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
long GetMousePosX(void);
long GetMousePosY(void);
char *GetDebugStr(void);

//------------------- 各インスタンスへのアクセス用関数
CModeGame* GetGame();	// ゲームモードのインスタンスを取得

//------------------- メンバ変数のアクセス用グローバル関数
void RequestSetMode(MODE mode);					// セットモード
//MODE RequestGetMode();
//void RequestSetScrollPosition(D3DXVECTOR2 Pos);	// スクロール座標のセット


//------------------- ファイル関数
int LoadCsvFile(const char* pCsvFileName, char* &pFirst, int MaxCharCell, char* DivMark);
int DivideString(const char* String, int* retCol, int* retRow, char* DivMark);
int SerchWordOffset(const char* String, const char SingleWord);

//------------------- その他関数


