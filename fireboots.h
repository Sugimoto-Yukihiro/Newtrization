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
#define BOOTS_BULLET_NUM		(3)		// �t�@�C���[�u�[�c�Ŏg�p����e�̐�

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CFireBoots
{
public:
	CFireBoots();	// �R���X�g���N�^
	~CFireBoots();	// �f�X�g���N�^

	void Init(char* pBulletTextureName = NULL, int TexDivX = 1, int TexDivY = 1, int AnimWait = 0);	// ����������
	void Uninit();	// �I������
	void Update(D3DXVECTOR2 StageSize);	// �X�V����
	void Draw(D3DXVECTOR2 ScrollPos);	// �`�揈��

	//------------------- �����o�֐�
	bool ActivateFireBoots(D3DXVECTOR2 BulletMove, D3DXVECTOR2 BulletSize, float Attack = 0.0f, float HP = 0.0f);	// �t�@�C���[�u�[�c�̋N��

	//------------------- �Z�b�^�[�֐�
//	void SetFireBoots(CPlayer* User);			// �v���C���[�Ƀt�@�C���[�u�[�c���Z�b�g
	bool SetFireBoots(D3DXVECTOR2* UserPos);	// �t�@�C���[�u�[�c���Z�b�g����L�����N�^�[�̍��W���Z�b�g
	bool UnsetFireBoots();						// �t�@�C���[�u�[�c�̉���

	//------------------- �Q�b�^�[�֐�


private:
	CBullet m_Bullet[BOOTS_BULLET_NUM];	// �t�@�C���[�u�[�c�ŉ������ɔ�΂��o���b�g
//	CPlayer* m_pUser;				// ���̃t�@�C���[�u�[�c�𑕒����Ă���v���C���[�ւ̃|�C���^
	D3DXVECTOR2* m_pPosition;		// ���̃t�@�C���[�u�[�c�𑕒����Ă���L�����N�^�[�̍��W
	int m_nUsedBulletNum;			// ���ɔ��˂����o���b�g�̐�
};
