//=============================================================================
//
// UI���� [userInterface.h]
// Author : ���{�K�G
//
//=============================================================================
#pragma once

#include "texture.h"

//*****************************************************************************
// enum
//*****************************************************************************
enum
{
/* ���㌴�_�ŕ`�悷��e�N�X�`�� */
	GAMEUI_TEX_TYPE_HPgage,			// �v���C���[��HP�Q�[�W
	GAMEUI_TEX_TYPE_HPgage_Cover,	// �v���C���[��HP�Q�[�W�̑���

/* ������艺�͒��S���_�ŕ`�悷��e�N�X�`�� */
//	UI_TEX_TYPE_Player_PoisonIcon,	// �v���C���[�̓ŏ�ԃA�C�R��


	// �g�p����e�N�X�`���̐�
	GAMEUI_TEX_TYPE_MAX,

	// ���㌴�_�ŕ`�悷��e�N�X�`���̍ő�ԍ��i�܂�Aenum�ň�ԉ��ɏ����Ă����j
	GAMEUI_TEX_DRAW_TOPLEFT_MAXNO = GAMEUI_TEX_TYPE_HPgage_Cover,
}; // GAME_UI_TEXTURE_TYPE;	// �Q�[����ʂ�UI�Ŏg�p����e�N�X�`���̎��

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define HP_GAGE_POS_TOPLEFT		D3DXVECTOR2(0.0f, 0.0f)			// HP�Q�[�W�̕`��ʒu�i������W�j
#define HP_GAGE_WIDTH			275.0f								// HP�Q�[�W�̉���
#define HP_GAGE_HEIGHT			23.0f								// HP�Q�[�W�̏c��
#define HP_GAGE_SIZE			D3DXVECTOR2(HP_GAGE_WIDTH, HP_GAGE_HEIGHT)	// HP�Q�[�W�̃T�C�Y
#define HP_GAGE_COLOR			D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)	// HP�Q�[�W�{�̂̒��]�E

#define HP_GAGE_COVER_WIDTH		300.0f		// HP�Q�[�W�J�o�[�̉���
#define HP_GAGE_COVER_HEIGHT	50.0f		// HP�Q�[�W�J�o�[�̏c��

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CGameUI	// ���[�U�[�C���^�[�t�F�[�X �N���X
{
public:
	CGameUI();		// �R���X�g���N�^
	~CGameUI();		// �f�X�g���N�^

	//------------------- �����o�֐�
	void Init();	// ����������
	void Uninit();	// �I������
	void Update();	// �X�V����
	void Draw();	// �`�揈��

private:
	//------------------- �����o�ϐ�
	CTexture m_GameTexture[GAMEUI_TEX_TYPE_MAX];	// �g�p�e�N�X�`���iGame�j

};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void CreateGameUITexture(void);		// �e�N�X�`���̐���
void ReleaseGameUITexture(void);	// �e�N�X�`���̉��
