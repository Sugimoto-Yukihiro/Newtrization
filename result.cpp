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
	"data/TEXTURE/Result/bg_result.png",
	"data/TEXTURE/Result/0829_Result.png",
};

// �g�p�e�N�X�`���̃t�@�C����(�Q�[���I�[�o�[��)
static char *g_TextureGameOver[TEXTURE_MAX_GAMEOVER] = {
	"data/TEXTURE/fade_black.png",	// �w�i
	"data/TEXTURE/Result/0829_GameOver.png",
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

//	m_Score.Init(RESULT_TEX_NAME_SCORE, RESULT_TEX_SIZE_SCORE);	// �X�R�A�̏�����

	// �Q�[���̃N���A��Ԃɂ���ď�����ς���
	if (m_CreaFlag)
	{	// �Q�[���N���A
		CreateTextureGameClear();					// �g�p����e�N�X�`���𐶐�
		PlaySound(SOUND_LABEL_BGM_result_CLEAR);	// �Q�[���N���A����BGM�Đ�
	}
	else
	{	// �Q�[���I�[�o�[
		CreateTextureGameOver();					// �g�p����e�N�X�`���𐶐�
		PlaySound(SOUND_LABEL_BGM_result_FAILED);	// �Q�[���I�[�o�[����BGM�Đ�
	}

}



//=============================================================================
// �I������
//=============================================================================
void CModeResult::Uninit()
{
	// �T�E���h��~
	StopSound();

	//------------------- �����o�C���X�^���X�̏I������
	// �X�R�A�̏I������
	m_Score.Uninit();

	// �e�N�X�`���̏I������
	for (int i = 0; i < RESULT_TEXTURE_MAX; i++)
	{
		m_Texture[i].Uninit();				// �e�N�X�`���̏I������
		m_Texture[i].ReleaseTextureInf();	// �e�N�X�`���̉��
	}

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

#ifdef _DEBUG
	
#endif // _DEBUG


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

		// �X�R�A�̕\��
		m_Score.Draw(RESULT_TEX_POS_SCORE);
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

	// �ʂɃT�C�Y�E�ʒu���w��
	//------------------- �w�i
	m_Texture[GAMECLEAR_TEX_bg].SetTexSize(SCREEN_SIZE);	// �傫���̓X�N���[���̑傫��
	m_Texture[GAMECLEAR_TEX_bg].SetTexPos(SCREEN_CENTER);	// ���W�̓X�N���[���̒��S

	//------------------- ���S("Result")
	m_Texture[GAMECLEAR_TEX_logo].SetTexSize(RESULT_LOGO_SIZE);		// �傫���̓X�N���[���̑傫��
	m_Texture[GAMECLEAR_TEX_logo].SetTexPos(RESULT_LOGO_POS);		// ���W�̓X�N���[���̒��S
	m_Texture[GAMECLEAR_TEX_logo].SetTexColor(RESULT_LOGO_COLOR);	// �F���w��

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

	// �ʂɃT�C�Y�E�ʒu���w��
	//------------------- �w�i
	m_Texture[GAMECLEAR_TEX_bg].SetTexSize( SCREEN_SIZE );	// �傫���̓X�N���[���̑傫��
	m_Texture[GAMECLEAR_TEX_bg].SetTexPos( SCREEN_CENTER );	// ���W�̓X�N���[���̒��S

	//------------------- ���S("GANEOVER")
	m_Texture[GAMEOVER_TEX_logo].SetTexSize(RESULT_LOGO_GAMEOVER_SIZE);	// �傫���̓X�N���[���̑傫��
	m_Texture[GAMEOVER_TEX_logo].SetTexPos(RESULT_LOGO_GAMEOVER_POS);		// ���W�̓X�N���[���̒��S
	m_Texture[GAMEOVER_TEX_logo].SetTexColor(RESULT_LOGO_GAMEOVER_COLOR);	// �F���w��

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

