//=============================================================================
//
// Main�w�b�_�[ [main.h]
// Author : 
//
//=============================================================================
#pragma once


#pragma warning(push)
#pragma warning(disable:4005)

#define _CRT_SECURE_NO_WARNINGS			// scanf ��warning�h�~
#include <stdio.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800		// �x���Ώ�
#include "dinput.h"
#include "mmsystem.h"

#pragma warning(pop)


//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#pragma comment (lib, "d3d11.lib")		
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "d3dx11.lib")	
#pragma comment (lib, "d3dx9.lib")	
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")


#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(960)				// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(540)				// �E�C���h�E�̍���
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)	// �E�C���h�E�̒��S�w���W
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)	// �E�C���h�E�̒��S�x���W
#define SCREEN_CENTER	D3DXVECTOR2((float)SCREEN_CENTER_X, (float)SCREEN_CENTER_Y)	// �E�B���h�E�̒��S���W

#define NUM_VERTEX		(4)					// ���_��

#define FPS_RATE		(60)				// FPS�l�i1�b���Ƃɕ`��E�X�V�������s���񐔁j
#define NULL_SIZE		(1)
#define ZERO_VECTOR2	D3DXVECTOR2(0.0f, 0.0f)
#define DEFAULT_COLOR	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)

//*****************************************************************************
// enum
//*****************************************************************************
typedef enum
{
	MODE_NONE = -1,
	MODE_OPENING,		// �I�[�v�j���O���
	MODE_TITLE,			// �^�C�g�����
	MODE_TUTORIAL,		// �Q�[���������
	MODE_GAME,			// �Q�[�����
	MODE_RESULT,		// ���U���g���
	MODE_MAX
} MODE;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CMode
{
public:
	//------------------- �����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Update();
	void Draw();
	void Uninit();
	//------------------- �Q�b�^�[�֐�
	MODE GetMode();

	//------------------- �Z�b�^�[�֐�
	void SetMode(MODE mode);

	//------------------- �e���[�h�̃C���X�^���X
	CModeGame m_GameMode;	// �Q�[�����

private:
	MODE m_Mode;	// ���[�h�̏�Ԃ��i�[����ϐ�
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
long GetMousePosX(void);
long GetMousePosY(void);
char *GetDebugStr(void);

//------------------- �e�C���X�^���X�ւ̃A�N�Z�X�p�֐�
CModeGame* GetGame();

//------------------- �����o�ϐ��̃A�N�Z�X�p�O���[�o���֐�
void RequestSetMode(MODE mode);
//MODE RequestGetMode();

//------------------- �t�@�C���֐�
int DivideString(const char* String, int* Col, int* Row, char* DivMark);
int SerchWordOffset(const char* String, const char SingleWord);