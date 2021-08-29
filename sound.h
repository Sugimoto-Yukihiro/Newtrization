//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : ��_�C��Y, ���{�K�G
//
//=============================================================================
#pragma once

#include <windows.h>
#include "xaudio2.h"	// �T�E���h�����ŕK�v

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
enum 
{
	SOUND_LABEL_BGM_title_01,		// �^�C�g��BGM_���̂P
	SOUND_LABEL_BGM_game_01,		// �Q�[��BGM_���̂P
	SOUND_LABEL_BGM_result_CLEAR,	// ���U���gBGM_�Q�[���N���A
	SOUND_LABEL_BGM_result_FAILED,	// ���U���gBGM_�Q�[���I�[�o�[


	SOUND_LABEL_MAX,
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
bool InitSound(HWND hWnd);
void UninitSound(void);
void PlaySound(int label);
void StopSound(int label);
void StopSound(void);

