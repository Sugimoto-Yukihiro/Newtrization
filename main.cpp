//=============================================================================
//
// Main処理 [main.cpp]
// Author : 杉本 幸宏
//
// エネミーとプレイヤー追加したら、SetModeの最後の方のコメントアウト解除しとく
//=============================================================================
#include "main.h"

#include "title.h"		// タイトル画面
#include "game.h"		// ゲーム画面
#include "result.h"		// リザルト画面

#include "input.h"		// キー・ゲームパッド入力処理
#include "renderer.h"	// レンダリング処理
#include "camera.h"		// カメラ
#include "fade.h"		// フェード処理
#include "sound.h"		// サウンド

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME			"AppClass"				// ウインドウのクラス名
#define WINDOW_NAME			"GP23 DirectX11"		// ウインドウのキャプション名

#define START_MODE			(MODE_TITLE)

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);


//*****************************************************************************
// グローバル変数:
//*****************************************************************************
long g_MouseX = 0;
long g_MouseY = 0;

#ifdef _DEBUG
int		g_CountFPS;							// FPSカウンタ
char	g_DebugStr[2048] = WINDOW_NAME;		// デバッグ文字表示用
#endif

// 起動時の画面を初期値として設定
MODE g_Mode = START_MODE;

//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	// 時間計測用
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	
	WNDCLASSEX	wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW+1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND		hWnd;
	MSG			msg;
	
	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
	hWnd = CreateWindow(CLASS_NAME,
						WINDOW_NAME,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,																		// ウィンドウの左座標
						CW_USEDEFAULT,																		// ウィンドウの上座標
						SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME)*2,									// ウィンドウ横幅
						SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME)*2+GetSystemMetrics(SM_CYCAPTION),	// ウィンドウ縦幅
						NULL,
						NULL,
						hInstance,
						NULL);

#ifndef _DEBUG
	{
		int id = MessageBox(NULL, "Windowモードでプレイしますか？", "起動モード", MB_YESNOCANCEL | MB_ICONQUESTION);
		switch (id)
		{
		case IDYES:		// YesならWindowモードで起動
			break;
		case IDNO:		// Noならフルスクリーンモードで起動
			break;
		case IDCANCEL:	// CANCEL
		default:		// またはそれ以外なら終了
			return -1;
			break;
		}
	}
#endif // !_DEBUG

	// DirectXの初期化(ウィンドウを作成してから行う)
	if(FAILED(Init(hInstance, hWnd, true)))
	{
		return -1;
	}

	// フレームカウント初期化
	timeBeginPeriod(1);	// 分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// システム時刻をミリ秒単位で取得
	dwCurrentTime = dwFrameCount = 0;
	
	// ウインドウの表示(Init()の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// メッセージループ
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();					// システム時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 1秒ごとに実行
			{
#ifdef _DEBUG
				g_CountFPS = dwFrameCount;
#endif
				dwFPSLastTime = dwCurrentTime;				// FPSを測定した時刻を保存
				dwFrameCount = 0;							// カウントをクリア
			}

			// 1/60秒ごとに実行
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / FPS_RATE))
			{
				dwExecLastTime = dwCurrentTime;	// 処理した時刻を保存

				// WINDOW_NAMEの表示
				wsprintf(g_DebugStr, WINDOW_NAME);

#ifdef _DEBUG	// デバッグ版の時だけ表示するやつ
				// FPSを表示
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], " FPS:%d", g_CountFPS);
				// マウス座標の表示
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], " MX:%d MY:%d", GetMousePosX(), GetMousePosY());
				// 現在のモードの表示
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], "  CurrentMode:%d", GetMode());

#endif
				// テキストのセット
				SetWindowText(hWnd, g_DebugStr);

				Update();			// 更新処理
				Draw();				// 描画処理

				dwFrameCount++;		// 処理回数のカウントを加算
			}
		}
	}
	
	timeEndPeriod(1);				// 分解能を戻す

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 終了処理
	Uninit();

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch( message )
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:					// [ESC]キーが押された
			DestroyWindow(hWnd);		// ウィンドウを破棄するよう指示する
			break;
		}
		break;

	// マウスが動いた時の処理
	case WM_MOUSEMOVE:
		g_MouseX = LOWORD(lParam);		// マウスのX座標を格納
		g_MouseY = HIWORD(lParam);		// マウスのY座標を格納
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// レンダリング処理の初期化
	InitRenderer(hInstance, hWnd, bWindow);

	// フェード処理の初期化
	InitFade();

	// カメラ処理の初期化
	InitCamera();

	// 入力処理の初期化
	InitInput(hInstance, hWnd);

	// サウンドの初期化
	InitSound(hWnd);

	// 最初のモードをセット
	g_Mode = START_MODE;

	//------------------- モードに応じた初期化
	if (g_Mode == MODE_TITLE) InitTitle();				// タイトル画面の終了処理
//	else if(g_Mode == MODE_TUTORIAL) InitTutorial();	// チュートリアル画面の終了処理
	else if (g_Mode == MODE_GAME) InitGame();			// ゲーム画面の終了処理
	else if (g_Mode == MODE_RESULT) InitResult();		// リザルト画面の終了処理

	return S_OK;
}


//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	//------------------- モードに応じたメモリ解放
	if (g_Mode == MODE_TITLE) UninitTitle();				// タイトル画面の終了処理
//	else if(g_Mode == MODE_TUTORIAL) UninitTutorial();	// チュートリアル画面の終了処理
	else if (g_Mode == MODE_GAME) UninitGame();			// ゲーム画面の終了処理
	else if (g_Mode == MODE_RESULT) UninitResult();		// リザルト画面の終了処理

	// サウンドの終了処理
	UninitSound();

	// キー・ゲームパッドの終了処理
	UninitInput();

	// カメラの終了処理
	UninitCamera();

	// フェード処理の終了処理
	UninitFade();

	// レンダリングの終了処理
	UninitRenderer();
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	// キー・ゲームパッドの更新処理
	UpdateInput();

	// カメラの更新処理
	UpdateCamera();

	//------------------- モードに応じた更新処理
	switch (g_Mode)
	{
	case MODE_TITLE:
		UpdateTitle();
		break;

	case MODE_TUTORIAL:
	//	UpdateTutorial();
		break;

	case MODE_GAME:
		UpdateGame();
		break;

	case MODE_RESULT:
		UpdateResult();
		break;

	default:
		break;
	}

	// フェードの更新処理
	UpdateFade();

}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファクリア
	Clear();

	// カメラをセット
	SetCamera();

	// 2D描画なので深度無効
	SetDepthEnable(false);
	
	//------------------- モードに応じた描画処理
	switch (g_Mode)
	{
	case MODE_TITLE:
		DrawTitle();
		break;

	case MODE_TUTORIAL:
	//	DrawTutorial();
		break;

	case MODE_GAME:
		DrawGame();
		break;

	case MODE_RESULT:
		DrawResult();
		break;

	default:
		break;
	}

	// フェードの描画処理
	DrawFade();

	// バックバッファ、フロントバッファ入れ替え
	Present();
}


//=============================================================================
// モードの設定
//=============================================================================
void SetMode(MODE mode)
{
	//------------------- モードを変える前にメモリを解放しちゃう
	if(g_Mode == MODE_TITLE) UninitTitle();				// タイトル画面の終了処理
//	else if(g_Mode == MODE_TUTORIAL) UninitTutorial();	// チュートリアル画面の終了処理
	else if(g_Mode == MODE_GAME) UninitGame();			// ゲーム画面の終了処理
	else if(g_Mode == MODE_RESULT) UninitResult();		// リザルト画面の終了処理

	//------------------- 次のモードのセット
	g_Mode = mode;

	//------------------- セットしたモードに応じた初期化処理を行う
	switch (g_Mode)
	{
	case MODE_TITLE:
		// タイトル画面の初期化
		InitTitle();
		break;

	case MODE_TUTORIAL:
		// ゲーム画面の初期化
	//	InitTutorial();
		break;

	case MODE_GAME:
		// ゲーム画面の初期化
		InitGame();
		break;

	case MODE_RESULT:
		// リザルト画面の初期化
		InitResult();
		break;

	case MODE_MAX:
		break;
	}
}


long GetMousePosX(void)
{
	return g_MouseX;
}


long GetMousePosY(void)
{
	return g_MouseY;
}


#ifdef _DEBUG
char* GetDebugStr(void)
{
	return g_DebugStr;
}
#endif

// 現在のモードを取得
MODE GetMode(void)
{
	return g_Mode;
}