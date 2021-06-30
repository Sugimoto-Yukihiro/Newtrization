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
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);


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
MODE g_Mode = START_MODE;

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
	if(FAILED(Init(hInstance, hWnd, true)))
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
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], "  CurrentMode:%d", GetMode());

#endif
				// �e�L�X�g�̃Z�b�g
				SetWindowText(hWnd, g_DebugStr);

				Update();			// �X�V����
				Draw();				// �`�揈��

				dwFrameCount++;		// �����񐔂̃J�E���g�����Z
			}
		}
	}
	
	timeEndPeriod(1);				// ����\��߂�

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �I������
	Uninit();

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
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
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
	if (g_Mode == MODE_TITLE) InitTitle();				// �^�C�g����ʂ̏I������
//	else if(g_Mode == MODE_TUTORIAL) InitTutorial();	// �`���[�g���A����ʂ̏I������
	else if (g_Mode == MODE_GAME) InitGame();			// �Q�[����ʂ̏I������
	else if (g_Mode == MODE_RESULT) InitResult();		// ���U���g��ʂ̏I������

	return S_OK;
}


//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	//------------------- ���[�h�ɉ��������������
	if (g_Mode == MODE_TITLE) UninitTitle();				// �^�C�g����ʂ̏I������
//	else if(g_Mode == MODE_TUTORIAL) UninitTutorial();	// �`���[�g���A����ʂ̏I������
	else if (g_Mode == MODE_GAME) UninitGame();			// �Q�[����ʂ̏I������
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
void Update(void)
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
		UpdateGame();
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
void Draw(void)
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
		DrawGame();
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
// ���[�h�̐ݒ�
//=============================================================================
void SetMode(MODE mode)
{
	//------------------- ���[�h��ς���O�Ƀ���������������Ⴄ
	if(g_Mode == MODE_TITLE) UninitTitle();				// �^�C�g����ʂ̏I������
//	else if(g_Mode == MODE_TUTORIAL) UninitTutorial();	// �`���[�g���A����ʂ̏I������
	else if(g_Mode == MODE_GAME) UninitGame();			// �Q�[����ʂ̏I������
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
		InitGame();
		break;

	case MODE_RESULT:
		// ���U���g��ʂ̏�����
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

// ���݂̃��[�h���擾
MODE GetMode(void)
{
	return g_Mode;
}