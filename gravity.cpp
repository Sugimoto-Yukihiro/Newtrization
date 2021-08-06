//=============================================================================
//
// �d�͏��� [gravity.cpp]
// Author : ��_�C��Y, ���{�K�G
//
//=============================================================================

#include "main.h"
#include "gravity.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define DEFAULT_GRAVITY_WAIT		(0.55f)		// �d�͂̒l(�f�t�H���g�̎�)
#define LEFT_GRAVITY_WAIT			(0.55f)		// �d�͂̒l(�������̎�)



//=============================================================================
// �R���X�g���N�^�E�f�X�g���N�^
//=============================================================================
CGravity::CGravity()	// �R���X�g���N�^
{
	Init();	// �����o�ϐ�������������
}

CGravity::~CGravity()	// �f�X�g���N�^
{

}



//=============================================================================
// ����������
//=============================================================================
void CGravity::Init()
{
	// �S�Ẵ����o�ϐ����f�t�H���g�̒l�ɃZ�b�g
	m_Position = ZERO_VECTOR2;
	m_GravityWait = DEFAULT_GRAVITY_WAIT;
	m_fVerocity = 0.0f;	/* �����x�N�g���ɂ����� */
	m_nDirection = GRAVITY_DEFAULT;
	m_nFlameCount = 0;
	m_bFall = true;	// �d�͏�����"true"���f�t�H���g�ɃZ�b�g
}



//=============================================================================
// �I������
//=============================================================================
void CGravity::Uninit()
{
	// �S�Ẵ����o�ϐ����[���̒l�ɃZ�b�g
	m_Position = ZERO_VECTOR2;
	m_GravityWait = 0.0f;
	m_fVerocity = 0.0f;
	m_nDirection = 0;
	m_nFlameCount = 0;
	m_bFall = true;	// �d�͏�����"true"���f�t�H���g�ɃZ�b�g
}



//=============================================================================
// �X�V����
//=============================================================================
void CGravity::Update()
{
	if (!m_bFall) return;	// �d�̓t���O�������Ă��Ȃ�������A���������Ȃ�

	int nIdxNumX = 0, nIdxNumY = 0;

	// �o�߃t���[���������Z
	m_nFlameCount++;

	// �d�͂̕����ɂ���ď������e��ς���
	if (m_nDirection == GRAVITY_DEFAULT)	// �f�t�H���g�i�������j
	{
		// �ω�����̂͂����W
		m_fVerocity = m_GravityWait * m_nFlameCount;	// �y�d�� * �o�ߎ��ԁz�ő������Z�o
		m_Position.y += m_fVerocity;		// �����𑫂�
	}
	else if (m_nDirection == GRAVITY_LEFT)	// ������
	{
		// �ω�����̂͂����W
		m_fVerocity = m_GravityWait * m_nFlameCount;	// �y�d�� * �o�ߎ��ԁz�ő������Z�o
		m_Position.x -= m_fVerocity;		// �����𑫂�
	}

}



//=============================================================================
// �Z�b�^�[�֐�
//=============================================================================
// ���W�̃Z�b�g
void CGravity::SetGravityObjectPos(D3DXVECTOR2 Pos)
{
	m_Position = Pos;
}

// �傫���̃Z�b�g
void CGravity::SetGravityObjectSize(D3DXVECTOR2 Size)
{
	m_ObjectSize = Size;
}

// ���̃I�u�W�F�N�g�ɂ�����d�͂̑傫�����Z�b�g
void CGravity::SetGravityWait(float GravityWait)
{
	m_GravityWait = GravityWait;
}

// ���̃I�u�W�F�N�g�̑������Z�b�g
void CGravity::SetGravitySpeed(float Speed)
{
	m_fVerocity = Speed;	// �������Z�b�g
}

// ���̃I�u�W�F�N�g�̏d�͂̕������Z�b�g
void CGravity::SetGravityObjectDirection(int Direction)
{
	m_nDirection = Direction;	
}

// �d�͏������s���t���O�̃Z�b�g
void CGravity::SetGravityFlag(bool Flag)
{
	// �t���O��"false"�̂Ƃ�
	if (!Flag) m_nFlameCount = 0;	// �t���[���J�E���g�����Z�b�g
	m_bFall = Flag;	// �d�͏����t���O�̃Z�b�g
}

//=============================================================================
// �Q�b�^�[�֐�
//=============================================================================
// ���W�̎擾
D3DXVECTOR2 CGravity::GetGravityObjectPos()
{
	return m_Position;		// ���W��Ԃ�
}

// �傫���̎擾
D3DXVECTOR2 CGravity::GetGravityObjectSize()
{
	return m_ObjectSize;	// ���̃I�u�W�F�N�g�̑傫����Ԃ�
}

// ���̃I�u�W�F�N�g�ɂ�����d�͂̑傫�����擾
float CGravity::GetGravityWait()
{
	return m_GravityWait;	// �d�͂̑傫���̕ϐ��l��Ԃ�
}

// ���̃I�u�W�F�N�g�̑������擾
float CGravity::GetGravitySpeed()
{
	return m_fVerocity;		// ���x��Ԃ�
}

// ���̃I�u�W�F�N�g�̏d�͂̌������擾
int CGravity::GetGravityObjectDirection()
{
	return m_nDirection;	// �d�͕�����Ԃ�
}

// �o�ߎ��ԁi�t���[���j���̎擾
int CGravity::GetGravityFlameCnt()
{
	return m_nFlameCount;	// �o�߃t���[������Ԃ�
}

// �d�͏������s���t���O�̎擾
bool CGravity::GetGravityFlag()
{
	return m_bFall;			// �d�̓t���O�̐^�U�l��Ԃ�
}
