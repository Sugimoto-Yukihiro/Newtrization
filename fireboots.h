//==================================================================
//
// �t�@�C���[�u�[�c���� [fireboots.cpp]
// Auther : ���{�K�G
//
//==================================================================
#pragma once

//#include "player.h"	// �v���C���[
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
	bool ActivateFireBoots(D3DXVECTOR2 Pos, D3DXVECTOR2 BulletMove, D3DXVECTOR2 BulletSize, float Attack = 0.0f, float HP = 0.0f);	// �t�@�C���[�u�[�c�̋N��

	//------------------- �Z�b�^�[�֐�

	//------------------- �Q�b�^�[�֐�


private:
	CBullet m_Bullet[BOOTS_BULLET_NUM];	// �t�@�C���[�u�[�c�ŉ������ɔ�΂��o���b�g
	int m_nUsedBulletNum;			// ���ɔ��˂����o���b�g�̐�
};
