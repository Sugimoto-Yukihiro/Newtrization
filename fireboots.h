//==================================================================
//
// �t�@�C���[�u�[�c���� [fireboots.cpp]
// Auther : ���{�K�G
//
//==================================================================
#pragma once

#include "player.h"	// �v���C���[
#include "bullet.h"	// �o���b�g

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BULLET_NUM		(3)		// �t�@�C���[�u�[�c�Ŏg�p����e�̐�

#define BULLET_WIDTH	50.0f
#define BULLET_HEIGHT	50.0f
#define BULLET_SIZE		D3DXVECTOR2(BULLET_WIDTH, BULLET_HEIGHT)	// �e�̃T�C�Y


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CFireBoots
{
public:
	CFireBoots();	// �R���X�g���N�^
	~CFireBoots();	// �f�X�g���N�^

	void Init(char* pTextureName = NULL, int TexDivX = 1, int TexDivY = 1, int AnimWait = 0);	// ����������
	void Uninit();	// �I������
	void Update();	// �X�V����
	void Draw(D3DXVECTOR2 ScrollPos);	// �`�揈��

	//------------------- �Z�b�^�[�֐�
//	void SetFireBoots(CPlayer* User);			// �v���C���[�Ƀt�@�C���[�u�[�c���Z�b�g
	bool SetFireBoots(D3DXVECTOR2* UserPos);	// �t�@�C���[�u�[�c���Z�b�g����L�����N�^�[�̍��W���Z�b�g
	bool UnsetFireBoots();						// �t�@�C���[�u�[�c�̉���

	//------------------- �Q�b�^�[�֐�


private:
	CBullet m_Bullet[BULLET_NUM];	// �t�@�C���[�u�[�c�ŉ������ɔ�΂��o���b�g
//	CPlayer* m_pUser;				// ���̃t�@�C���[�u�[�c�𑕒����Ă���v���C���[�ւ̃|�C���^
	D3DXVECTOR2* m_pPosition;		// ���̃t�@�C���[�u�[�c�𑕒����Ă���L�����N�^�[�̍��W
	float m_fUpForce;				// �t�@�C���[�u�[�c����e�𔭎˂������Ƃ��̏�����ւ̗�
	int m_nUsedBulletNum;			// ���ɔ��˂����o���b�g�̐�
};
