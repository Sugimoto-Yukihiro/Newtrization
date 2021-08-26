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
#include "fireboots.h"	// �t�@�C���[�u�[�c
#include "poison.h"		// �ŏ���

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPlayer : public CTexture, public CGravity
{
public:
	CPlayer();	// �R���X�g���N�^
	~CPlayer();	// �f�X�g���N�^

	//------------------- �����o�֐�
	void Init(char* FireBootsTexName = NULL);		// ������
	void Uninit();						// �I������
	void Update(int FalmeCnt = 0);		// �X�V����
	void Draw(D3DXVECTOR2 ScrollPos);	// �`�揈��

	//------------------- ���̑������o�֐�
	void KillPlayer();	// ���̃v���C���[���E������

	//------------------- �Z�b�^�[�֐�
	void SetPlayer(D3DXVECTOR2 Pos);	// �v���C���[���o��������
	void SetPosition(D3DXVECTOR2 Pos);	// �v���C���[�̍��W���Z�b�g

	void SetSize(D3DXVECTOR2 Size) { SetGravityObjectSize(Size); };	// �v���C���[�̃T�C�Y���Z�b�g
	void SetBouyant(D3DXVECTOR2 Bouyant) { m_fBouyant = Bouyant; };	// �v���C���[�̕��͂��Z�b�g
	void SetJumpForce(float Force) { m_fJumpForce = Force; };		// �v���C���[�̃W�����v�x�N�g�����擾
	void SetHPMax(float MaxHP) { m_fHitPointMAX = MaxHP; };			// �v���C���[��HP��MAX�l���Z�b�g
	void SetCurrentHP(float CurHP) { m_fCurrentHP = CurHP; };		// �v���C���[�̌��݂�HP���Z�b�g
	void SetUseFlag(bool Use) { m_bUse = Use; };					// �v���C���[��use�t���O�̃Z�b�g
	void SetPoisonFlag(bool Poison) { m_bPoison = Poison; };		// �v���C���[��use�t���O�̃Z�b�g

	//------------------- �Q�b�^�[�֐�
	D3DXVECTOR2 GetPosition() { return GetGravityObjectPos(); };	// �v���C���[�̍��W���擾
	D3DXVECTOR2 GetSize() { return GetGravityObjectSize(); };		// �v���C���[�̑傫�����擾
	D3DXVECTOR2 GetLegPos() { return m_LegPosition; };	// �v���C���[�̑��̈ʒu���擾
	D3DXVECTOR2 GetBouyant() { return m_fBouyant; };	// �v���C���[�̕��͂��擾
	float GetJumpForce() { return m_fJumpForce; };		// �v���C���[�̃W�����v�͂��擾
	float GetHP() { return m_fHitPointMAX; };			// �v���C���[��HP���擾
	float GetCurrentHP() { return m_fCurrentHP; };		// �v���C���[�̌��݂�HP���擾
	bool GetUseFlag() { return m_bUse; };				// �v���C���[��use�t���O�̎擾
	bool GetIsDush() { return m_bDush; };				// �v���C���[�̃_�b�V���t���O���擾
	bool GetIsGround() { return m_bOnGround; };			// �v���C���[�̐ڒn�t���O���擾
	bool GetIsJump() { return m_bIsJump; };				// �v���C���[�̃W�����v�t���O���擾
	bool GetIsMove() { return m_bIsMove; };				// �v���C���[�̃W�����v�t���O���擾
	bool GetIsPoison() { return m_bPoison; };			// �v���C���[�̓ŏ�ԃt���O���擾


	//------------------- �}�N����`
	#define PLAYER_ALIVE	SetUseFlag(true)	// �v���C���[�𐶂��Ԃ点��
	#define PLAYER_KILL		KillPlayer()		// �v���C���[���E��


private:
	//------------------- �����o�֐�(private)
	/* ���W�����v�����͂��̊֐����ōs���Ă��i�W�����v������p�̊֐����\��j */
	void InputControllPlayer();					// �v���C���[�� �L�[�܂��̓Q�[���p�b�h���� �œ�����
	void CollisionMapchip(CMapchip Mapchip, D3DXVECTOR2 PlayerOldPos);	// �}�b�v�`�b�v�Ƃ̓����蔻�������ĉ����o���������s��
	void OnGround();	// ���n�������̏���
	void NotOnGround();	// �󒆂ɂ��鎞�̏���

	//------------------- �����o�ϐ�
	CFireBoots	m_FireBoots;				// �t�@�C���[�u�[�c
	CPoison		m_Poison;					// �ŏ���
	D3DXVECTOR2	m_LegPosition;				// �v���C���[�̑��̍��W
	D3DXVECTOR2	m_fBouyant;					// ���͉����G���A�ɂԂ��������̗͂�ۑ�����ϐ�
	float		m_fJumpForce;				// �v���C���[�̃W�����v��
	float		m_fHitPointMAX;				// �v���C���[��HP��MAX�l
	float		m_fCurrentHP;				// �v���C���[�̌��݂�HP
//	int			m_nCurrentMapChipNo;		// �v���C���[�̌��݂���}�b�v�`�b�v�ԍ�
//	int			m_nMapchipX, m_nMapchipY;	// �}�b�v�`�b�v���W�n�ł́A�v���C���[�̌��݈ʒu
	int			m_nTexNo;					// �e�N�X�`���ԍ�
	bool		m_bUse;						// true:�g���Ă���(����)  false:���g�p(���S)
	bool		m_bDush;					// �v���C���[���_�b�V�������ǂ���
	bool		m_bOnGround;				// �v���C���[���ڒn���Ă��邩�ǂ���  true:�����n�ʂɂ��Ă���  false:�󒆂ɂ���
	bool		m_bIsJump;					// �v���C���[���W�����v�����ǂ���
	bool		m_bIsMove;					// �v���C���[�̓���t���O   true:�����Ă� false:��~��
	bool		m_bPoison;					// �v���C���[�̓ŏ�ԃt���O   true:�ŏ�� false:�ŏ�Ԃ���Ȃ�
};



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void CreatePlayerTexture(void);
void ReleasePlayerTexture(void);
