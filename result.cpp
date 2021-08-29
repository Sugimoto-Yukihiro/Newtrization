//=============================================================================
//
// ���U���g��ʏ��� [result.cpp]
// Author : ���{�K�G
//
//=============================================================================
#include "main.h"
#include "result.h"

#include "fade.h"		// �t�F�[�h����
#include "input.h"		// �L�[�E�Q�[���p�b�h���͏���
#include "renderer.h"	// �����_�����O����
#include "sound.h"		// �T�E���h
#include "texture.h"	// �X�v���C�g

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NEXT_MODE		MODE_TITLE		// ���̃��[�h

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//static ID3D11ShaderResourceView	*g_Texture[RESULT_TEXTURE_MAX] = { NULL };	// �e�N�X�`�����

// �g�p�e�N�X�`���̃t�@�C����(�Q�[���N���A��)
static char *g_TextureGameClear[TEXTURE_MAX_CLEAR] = {
	"data/TEXTURE/Result/bg_result.png",	// TexNo�F0
	"data/TEXTURE/Result/result_logo.png",	// TexNo�F1
};

// �g�p�e�N�X�`���̃t�@�C����(�Q�[���I�[�o�[��)
static char *g_TextureGameOver[TEXTURE_MAX_GAMEOVER] = {
	"data/TEXTURE/Result/bg_result.png",	// TexNo�F0
	"data/TEXTURE/Result/result_logo.png",	// TexNo�F1
};

//=============================================================================
// ����������
//=============================================================================
void CModeResult::Init()
{
	//------------------- �����o�C���X�^���X�̏�����
	for (int i = 0; i < RESULT_TEXTURE_MAX; i++)
	{
		m_Texture[i].Init();	// �e�N�X�`��
	}
	m_Score.Init(RESULT_TEX_NAME_SCORE, RESULT_TEX_SIZE_SCORE);	// �X�R�A
	m_CreaFlag = false;	// �Q�[���I�[�o�[�ŏ�����

	// BGM�Đ�
//	PlaySound(SOUND_LABEL_BGM_sample002);
}



//=============================================================================
// �I������
//=============================================================================
void CModeResult::Uninit()
{
	//------------------- �����o�C���X�^���X�̏I������
	for (int i = 0; i < RESULT_TEXTURE_MAX; i++)
	{
		m_Texture[i].Uninit();				// �e�N�X�`���̏I������
		m_Texture[i].ReleaseTextureInf();	// �e�N�X�`���̉��
	}
	m_Score.Uninit();	// �X�R�A�̏I������

}

//=============================================================================
// �X�V����
//=============================================================================
void CModeResult::Update()
{
	//------------------- �L�[�E�Q�[���p�b�g�ł̓��͂Ŏ��̃��[�h��
#ifdef KEY_MODE_CHANGE
	if (KEY_MODE_CHANGE)
	{// Enter��������A�X�e�[�W��؂�ւ���
		SetFade(FADE_OUT, NEXT_MODE);	// �t�F�[�h���Ď��̃��[�h��
	//	SetMode(NEXT_MODE);				// ���̃��[�h�ɃV�[���J��
	}
	// �Q�[���p�b�h�œ��͏���
	else if (PAD_MODE_CHANGE)
	{
		SetFade(FADE_OUT, NEXT_MODE);	// �t�F�[�h���Ď��̃��[�h��
	//	SetMode(NEXT_MODE);				// ���̃��[�h�ɃV�[���J��
	}
#endif // KEY_MODE_CHANGE



	/* �ȉ��A�e�e�N�X�`�����ƂɍX�V����������΋L�� */



}

//=============================================================================
// �`�揈��
//=============================================================================
void CModeResult::Draw()
{
	// �`��̑O����
	PresetDraw2D();

	// �S�Ẵe�N�X�`���̕`��
	if (m_CreaFlag)
	{	// �Q�[���N���A���̃e�N�X�`���`��
		for (int i = 0; i < TEXTURE_MAX_CLEAR; i++)
		{
			m_Texture[i].DrawTexture();
		}

	}
	else
	{	// �Q�[���I�[�o���̃e�N�X�`���`��
		for (int i = 0; i < TEXTURE_MAX_GAMEOVER; i++)
		{
			m_Texture[i].DrawTexture();
		}

	}

}


// �Q�[���N���A���Ɏg�p����e�N�X�`���̐���
void CModeResult::CreateTextureGameClear()
{
	// �g�p����e�N�X�`�����ꊇ����
	for (int i = 0; i < TEXTURE_MAX_CLEAR; i++)
	{
		// �e�N�X�`������
		m_Texture[i].CreateTextureInf(g_TextureGameClear[i]);
	}

}

// �Q�[���N���A���Ɏg�p����e�N�X�`���̉��
void CModeResult::ReleaseTextureGameClear()
{
	// �g�p�����e�N�X�`�����ꊇ����
	for (int i = 0; i < TEXTURE_MAX_CLEAR; i++)
	{
		// �e�N�X�`�����
		m_Texture[i].ReleaseTextureInf();
	}

}


// �Q�[���I�[�o�[���Ɏg�p����e�N�X�`���̐���
void CModeResult::CreateTextureGameOver()
{
	// �g�p����e�N�X�`�����ꊇ����
	for (int i = 0; i < TEXTURE_MAX_GAMEOVER; i++)
	{
		// �e�N�X�`������
		m_Texture[i].CreateTextureInf(g_TextureGameOver[i]);
	}

}

// �Q�[���I�[�o�[���Ɏg�p����e�N�X�`���̉��
void CModeResult::ReleaseTextureGameOver()
{
	// �g�p�����e�N�X�`�����ꊇ����
	for (int i = 0; i < TEXTURE_MAX_GAMEOVER; i++)
	{
		// �e�N�X�`�����
		m_Texture[i].ReleaseTextureInf();
	}

}

