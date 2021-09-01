//=============================================================================
//
// �^�C�g����ʏ��� [title.cpp]
// Author : ���{�K�G
//
//=============================================================================
#include "main.h"
#include "title.h"

#include "renderer.h"
#include "input.h"		// �L�[�E�Q�[���p�b�h����
#include "fade.h"		// �t�F�[�h
#include "sound.h"		// �T�E���h

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NEXT_MODE					MODE_GAME		// ���̃��[�h

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static char *g_TextureName[] = {
	"data/TEXTURE/BG/0830_BG_1.png",		// �w�i
	"data/TEXTURE/Title/0829_Logo.png",		// ���S
};

//=============================================================================
// ����������
//=============================================================================
void CModeTitle::Init()
{
	// �e�N�X�`�����ꊇ����
	for (int i = 0; i < TITLE_TEX_MAX; i++)
	{
		m_Texture[i].Init();	// ������
		m_Texture[i].CreateTextureInf(g_TextureName[i]);	// �e�N�X�`������
	}

	// �e�N�X�`���C���X�^���X�̃p�����[�^���Z�b�g
	SetTitleTexInf();

	// BGM�Đ�
	PlaySound(SOUND_LABEL_BGM_title_01);

}

//=============================================================================
// �I������
//=============================================================================
void CModeTitle::Uninit()
{
	// �T�E���h��~
	StopSound();

	// �e�N�X�`�����ꊇ���
	for (int i = 0; i < TITLE_TEX_MAX; i++)
	{
		m_Texture[i].ReleaseTextureInf();	// �e�N�X�`�����
		m_Texture[i].Uninit();	// �I������
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void CModeTitle::Update()
{
	//------------------- �L�[�E�Q�[���p�b�g�ł̓��͂Ŏ��̃��[�h��
#ifdef KEY_MODE_CHANGE
	if (KEY_MODE_CHANGE || PAD_MODE_CHANGE)
	{
		SetFade(FADE_OUT, NEXT_MODE);			// �t�F�[�h���Ď��̃��[�h��
	//	SetMode(NEXT_MODE);						// ���̃��[�h�ɃV�[���J��
		PlaySound(SOUND_LABEL_SE_scenemove);	// ���ʉ��Đ�
	}
#endif // KEY_MODE_CHANGE


}

//=============================================================================
// �`�揈��
//=============================================================================
void CModeTitle::Draw()
{
	// 2D�̕`��O����
	PresetDraw2D();

	// �e�N�X�`�����ꊇ�`��
	for (int i = 0; i < TITLE_TEX_MAX; i++)
	{
		m_Texture[i].DrawTexture();
	}

}

// �e�N�X�`���̃T�C�Y�E�`��ʒu�E�F���ʂŐݒ�
void CModeTitle::SetTitleTexInf()
{
	//------------------- �w�i
	m_Texture[TITLE_TEX_bg].SetTexSize(SCREEN_SIZE);		// �T�C�Y���Z�b�g
	m_Texture[TITLE_TEX_bg].SetTexPos(SCREEN_CENTER);		// �`��ʒu���Z�b�g
	m_Texture[TITLE_TEX_bg].SetTexColor(TITLE_BG_COLOR);	// ���_�F���Z�b�g

	//------------------- ���S
	m_Texture[TITLE_TEX_logo].SetTexSize(TITLE_LOGO_SIZE);		// �T�C�Y���Z�b�g
	m_Texture[TITLE_TEX_logo].SetTexPos(TITLE_LOGO_POS);		// �`��ʒu���Z�b�g
	m_Texture[TITLE_TEX_logo].SetTexColor(TITLE_LOGO_COLOR);	// ���_�F���Z�b�g

}

