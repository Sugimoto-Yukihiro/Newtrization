//=============================================================================
//
// Main���� [main.cpp]
// Author : ���{ �K�G
//
// �G�l�~�[�ƃv���C���[�ǉ�������ASetMode�̍Ō�̕��̃R�����g�A�E�g�������Ƃ�
//=============================================================================
#include "main.h"

#include "title.h"		// �^�C�g�����
#include "game.h"		// �Q�[�����
#include "result.h"		// ���U���g���

#include "input.h"		// �L�[�E�Q�[���p�b�h���͏���
#include "renderer.h"	// �����_�����O����
#include "camera.h"		// �J����
#include "fade.h"		// �t�F�[�h����
#include "sound.h"		// �T�E���h

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME			"AppClass"				// �E�C���h�E�̃N���X��
#define WINDOW_NAME			"GP23 DirectX11"		// �E�C���h�E�̃L���v�V������

#define START_MODE			(MODE_TITLE)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
//void Uninit(void);
//void Draw(void);
//void Update(void);


//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
long g_MouseX = 0;
long g_MouseY = 0;

#ifdef _DEBUG
int		g_CountFPS;							// FPS�J�E���^
char	g_DebugStr[2048] = WINDOW_NAME;		// �f�o�b�O�����\���p
#endif

// �N�����̉�ʂ������l�Ƃ��Đݒ�
//MODE g_Mode = START_MODE;

CMode g_aMode;

//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	// ���Ԍv���p
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
	
	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindow(CLASS_NAME,
						WINDOW_NAME,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,																		// �E�B���h�E�̍����W
						CW_USEDEFAULT,																		// �E�B���h�E�̏���W
						SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME)*2,									// �E�B���h�E����
						SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME)*2+GetSystemMetrics(SM_CYCAPTION),	// �E�B���h�E�c��
						NULL,
						NULL,
						hInstance,
						NULL);

#ifndef _DEBUG
	{
		int id = MessageBox(NULL, "Window���[�h�Ńv���C���܂����H", "�N�����[�h", MB_YESNOCANCEL | MB_ICONQUESTION);
		switch (id)
		{
		case IDYES:		// Yes�Ȃ�Window���[�h�ŋN��
			break;
		case IDNO:		// No�Ȃ�t���X�N���[�����[�h�ŋN��
			break;
		case IDCANCEL:	// CANCEL
		default:		// �܂��͂���ȊO�Ȃ�I��
			return -1;
			break;
		}
	}
#endif // !_DEBUG

	// DirectX�̏�����(�E�B���h�E���쐬���Ă���s��)
	if(FAILED(g_aMode.Init(hInstance, hWnd, true)))
	{
		return -1;
	}

	// �t���[���J�E���g������
	timeBeginPeriod(1);	// ����\��ݒ�
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// �V�X�e���������~���b�P�ʂŎ擾
	dwCurrentTime = dwFrameCount = 0;
	
	// �E�C���h�E�̕\��(Init()�̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// ���b�Z�[�W���[�v
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();					// �V�X�e���������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 1�b���ƂɎ��s
			{
#ifdef _DEBUG
				g_CountFPS = dwFrameCount;
#endif
				dwFPSLastTime = dwCurrentTime;				// FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;							// �J�E���g���N���A
			}

			// 1/60�b���ƂɎ��s
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / FPS_RATE))
			{
				dwExecLastTime = dwCurrentTime;	// ��������������ۑ�

				// WINDOW_NAME�̕\��
				wsprintf(g_DebugStr, WINDOW_NAME);

#ifdef _DEBUG	// �f�o�b�O�ł̎������\��������
				// FPS��\��
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], " FPS:%d", g_CountFPS);
				// �}�E�X���W�̕\��
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], " MX:%d MY:%d", GetMousePosX(), GetMousePosY());
				// ���݂̃��[�h�̕\��
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], "  CurrentMode:%d", g_aMode.GetMode());

#endif
				// �e�L�X�g�̃Z�b�g
				SetWindowText(hWnd, g_DebugStr);

				g_aMode.Update();			// �X�V����
				g_aMode.Draw();				// �`�揈��

				dwFrameCount++;		// �����񐔂̃J�E���g�����Z
			}
		}
	}
	
	timeEndPeriod(1);				// ����\��߂�

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �I������
	g_aMode.Uninit();

	return (int)msg.wParam;
}



//=============================================================================
// �v���V�[�W��
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
		case VK_ESCAPE:					// [ESC]�L�[�������ꂽ
			DestroyWindow(hWnd);		// �E�B���h�E��j������悤�w������
			break;
		}
		break;

	// �}�E�X�����������̏���
	case WM_MOUSEMOVE:
		g_MouseX = LOWORD(lParam);		// �}�E�X��X���W���i�[
		g_MouseY = HIWORD(lParam);		// �}�E�X��Y���W���i�[
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}



//=============================================================================
// ����������
//=============================================================================
HRESULT CMode::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �����_�����O�����̏�����
	InitRenderer(hInstance, hWnd, bWindow);

	// �t�F�[�h�����̏�����
	InitFade();

	// �J���������̏�����
	InitCamera();

	// ���͏����̏�����
	InitInput(hInstance, hWnd);

	// �T�E���h�̏�����
	InitSound(hWnd);

	// �ŏ��̃��[�h���Z�b�g
	g_Mode = START_MODE;

	//------------------- ���[�h�ɉ�����������
	if (g_Mode == MODE_TITLE) InitTitle();				// �^�C�g����ʂ̏���������
//	else if(g_Mode == MODE_TUTORIAL) InitTutorial();	// �`���[�g���A����ʂ̏���������
	else if (g_Mode == MODE_GAME) m_GameMode.Init();	// �Q�[����ʂ̏���������
	else if (g_Mode == MODE_RESULT) InitResult();		// ���U���g��ʂ̏���������

	return S_OK;
}



//=============================================================================
// �I������
//=============================================================================
void CMode::Uninit(void)
{
	//------------------- ���[�h�ɉ��������������
	if (g_Mode == MODE_TITLE) UninitTitle();			// �^�C�g����ʂ̏I������
//	else if(g_Mode == MODE_TUTORIAL) UninitTutorial();	// �`���[�g���A����ʂ̏I������
	else if (g_Mode == MODE_GAME) m_GameMode.Uninit();	// �Q�[����ʂ̏I������
	else if (g_Mode == MODE_RESULT) UninitResult();		// ���U���g��ʂ̏I������

	// �T�E���h�̏I������
	UninitSound();

	// �L�[�E�Q�[���p�b�h�̏I������
	UninitInput();

	// �J�����̏I������
	UninitCamera();

	// �t�F�[�h�����̏I������
	UninitFade();

	// �����_�����O�̏I������
	UninitRenderer();
}



//=============================================================================
// �X�V����
//=============================================================================
void CMode::Update(void)
{
	// �L�[�E�Q�[���p�b�h�̍X�V����
	UpdateInput();

	// �J�����̍X�V����
	UpdateCamera();

	//------------------- ���[�h�ɉ������X�V����
	switch (g_Mode)
	{
	case MODE_TITLE:
		UpdateTitle();
		break;

	case MODE_TUTORIAL:
	//	UpdateTutorial();
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

	// �t�F�[�h�̍X�V����
	UpdateFade();

}



//=============================================================================
// �`�揈��
//=============================================================================
void CMode::Draw(void)
{
	// �o�b�N�o�b�t�@�N���A
	Clear();

	// �J�������Z�b�g
	SetCamera();

	// 2D�`��Ȃ̂Ő[�x����
	SetDepthEnable(false);
	
	//------------------- ���[�h�ɉ������`�揈��
	switch (g_Mode)
	{
	case MODE_TITLE:
		DrawTitle();
		break;

	case MODE_TUTORIAL:
	//	DrawTutorial();
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

	// �t�F�[�h�̕`�揈��
	DrawFade();

	// �o�b�N�o�b�t�@�A�t�����g�o�b�t�@����ւ�
	Present();
}



//=============================================================================
// �Z�b�^�[�֐�
//=============================================================================
// ���[�h�̐ݒ�
void CMode::SetMode(MODE mode)
{
	//------------------- ���[�h��ς���O�Ƀ���������������Ⴄ
	if(g_Mode == MODE_TITLE) UninitTitle();				// �^�C�g����ʂ̏I������
//	else if(g_Mode == MODE_TUTORIAL) UninitTutorial();	// �`���[�g���A����ʂ̏I������
	else if(g_Mode == MODE_GAME) m_GameMode.Uninit();			// �Q�[����ʂ̏I������
	else if(g_Mode == MODE_RESULT) UninitResult();		// ���U���g��ʂ̏I������

	//------------------- ���̃��[�h�̃Z�b�g
	g_Mode = mode;

	//------------------- �Z�b�g�������[�h�ɉ������������������s��
	switch (g_Mode)
	{
	case MODE_TITLE:
		// �^�C�g����ʂ̏�����
		InitTitle();
		break;

	case MODE_TUTORIAL:
		// �Q�[����ʂ̏�����
	//	InitTutorial();
		break;

	case MODE_GAME:
		// �Q�[����ʂ̏�����
		m_GameMode.Init();
		break;

	case MODE_RESULT:
		// ���U���g��ʂ̏�����
		InitResult();
		break;

	case MODE_MAX:
		break;
	}
}



//=============================================================================
// �Q�b�^�[�֐�
//=============================================================================
// ���݂̃��[�h���擾
MODE CMode::GetMode()
{
	return g_Mode;
}

//------------------- �e���[�h�̃C���X�^���X�ւ̃Q�b�^�[�֐�
// �Q�[��
CModeGame* GetGame()
{
	return &(g_aMode.m_GameMode);
}


//=============================================================================
// CMode�̃����o�ϐ��փA�N�Z�X�ł���O���[�o���֐�
//=============================================================================
// ���[�h�̃Z�b�g
void RequestSetMode(MODE mode)
{
	g_aMode.SetMode(mode);
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




/*******************************************************************************
�֐���	:	void LoadCsvData( void )
����	:	�ǂݍ��ރt�@�C����, �쐬�f�[�^�̐擪�A�h���X���i�[����|�C���^, 1�̃Z�����Ƃ̍ő啶����, ��؂蕶���i�w�薳�����NULL�j
�Ԃ�l	:	�i�[�f�[�^�̑��������B�G���[���́u-1�v
����	:	�J���}��؂��csv�t�@�C�����A������̂܂ܓǂݍ���
			"new���Z�q"�Ń��������m�ۂ��Ă��邽�߁A�g������͕K��"delete"���邱��
*******************************************************************************/
#define	MAX_COLUMN			(64)								// �Z���̍ő��<���̐�>
#define	MAX_ROW				(64)								// �Z���̍ő�s��<�c�̐�>
#define	SizeOfCell(wordCnt)	(sizeof(char) * wordCnt)			// 1�̃Z���Ɏg��char�^������
#define	SizeOfLine(wordCnt)	(SizeOfCell(wordCnt) * MAX_COLUMN)	// 1�s������Ɏg��char�^������
#define	MAX_SIZE(wordCnt)	(SizeOfLine(wordCnt) * MAX_ROW)		// �g�p����ő�char�^�������i= 1��csv�t�@�C���ɋL�ڂ���Ă���ő啶����j
#define	CommentsSymbol		'#'									// �R�����g�L��
#define	DefaultDivMark		"#"									// �f�t�H���g�̋�؂�L��

int LoadCsvFile(const char* pCsvFileName, char* &pFirst, int MaxCharCell, char* DivMark)
{
	FILE*	csvFile = fopen(pCsvFileName, "r");					// �t�@�C���̃I�[�v��<fclose�L�ڍς�>

	// �ǂݍ��ݎ��s��(�G���[�`�F�b�N)
	if (csvFile == NULL) {
		fclose(csvFile);
		printf("�I�[�v���G���[�I");
		return -1;	// �G���[��Ԃ��ďI��
	}

	// ���������烍�[�h
	// ��؂�L���Ɏw�肪���������ꍇ�A"#"�ɂ���
	if (DivMark == NULL)
	{
		DivMark = DefaultDivMark;
	}

	// ���I�z��̐���
	char*	pTmpArray = NULL;
	pTmpArray = (char*)malloc(MAX_SIZE(MaxCharCell) + NULL_SIZE);			// char�^�z����g�p����ő僁�������������m��<free�L�ڍς�>
	if (pTmpArray == NULL) {	// �m�ۂł��Ȃ�������
		fclose(csvFile);		// �t�@�C���̃N���[�Y
		return -1;				// �G���[�o���ďI��
	}

	memset(pTmpArray, '\0', MAX_SIZE(MaxCharCell) + NULL_SIZE);			// ������

	// �t�@�C���ւ̃A�N�Z�X�Ɏg�p����char�^�ϐ�
	char	OneLineStr[1024] = { NULL };								// �ǂݎ��t�@�C���́A��s���̕�������i�[���邽�߂�char�^�z��
	char*	pDivideStr = NULL;											// str�z��ւ̃A�N�Z�X�pchar�^�|�C���^

	// �ǂݍ��񂾃f�[�^�̐����J�E���g����ϐ�
	//int		storeCharCnt = 0;

	// �z��ɐ��l���i�[������
	while (fgets(&OneLineStr[0], (MaxCharCell * MAX_COLUMN), csvFile) != NULL)		// �ǂݎ��t�@�C���́A��s���̕�������i�[
	{	// ��s�P�ʂ̓ǂݎ���Ƃ��A�t�@�C���I���܂ŌJ��Ԃ�
		pDivideStr = strtok(OneLineStr, ",");							// �P��ڂ̕���������o��
		if (pDivideStr == NULL) break;									// NULL�Ȃ烋�[�v�𔲂���

		do
		{
			int comOffset = SerchWordOffset(pDivideStr, CommentsSymbol);	// �R�����g�L���̈ʒu���擾

			// �R�����g�L�����擪�ɂ���Ƃ��͂��̃Z���ɏ�����Ă�����e�͔�΂�
			if (comOffset != 0 && pDivideStr != NULL)
			{	// �f�[�^�̊i�[
				char*	pBuf = NULL;

				int		bufNum = MaxCharCell + NULL_SIZE;				// pBuf�̗v�f��
				pBuf = new char[bufNum];								// �ꎞ�I�ȕ�����R�s�[�p�̔z��<delete�L�ڍς�>
				memset(pBuf, '\0', bufNum);								// ������

				// pDivideStr�̕�������R�s�[
				strncpy_s(pBuf, bufNum, pDivideStr, MaxCharCell);

				// ���o����������̕��������擾
				int		len = (int)strlen(pBuf);
				// �R�����g�L���ȉ��̕����́A�S��"\0"�ɒu��������i���R�����g�ȉ��̂��̂͊i�[���Ȃ��悤�ɂ��邽�߁j
				if (comOffset != -1) {						// �R�����g�L����������Ă��Ȃ��ꍇ�͍s��Ȃ�

					//		�R�����g�L���̏ꏊ����	  �R�����g�L���ȉ��̕������������u��������
					memset(pBuf + comOffset, '\0', (len - comOffset));

					len = (int)strlen(pBuf);				// �u��������̕�����������
				}

				strncat_s(pTmpArray, MAX_SIZE(MaxCharCell), pBuf, MaxCharCell - sizeof(DivMark));	// ��؂�L����������悤�ɁApBuf�ɋ󂫂����
				strncat_s(pTmpArray, MAX_SIZE(MaxCharCell), DivMark, sizeof(DivMark));			// ��؂�L��������ɂ���
			//	storeCharCnt += (int)(strlen(pBuf) + strlen(DivMark));							// �������̃J�E���g

				if (pBuf != NULL) delete[] pBuf;
			}

			pDivideStr = strtok(NULL, ",");					// 2��ڈȍ~�̕���������o��
		} while (pDivideStr != NULL);						// ���o�������񂪂Ȃ��Ȃ�܂ŌJ��Ԃ�

	}

	// �z����Œ���̃������T�C�Y�����R�s�[
	size_t	BufSize = strlen(pTmpArray);					// �f�[�^�̑��������T�C�Y(������)���擾
	pFirst = new char[(int)BufSize + NULL_SIZE];			// ��������K�v�������V���Ɋm��(NULL�̊i�[���l��)
	memset(pFirst, '\0', BufSize + NULL_SIZE);				// ������

	// �K�v�������R�s�[
	strncpy(pFirst, pTmpArray, BufSize);

	// malloc�Ŋm�ۂ���"pTmpArray"�̃����������
	free(pTmpArray);

	// �t�@�C���̃N���[�Y���G���[�`�F�b�N
	if (fclose(csvFile) == EOF) {
		// �G���[���̏���
		printf("�N���[�Y�h�G���[�I");
		//	exit(1);			// �N���[�Y���s���AOS�Ɂu1�v��Ԃ��Đ���I��������
		return -1;
	}

	return (int)BufSize;	// ����������Ԃ�
	//return storeCharCnt;
}


/*******************************************************************************
* �֐���	: int SerchWordOffset(char* String, const char SingleWord)
* ����		: ������, �w�蕶��
* �Ԃ�l	: �w�蕶���́A�擪���琔�����Ƃ��̈ʒu		������Ȃ��������E�G���[ : -1
* ����		: ������"String"�̒�����A�w�蕶�����擪����ǂ̈ʒu�ɂ���̂���Ԃ�
*******************************************************************************/
int SerchWordOffset(const char* String, const char SingleWord)
{
	// �����񂪌�����Ȃ���
	if (String == NULL) return -1;	// �G���[��Ԃ�

	// �w�蕶���̈ʒu���i�[����ϐ�(�Ԃ�l)
	int		offset = 0;

	// Buf�ɋL�ڂ��ꂽ�������擪����ꕶ�������ʂ���
	// �p������:String�̏I�[�܂� �ϐ��̍X�V���e:�uString�v���w���A�h���X�Ɓuoffset�v�̒l�����ꂼ����Z
	for (; *String; ++String, ++offset)
	{
		// 1�����i�[�p��char�^�z��
		char singleWord[2] = { "\0" };

		// �P�����𒊏o
		strncat(singleWord, String, 1);

		// ���o�����P�����ɂ���ď�����ς���
		if (strcmp(singleWord, &SingleWord) == 0)
		{	// �w�肵�������񂪌�����΁A���̈ʒu��Ԃ�
			return offset;
		}

	}

	return -1;	// ������Ȃ��������A-1��Ԃ�
}


/*******************************************************************************
* �֐���		:	int DivideString(const char* String, int* Col, int* Row, char* DivMark)
* ����		:	���W�ԍ�, �ő�񐔂��i�[����Ԓn, �s�����i�[����Ԓn, ��؂�L��
* �Ԃ�l		:	���� �� 1		���s �� 0
* ����		:	�ǂݍ��񂾕�����̏c���̕��������A"\n"(���s�R�[�h)���狁�߂�
********************************************************************************/
int DivideString(const char* String, int* Col, int* Row, char* DivMark)
{
	// �����񂪌�����Ȃ���(�G���[�`�F�b�N)
	if (String == NULL) return 0;

	// char�^�|�C���^
	char*	Buf;

	// �uString�v�̕�������uBuf�v�ɃR�s�[
	{
		int	BufSize = (int)strlen(String);			// string�̃����������o��

		int		idxNum = BufSize + NULL_SIZE;		// �K�v�ȗv�f��
		Buf = new char[idxNum];						// �����^�z���K�v���������p��
		memset(Buf, '\0', sizeof(char) * idxNum);	// ������

		strncpy(Buf, String, BufSize);				// ������̃R�s�[
	}

	int		ColCnt = 0, RowCnt = 0;						// �s�Ɨ񂻂ꂼ��̃J�E���g�p�ϐ�
	int		MaxCol = -1;								// �ő�񐔂̔�r�p�̕ϐ�

	// ���ڂ̕�������i�[
	char*	divideBuf = NULL;							// ��؂���������������|�C���^
	char*	p = NULL;									// strtok_s�p�̃|�C���^
	divideBuf = strtok_s(&Buf[0], DivMark, &p);

	do
	{
		// �񐔂̃J�E���g
		ColCnt++;

		if (SerchWordOffset(divideBuf, '\n') >= 0)		// ���s�R�[�h����������
		{
			RowCnt++;									// ���̍s�֍s���̂ŁA�s�����v���X

			if (ColCnt > MaxCol) MaxCol = ColCnt;		// �ő吔�𒴂��Ă�����A�ő�񐔂��X�V
			ColCnt = 0;									// �񐔃J�E���g�̃��Z�b�g
		}

		divideBuf = strtok_s(NULL, DivMark, &p);		// �Q��ڈȍ~�̕��������肾��
	} while (divideBuf != NULL);				// divideBuf�ɓ��镶���񂪖����Ȃ�܂ŌJ��Ԃ�

	// ���ꂼ����
	*Row = RowCnt;
	*Col = MaxCol;

	// �������̉��
	if (Buf != NULL) delete[] Buf;

	return 1;
}