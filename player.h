//=============================================================================
//
// �v���C���[���� [player.h]
// Author : ���Α�q, ���{�K�G
//
//=============================================================================
#pragma once

#include "texture.h"	// �e�N�X�`���`�揈��
#include "gravity.h"	// �d�͏���
#include "mapchip.h"	// �}�b�v�`�b�v

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_MAX		(1)			// �v���C���[��Max�l��

#define SCROLL_SET_X	(SCREEN_CENTER_X)	// �X�N���[�����W�̃Z�b�g�ʒu
#define SCROLL_SET_Y	(SCREEN_CENTER_Y)	// �X�N���[�����W�̃Z�b�g�ʒu

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPlayer : public CTexture, public CGravity
{
public:
	CPlayer();	// �R���X�g���N�^
	~CPlayer();	// �f�X�g���N�^

	//------------------- �����o�֐�
	void Init();	// ������
//	void Uninit();	// �I������
	void Update();	// �X�V����
	void Draw();	// �`�揈��

	//------------------- �Z�b�^�[�֐�
	void SetPlayer(D3DXVECTOR2 Pos);	// �v���C���[���o��������
	void SetPosition(D3DXVECTOR2 Pos);	// �v���C���[�̍��W���Z�b�g
	void SetSize(D3DXVECTOR2 Size);		// �v���C���[�̃T�C�Y���Z�b�g
	void SetJumpForce(float Force);		// �v���C���[�̃W�����v�x�N�g�����擾
	void SetUseFlag(bool Use);			// �v���C���[��use�t���O�̃Z�b�g
	void KillPlayer();					// �v���C���[���E������

	//------------------- �Q�b�^�[�֐�
	D3DXVECTOR2 GetPosition();	// �v���C���[�̍��W���擾
	D3DXVECTOR2 GetSize();		// �v���C���[�̑傫�����擾
	float GetJumpForce();		// �v���C���[�̃W�����v�͂��擾

	bool GetUseFlag() { return m_bUse; };		// �v���C���[��use�t���O�̎擾
	bool GetIsDush() { return m_bDush; };		// �v���C���[�̃_�b�V���t���O���擾
	bool GetIsGround() { return m_bOnGround; };	// �v���C���[�̐ڒn�t���O���擾
	bool GetIsJump() { return m_bIsJump; };		// �v���C���[�̃W�����v�t���O���擾
	bool GetIsMove() { return m_bIsMove; };		// �v���C���[�̃W�����v�t���O���擾


	//------------------- �}�N����`
	#define PLAYER_ALIVE	SetUseFlag(true)	// �v���C���[�𐶂��Ԃ点��
	#define PLAYER_KILL		KillPlayer()		// �v���C���[���E��


private:
	//------------------- �����o�֐�(private)
	/* ���W�����v�����͂��̊֐����ōs���Ă��i�W�����v������p�̊֐����\��j */
	void InputControllPlayer(D3DXVECTOR2 NowPosition);					// �v���C���[�� �L�[�܂��̓Q�[���p�b�h���� �œ�����
	void CollisionMapchip(CMapchip Mapchip, D3DXVECTOR2 PlayerOldPos);	// �}�b�v�`�b�v�Ƃ̓����蔻�������ĉ����o���������s��

	//------------------- �����o�ϐ�
	float		m_fJumpForce;				// �v���C���[�̃W�����v�x�N�g��
//	int			m_nCurrentMapChipNo;		// �v���C���[�̌��݂���}�b�v�`�b�v�ԍ�
//	int			m_nMapchipX, m_nMapchipY;	// �}�b�v�`�b�v���W�n�ł́A�v���C���[�̌��݈ʒu
	int			m_nTexNo;					// �e�N�X�`���ԍ�
	bool		m_bUse;						// true:�g���Ă���(����)  false:���g�p(���S)
	bool		m_bDush;					// �v���C���[���_�b�V�������ǂ���
	bool		m_bOnGround;				// �v���C���[���ڒn���Ă��邩�ǂ���  true:�����n�ʂɂ��Ă���  false:�󒆂ɂ���
	bool		m_bIsJump;					// �v���C���[���W�����v�����ǂ���
	bool		m_bIsMove;					// �v���C���[�̓���t���O   true:�����Ă� false:��~��
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void CreatePlayerTextureAndBuffer(void);
void ReleasePlayerTextureAndBuffer(void);
void PresetDrawPlayer(void);