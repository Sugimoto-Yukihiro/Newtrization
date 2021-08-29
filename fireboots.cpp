//==================================================================
//
// �t�@�C���[�u�[�c���� [fireboots.cpp]
// Auther : ���{�K�G
//
//==================================================================

#include "main.h"
#include "fireboots.h"

//==================================================================
// �R���X�g���N�^�E�f�X�g���N�^
//==================================================================
CFireBoots::CFireBoots()	// �R���X�g���N�^
{
	Init();		// ����������
}

CFireBoots::~CFireBoots()	// �f�X�g���N�^
{
//	Uninit();	// �I������������
}



//==================================================================
// ����������
// �����F�o���b�g�e�N�X�`���̃t�@�C����, �o���b�g�e�N�X�`���̉�������, �o���b�g�e�N�X�`���̏c������, �A�j���[�V������Wait�l
//==================================================================
void CFireBoots::Init(char* pBulletTextureName, int TexDivX, int TexDivY, int AnimWait)	// ����������
{
	// �o���b�g�̏�����
	for (int i = 0; i < BOOTS_BULLET_NUM; i++)
	{
		m_Bullet[i].Init(pBulletTextureName, TexDivX, TexDivY, AnimWait);
		m_nFlameCnt[i] = 0;	// �t���[���J�E���g��������
		m_nCoolTime[i] = 0;	// �N�[���^�C����������
	}

	// �����o�ϐ��̏�����
	m_nUsedBulletNum = 0;
}



//==================================================================
// �I������
//==================================================================
void CFireBoots::Uninit()
{
	// �����o�ϐ��̉��
	m_nUsedBulletNum = 0;

	// �o���b�g�̉��
	for (int i = 0; i < BOOTS_BULLET_NUM; i++)
	{
		m_Bullet[i].Uninit();
	}

}



//==================================================================
// �X�V����
//==================================================================
void CFireBoots::Update(D3DXVECTOR2 StageSize)
{
	// �o���b�g�̍X�V
	for (int i = 0; i < BOOTS_BULLET_NUM; i++)
	{
		// ���̃o���b�g���g���Ă��Ȃ�������I��
		if (!m_Bullet[i].GetUseFlag()) continue;
		m_Bullet[i].Update();	// �X�V

		// �t���[�������J�E���g
		m_nFlameCnt[i]++;

		// �X�e�[�W�O�ɂ�������A���̃o���b�g�����
		if ((m_Bullet[i].GetPosition().x + (m_Bullet[i].GetSize().x * 0.5f)) < 0.0f ||			// �E�[�̓_���A�X�e�[�W���[�𒴂�������
			(m_Bullet[i].GetPosition().x - (m_Bullet[i].GetSize().x * 0.5f)) > StageSize.x ||	// ���[�̓_���A�X�e�[�W�E�[�𒴂�������
			(m_Bullet[i].GetPosition().y + (m_Bullet[i].GetSize().y * 0.5f)) < 0.0f ||			// ���[�̓_���A�X�e�[�W��[�𒴂�������
			(m_Bullet[i].GetPosition().y - (m_Bullet[i].GetSize().y * 0.5f)) > StageSize.y	)	// ��[�̓_���A�X�e�[�W���[�𒴂�������
		{
			m_Bullet[i].UnsetBullet();	// �o���b�g���
			m_nFlameCnt[i] = 0;			// �o�߃t���[�����̃��Z�b�g
			m_nUsedBulletNum--;			// �g�p�o���b�g���̌��Z
		}

	}

}



//==================================================================
// �`�揈��
//==================================================================
void CFireBoots::Draw(D3DXVECTOR2 ScrollPos)
{
	// �o���b�g�̕`��
	for (int i = 0; i < BOOTS_BULLET_NUM; i++)
	{
		m_Bullet[i].Draw(ScrollPos);	// �`��
	}

}



//==================================================================
// �����o�֐�
//==================================================================
/*******************************************************************************
* �֐���	:	
* ����	:	
* �Ԃ�l	:	
* ����	:	�t�@�C���[�u�[�c�̋N���i�o���b�g���������ɏo���āA�L�����N�^�[��������������j
********************************************************************************/
bool CFireBoots::ActivateFireBoots(D3DXVECTOR2 Pos, D3DXVECTOR2 BulletMove, D3DXVECTOR2 BulletSize, float Attack, float HP)
{
	// ���˂����o���b�g�̐����A�����𒴂��Ă����玸�s��Ԃ�
	if (m_nUsedBulletNum >= BOOTS_BULLET_NUM) return (false);

	// �o���b�g�̔z�u
	for (int i = 0; i < BOOTS_BULLET_NUM; i++)
	{
		// ���̃o���b�g���g�p���Ȃ玟�̃o���b�g��
		if (m_Bullet[i].GetUseFlag()) continue;

		// ���g�p�̃o���b�g���Z�b�g
		m_Bullet[i].SetBullet(Pos, BulletSize, BulletMove, Attack, HP);
		m_nUsedBulletNum++;		// ���˂����o���b�g�̐������Z

		// ������Ԃ�
		return (true);
	}

	// �o���b�g���Z�b�g�ł��Ȃ��������Ă��Ƃ�����A���s��Ԃ�
	return (false);
}




//==================================================================
// �Z�b�^�[�֐�
//==================================================================
///*******************************************************************************
//* �֐���	:	bool CFireBoots::SetFireBoots(D3DXVECTOR2* UserPos)
//* ����	:	�t�@�C���[�u�[�c�𑕒�����L�����N�^�̍��W���i�[����ϐ��ւ̃|�C���^
//* �Ԃ�l	:	����(true) or ���s(false)
//* ����	:	�t�@�C���[�u�[�c�𑕒�����
//********************************************************************************/
//bool CFireBoots::SetFireBoots(D3DXVECTOR2* UserPos)
//{
//	// ���łɑ�������Ă����Ԃł���Ύ��s��Ԃ�
//	if (m_pPosition != NULL) return (false);
//
//	// �|�C���^���Z�b�g
//	m_pPosition = UserPos;
//
//	// ������Ԃ�
//	return (true);
//}
//
///*******************************************************************************
//* �֐���	:	void CFireBoots::UnsetFireBoots()
//* ����	:	void
//* �Ԃ�l	:	����(true) or ���s(false)
//* ����	:	�t�@�C���[�u�[�c�̉���
//********************************************************************************/
//bool CFireBoots::UnsetFireBoots()
//{
//	// ���łɉ�������Ă����Ԃł���Ύ��s��Ԃ�
//	if (m_pPosition == NULL) return (false);
//
//	// �|�C���^��NULL���Z�b�g
//	m_pPosition = NULL;
//
//	// ������Ԃ�
//	return (true);
//}
//
