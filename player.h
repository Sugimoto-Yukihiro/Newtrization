//=============================================================================
//
// �v���C���[���� [player.h]
// Author : ���Α�q, ���{�K�G
//
//=============================================================================
#pragma once

#include "texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_MAX		(1)			// �v���C���[��Max�l��

#define SCROLL_SET_X				(SCREEN_CENTER_X / 2)			// �X�N���[�����W�̃Z�b�g�ʒu
#define SCROLL_SET_Y				(SCREEN_CENTER_Y * 2)			// �X�N���[�����W�̃Z�b�g�ʒu


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPlayer : public CTexture
{
public:
	CPlayer();							// �R���X�g���N�^
	~CPlayer();							// �f�X�g���N�^

	//------------------- �����o�֐�
	void Init();						// ������
//	void Uninit();					// �I������
	void Update();						// �X�V����
	void Draw();						// �`�揈��

	//------------------- �Z�b�^�[�֐�
	void SetPlayerUseFlag(bool Use);	// �v���C���[��use�t���O�̃Z�b�g
	void KillPlayer();					// �v���C���[���E������

	//------------------- �Q�b�^�[�֐�
	D3DXVECTOR2 GetPlayerPos();			// �v���C���[�̍��W���擾
	bool GetPlayerUseFlag();			// �v���C���[��use�t���O�̎擾

	//------------------- �}�N����`
	#define PLAYER_ALIVE	SetPlayerUseFlag(true)	// �v���C���[�𐶂��Ԃ点��

private:
	//------------------- �����o�ϐ�
	int				m_nTexNo;			// �e�N�X�`���ԍ�
	bool			m_bUse;				// true:�g���Ă���  false:���g�p
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void CreatePlayerTextureAndBuffer(void);
void ReleasePlayerTextureAndBuffer(void);
void PresetDrawPlayer(void);