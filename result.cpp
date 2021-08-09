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
//#include "sound.h"	// �T�E���h
#include "texture.h"		// �X�v���C�g
//#include "score.h"	// �X�R�A

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NEXT_MODE					MODE_TITLE		// ���̃��[�h

#define TEXTURE_SIZE_BG				D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT)	// �w�i�T�C�Y

#define TEXTURE_WIDTH_LOGO			(480)			// ���S�T�C�Y
#define TEXTURE_HEIGHT_LOGO			(80)			// 

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11ShaderResourceView	*g_Texture[RESULT_TEX_PATTARN_MAX] = { NULL };	// �e�N�X�`�����

static char *g_TexturName[] = {	// �g�p�e�N�X�`���̃t�@�C����
	/* �y�d�v�z�����̏��Ԃ́A�w�b�_�[�ɋL�ڂ���Ă�enum�̏��ԂƑ����邱�ƁI�I�I�I�I */
	"data/TEXTURE/bg_result.png",	// TexNo�F0
	"data/TEXTURE/logo_result.png",	// TexNo�F1
};



//=============================================================================
// ����������
//=============================================================================
void CModeResult::Init()
{
	//------------------- �e�N�X�`������
	for (int i = 0; i < RESULT_TEX_PATTARN_MAX; i++)
	{
		CreateTexture(g_TexturName[i], &g_Texture[i]);	// ����
	}

	//------------------- �����o�ϐ��̏�����
	m_Tex[RESULT_TEX_Bg].SetTexSize( TEXTURE_SIZE_BG );	// �w�i�̃T�C�Y���Z�b�g
	m_Tex[RESULT_TEX_Bg].SetTexPos( SCREEN_CENTER );	// �w�i�̃T�C�Y���Z�b�g

	// BGM�Đ�
//	PlaySound(SOUND_LABEL_BGM_sample002);
}



//=============================================================================
// �I������
//=============================================================================
void CModeResult::Uninit()
{
	//------------------- Init()�Ő��������e�N�X�`�������
	for (int i = 0; i < RESULT_TEX_PATTARN_MAX; i++)
	{
		ReleaseTexture(&g_Texture[i]);	// ���
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void CModeResult::Update()
{
	//------------------- �L�[�E�Q�[���p�b�g�ł̓��͂Ŏ��̃��[�h��
#ifdef _DEBUG
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
#endif // _DEBUG



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
	for (int i = 0; i < RESULT_TEX_PATTARN_MAX; i++)
	{
		m_Tex[i].DrawTexture(g_Texture[i]);	// �`����s
	}

}

