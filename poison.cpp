//=============================================================================
//
// �ŏ��� [poison.cpp]
// Author : ���{�K�G
//
//=============================================================================

#include "main.h"
#include "poison.h"

#include "game.h"

// �R���X�g���N�^
CPoison::CPoison()
{
	Init();
}

// �f�X�g���N�^
CPoison::~CPoison()
{
}

//=============================================================================
// ����������
//=============================================================================
void CPoison::Init(D3DXVECTOR2* myLegPos, float* myHP, float Attack, int Wait)
{
//	m_pMapchipInf = Mapchip;	// �}�b�v�`�b�v���̃Z�b�g
	m_pLegPosition = myLegPos;	// �L�����N�^�̍��W�̏����Z�b�g
	m_pHitPointInf = myHP;		// �L�����N�^HP�ւ̃A�N�Z�X
	m_fAttack = Attack;			// �ł̍U���͂̃Z�b�g
	m_nFlameCnt = 0;			// �o�߃t���[���̓[��
	m_nFlameWait = Wait;		// wait�l���Z�b�g
}



//=============================================================================
// �I������
//=============================================================================
void CPoison::Uninit()
{
//	m_pMapchipInf = NULL;			// �}�b�v�`�b�v���̃Z�b�g
	m_pLegPosition = NULL;			// �L�����N�^�̍��W�̏����Z�b�g
	m_pHitPointInf = NULL;			// �L�����N�^HP�ւ̃A�N�Z�X
	m_nFlameCnt = m_nFlameWait = 0;	// �o�߃t���[���Ɋւ���ϐ���������
}



//=============================================================================
// �X�V����
//=============================================================================
void CPoison::Update()
{
	// �o�߃t���[���������Z
	m_nFlameCnt++;

	// �̗͂����t���[���ɂȂ����Ƃ�
	if (m_nFlameCnt >= m_nFlameWait)
	{
		// �̗͍��
		*m_pHitPointInf -= m_fAttack;

		// �o�߃t���[���������Z�b�g
		m_nFlameCnt = 0;
	}

}