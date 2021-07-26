//=============================================================================
//
// Main処理 [main.cpp]
// Author : 杉本 幸宏
//
//=============================================================================
#include "main.h"

#include "title.h"		// タイトル画面
#include "opening.h"	// オープニング画面
#include "tutorial.h"	// チュートリアル画面
//#include "game.h"		// ゲーム画面	【クラス化して、main.h の方でインクルードしてる】
#include "result.h"		// リザルト画面

#include "input.h"		// キー・ゲームパッド入力処理
#include "renderer.h"	// レンダリング処理
#include "camera.h"		// カメラ
#include "fade.h"		// フェード処理
#include "sound.h"		// サウンド
#include "debugproc.h"	// デバック

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME			"AppClass"				// ウインドウのクラス名
#define WINDOW_NAME			"GP23 DirectX11"		// ウインドウのキャプション名

#ifndef _DEBUG
	#define START_MODE			(MODE_OPENING)			// 起動時のモード
#endif // !_DEBUG

#ifdef _DEBUG
#define START_MODE			(MODE_GAME)			// 起動時のモード
#endif // _DEBUG

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
//void Uninit(void);
//void Draw(void);
//void Update(void);


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
//MODE g_Mode = START_MODE;

CMode g_aMode;

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
	if(FAILED(g_aMode.Init(hInstance, hWnd, true)))
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
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], "  CurrentMode:%d", g_aMode.GetMode());

#endif
				// テキストのセット
				SetWindowText(hWnd, g_DebugStr);

				g_aMode.Update();			// 更新処理
				g_aMode.Draw();				// 描画処理

				dwFrameCount++;		// 処理回数のカウントを加算
			}
		}
	}
	
	timeEndPeriod(1);				// 分解能を戻す

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 終了処理
	g_aMode.Uninit();

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
// コンストラクタ・デストラクタ
//=============================================================================
CMode::CMode()	// コンストラクタ
{
	m_Mode = MODE_NONE;		// モード無しで初期化
}

CMode::~CMode()	// デストラクタ
{
	
}


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMode::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
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
	g_aMode.SetMode(START_MODE);

	//------------------- モードに応じた初期化
//	if (g_aMode.GetMode() == MODE_TITLE) InitTitle();			 	// タイトル画面の初期化処理
//	else if (g_aMode.GetMode() == MODE_TUTORIAL) InitTutorial();	// オープニング画面の初期化処理
//	else if(g_aMode.GetMode() == MODE_TUTORIAL) InitTutorial();		// チュートリアル画面の初期化処理
//	else if (g_aMode.GetMode() == MODE_GAME) m_GameMode.Init();		// ゲーム画面の初期化処理
//	else if (g_aMode.GetMode() == MODE_RESULT) InitResult();		// リザルト画面の初期化処理
  
	return S_OK;
}



//=============================================================================
// 終了処理
//=============================================================================
void CMode::Uninit(void)
{
	//------------------- モードに応じたメモリ解放
	if (g_aMode.GetMode() == MODE_TITLE) UninitTitle();				// タイトル画面の終了処理
	if (g_aMode.GetMode() == MODE_OPENING) UninitOpening();			// オープニング画面の終了処理
	else if(g_aMode.GetMode() == MODE_TUTORIAL) UninitTutorial();	// チュートリアル画面の終了処理
	else if (g_aMode.GetMode() == MODE_GAME) m_GameMode.Uninit();	// ゲーム画面の終了処理
	else if (g_aMode.GetMode() == MODE_RESULT) UninitResult();		// リザルト画面の終了処理

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
void CMode::Update(void)
{
	// キー・ゲームパッドの更新処理
	UpdateInput();

	// カメラの更新処理
	UpdateCamera();

	//------------------- モードに応じた更新処理
	switch (g_aMode.GetMode())
	{
	case MODE_OPENING:
		UpdateOpening();
		break;

	case MODE_TITLE:
		UpdateTitle();
		break;

	case MODE_TUTORIAL:
		UpdateTutorial();
		break;

	case MODE_GAME:
		m_GameMode.Update();
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
void CMode::Draw(void)
{
	// バックバッファクリア
	Clear();

	// カメラをセット
	SetCamera();

	// 2D描画なので深度無効
	SetDepthEnable(false);
	
	//------------------- モードに応じた描画処理
	switch (g_aMode.GetMode())
	{
	case MODE_OPENING:
		DrawOpening();
		break;

	case MODE_TITLE:
		DrawTitle();
		break;

	case MODE_TUTORIAL:
		DrawTutorial();
		break;

	case MODE_GAME:
		m_GameMode.Draw();
		break;

	case MODE_RESULT:
		DrawResult();
		break;

	default:
		break;
	}

	// フェードの描画処理
	DrawFade();

#ifdef _DEBUG
	// デバッグ表示
	DrawDebugProc();
#endif


	// バックバッファ、フロントバッファ入れ替え
	Present();
}



//=============================================================================
// セッター関数
//=============================================================================
// モードの設定
void CMode::SetMode(MODE mode)
{
	//------------------- モードを変える前にメモリを解放
	if(g_aMode.GetMode() == MODE_TITLE) UninitTitle();				// タイトル画面の終了処理
	if (g_aMode.GetMode() == MODE_OPENING) UninitOpening();			// オープニング画面の終了処理
	else if(g_aMode.GetMode() == MODE_TUTORIAL) UninitTutorial();	// チュートリアル画面の終了処理
	else if(g_aMode.GetMode() == MODE_GAME) m_GameMode.Uninit();	// ゲーム画面の終了処理
	else if(g_aMode.GetMode() == MODE_RESULT) UninitResult();		// リザルト画面の終了処理

	//------------------- 次のモードのセット
	m_Mode = mode;

	//------------------- セットしたモードに応じた初期化処理を行う
	switch (m_Mode)
	{
	case MODE_OPENING:
		// オープニング画面の初期化
		InitOpening();
		break;

	case MODE_TITLE:
		// タイトル画面の初期化
		InitTitle();
		break;

	case MODE_TUTORIAL:
		// ゲーム画面の初期化
		InitTutorial();
		break;

	case MODE_GAME:
		// ゲーム画面の初期化
		m_GameMode.Init();
		break;

	case MODE_RESULT:
		// リザルト画面の初期化
		InitResult();
		break;

	case MODE_MAX:
		break;
	}
}



//=============================================================================
// ゲッター関数
//=============================================================================
// 現在のモードを取得
MODE CMode::GetMode()
{
	return m_Mode;
}

//------------------- 各モードのインスタンスへのゲッター関数
// ゲーム
CModeGame* GetGame()
{
	return &(g_aMode.m_GameMode);
}


//=============================================================================
// CModeのメンバ変数へアクセスできるグローバル関数
//=============================================================================
// モードのセット 【main】
void RequestSetMode(MODE mode)
{
	g_aMode.SetMode(mode);
}

// スクロール座標のセット 【game】
//void RequestSetScrollPosition(D3DXVECTOR2 Pos)
//{
//	g_aMode.m_GameMode.SetScrollPosition(Pos);
//}



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




/*******************************************************************************
関数名	:	void LoadCsvData( void )
引数		:	読み込むファイル名, 作成データの先頭アドレスを格納するポインタ, 1つのセルごとの最大文字数, 区切り文字（指定無ければNULL）
返り値	:	格納データの総文字数。エラー時は「-1」, 読み込み失敗エラー「-2」
説明	:	カンマ区切りのcsvファイルを、文字列のまま読み込む
			"new演算子"でメモリを確保しているため、使った後は必ず"delete"すること
*******************************************************************************/
#define	MAX_COLUMN			(64)								// セルの最大列数<横の数>
#define	MAX_ROW				(64)								// セルの最大行数<縦の数>
#define	SizeOfCell(wordCnt)	(sizeof(char) * wordCnt)			// 1つのセルに使うchar型メモリ
#define	SizeOfLine(wordCnt)	(SizeOfCell(wordCnt) * MAX_COLUMN)	// 1行あたりに使うchar型メモリ
#define	MAX_SIZE(wordCnt)	(SizeOfLine(wordCnt) * MAX_ROW)		// 使用する最大char型メモリ（= 1つのcsvファイルに記載されている最大文字列）
#define	CommentsSymbol		'#'									// コメント記号
#define	DefaultDivMark		"#"									// デフォルトの区切り記号

int LoadCsvFile(const char* pCsvFileName, char* &pFirst, int MaxCharCell, char* DivMark)
{
	FILE*	csvFile = fopen(pCsvFileName, "r");					// ファイルのオープン<fclose記載済み>

	// 読み込み失敗時(エラーチェック)
	if (csvFile == NULL) {
	//	fclose(csvFile);
	//	printf("オープンエラー！");
		return -2;	// 読み込み失敗エラーを返して終了
	}

	// 成功したらロード
	// 区切り記号に指定が無かった場合、"#"にする
	if (DivMark == NULL)
	{
		DivMark = DefaultDivMark;
	}

	// 動的配列の生成
	char*	pTmpArray = NULL;
	pTmpArray = (char*)malloc(MAX_SIZE(MaxCharCell) + NULL_SIZE);		// char型配列を使用する最大メモリ数分だけ確保<free記載済み>
	if (pTmpArray == NULL) {	// 確保できなかったら
		fclose(csvFile);		// ファイルのクローズ
		return -1;				// エラー出して終了
	}

	// 初期化
	memset(pTmpArray, '\0', MAX_SIZE(MaxCharCell) + NULL_SIZE);

	// ファイルへのアクセスに使用するchar型変数
	char	OneLineStr[1024] = { NULL };	// 読み取るファイルの、一行分の文字列を格納するためのchar型配列
	char*	pDivideStr = NULL;				// str配列へのアクセス用char型ポインタ

	// 読み込んだデータの数をカウントする変数
	//int		storeCharCnt = 0;

	// 配列に数値を格納する作業
	while (fgets(&OneLineStr[0], (MaxCharCell * MAX_COLUMN), csvFile) != NULL)	// 読み取るファイルの、一行分の文字列を格納
	{	// 一行単位の読み取り作業を、ファイル終了まで繰り返す
		pDivideStr = strtok(OneLineStr, ",");	// １列目の文字列を取り出す
		if (pDivideStr == NULL) break;			// NULLならループを抜ける

		do
		{
			int comOffset = SerchWordOffset(pDivideStr, CommentsSymbol);	// コメント記号の位置を取得

			// コメント記号が先頭にあるときはそのセルに書かれている内容は飛ばす
			if (comOffset != 0 && pDivideStr != NULL)
			{	// データの格納
				char*	pBuf = NULL;

				int		bufNum = MaxCharCell + NULL_SIZE;	// pBufの要素数
				pBuf = new char[bufNum];					// 一時的な文字列コピー用の配列<delete記載済み>
				memset(pBuf, '\0', bufNum);					// 初期化

				// pDivideStrの文字列をコピー
				strncpy_s(pBuf, bufNum, pDivideStr, MaxCharCell);

				// 取り出した文字列の文字数を取得
				int		len = (int)strlen(pBuf);
				// コメント記号以下の文字は、全て"\0"に置き換える（→コメント以下のものは格納しないようにするため）
				if (comOffset != -1) {						// コメント記号が書かれていない場合は行わない

					//		コメント記号の場所から	  コメント記号以下の文字数分だけ置き換える
					memset(pBuf + comOffset, '\0', (len - comOffset));

					len = (int)strlen(pBuf);				// 置き換え後の文字数を入れる
				}

				strncat_s(pTmpArray, MAX_SIZE(MaxCharCell), pBuf, MaxCharCell - sizeof(DivMark));	// 区切り記号を入れられるように、pBufに空きを作る
				strncat_s(pTmpArray, MAX_SIZE(MaxCharCell), DivMark, sizeof(DivMark));				// 区切り記号を語尾につける
			//	storeCharCnt += (int)(strlen(pBuf) + strlen(DivMark));								// 文字数のカウント

				if (pBuf != NULL) delete[] pBuf;
			}

			pDivideStr = strtok(NULL, ",");					// 2列目以降の文字列を取り出す
		} while (pDivideStr != NULL);						// 取り出す文字列がなくなるまで繰り返し

	}

	// 配列を最低限のメモリサイズだけコピー
	size_t	BufSize = strlen(pTmpArray);					// データの総メモリサイズ(文字数)を取得
	pFirst = new char[(int)BufSize + NULL_SIZE];			// メモリを必要分だけ新たに確保(NULLの格納を考慮)
	memset(pFirst, '\0', BufSize + NULL_SIZE);				// 初期化

	// 必要分だけコピー
	strncpy(pFirst, pTmpArray, BufSize);

	// mallocで確保した"pTmpArray"のメモリを解放
	free(pTmpArray);

	// ファイルのクローズかつエラーチェック
	if (fclose(csvFile) == EOF) {
		// エラー時の処理
	//	printf("クローズドエラー！");
		//	exit(1);			// クローズ失敗時、OSに「1」を返して正常終了させる
		return -1;
	}

	return (int)BufSize;	// 総文字数を返す
	//return storeCharCnt;
}


/*******************************************************************************
* 関数名	: int SerchWordOffset(char* String, const char SingleWord)
* 引数		: 文字列, 指定文字
* 返り値	: 指定文字の、先頭から数えたときの位置		見つからなかった時・エラー : -1
* 説明		: 文字列"String"の中から、指定文字が先頭からどの位置にあるのかを返す
*******************************************************************************/
int SerchWordOffset(const char* String, const char SingleWord)
{
	// 文字列が見つからない時
	if (String == NULL) return -1;	// エラーを返す

	// Bufに記載された文字列を先頭から一文字ずつ判別する
	// 継続条件:Stringの終端まで 変数の更新内容:「String」が指すアドレスと「offset」の値をそれぞれ加算
	for (int offset = 0; *String; ++String, ++offset)
	{
		// 1文字格納用のchar型配列
		char singleWord[2] = { "\0" };

		// １文字を抽出
		strncat(singleWord, String, 1);

		// 抽出した１文字によって処理を変える
		if (strcmp(singleWord, &SingleWord) == 0)
		{	// 指定した文字列が見つかれば、その位置を返す
			return offset;
		}

	}

	return -1;	// 見つからなかった時、-1を返す
}


/*******************************************************************************
* 関数名		:	int DivideString(const char* String, int* Col, int* Row, char* DivMark)
* 引数		:	座標番号, 最大列数を格納する番地, 行数を格納する番地, 区切り記号
* 返り値		:	成功 → 1		失敗 → 0
* 説明		:	読み込んだ文字列の縦横の分割数を、"\n"(改行コード)から求める
********************************************************************************/
int DivideString(const char* String, int* retCol, int* retRow, char* DivMark)
{
	// 文字列が見つからない時(エラーチェック)
	if (String == NULL) return 0;

	// char型ポインタ
	char*	Buf;

	// 「String」の文字列を「Buf」にコピー
	{
		int	BufSize = (int)strlen(String);			// stringのメモリ数を出す

		int		idxNum = BufSize + NULL_SIZE;		// 必要な要素数
		Buf = new char[idxNum];						// 文字型配列を必要メモリ分用意
		memset(Buf, '\0', sizeof(char) * idxNum);	// 初期化

		strncpy(Buf, String, BufSize);				// 文字列のコピー
	}

	int		ColCnt = 0, RowCnt = 0;					// 行と列それぞれのカウント用変数
	int		MaxCol = -1;							// 最大列数の比較用の変数

	// 一列目の文字列を格納
	char*	divideBuf = NULL;						// 区切った文字列を示すポインタ
	char*	p = NULL;								// strtok_s用のポインタ
	divideBuf = strtok_s(&Buf[0], DivMark, &p);

	do
	{
		// 列数のカウント
		ColCnt++;

		if (SerchWordOffset(divideBuf, '\n') >= 0)	// 改行コードがあったら
		{
			RowCnt++;								// 次の行へ行くので、行数をプラス

			if (ColCnt > MaxCol) MaxCol = ColCnt;	// 最大数を超えていたら、最大列数を更新
			ColCnt = 0;								// 列数カウントのリセット
		}

		divideBuf = strtok_s(NULL, DivMark, &p);	// ２列目以降の文字列を取りだす
	} while (divideBuf != NULL);					// divideBufに入る文字列が無くなるまで繰り返し

	// 算出したあたいを返す
	*retRow = RowCnt;
	*retCol = MaxCol;

	// メモリの解放
	if (Buf != NULL) delete[] Buf;

	return 1;
}