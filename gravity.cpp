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
	// �S�Ẵ����o�ϐ����[���̒l�ɃZ�b�g
	m_Position = ZERO_VECTOR2;
	m_nDirection = GRAVITY_DEFAULT;
	m_GravityWait = DEFAULT_GRAVITY_WAIT;
	m_nFlameCount = 0;
	m_bFall = true;	// �d�͏�����"true"���f�t�H���g�ɃZ�b�g
}

//=============================================================================
// �I������
//=============================================================================


//=============================================================================
// �X�V����
//=============================================================================
//void CGravity::Update(CMapchip MapchipInf)
void CGravity::Update()
{
	if (!m_bFall) return;	// �d�̓t���O�������Ă��Ȃ�������A���������Ȃ�

	int nIdxNumX = 0, nIdxNumY = 0;

	// �o�߃t���[���������Z
	m_nFlameCount++;

	// �d�͂̕����ɂ���ď������e��ς���
	if (m_nDirection == GRAVITY_DEFAULT)	// �f�t�H���g�i�������j
	{
		// �ω�����̂�x���W
		m_Position.y += m_GravityWait * m_nFlameCount;
	}
	else if (m_nDirection == GRAVITY_LEFT)	// ������
	{
		// �ω�����̂�x���W
		m_Position.x -= m_GravityWait * m_nFlameCount;
	}

//	// �}�b�v�`�b�v�Ƃ̓����蔻������
//	if (HitCheckMapchip(MapchipInf, &nIdxNumX, &nIdxNumY))
//	{	// �������Ă������̏���
//		// ���W����
//		m_Position.x = MapchipInf.GetMapchipSize().x * nIdxNumX;
//		m_Position.y = MapchipInf.GetMapchipSize().y * nIdxNumY;
//
//		// �t���[���J�E���g���Z�b�g
//		m_nFlameCount = 0;
//
//		// �d�͏����t���O��܂�
//		m_bFall = false;
//	}
}

//=============================================================================
// �}�b�v�`�b�v�Ƃ̓����蔻��
//=============================================================================
//bool CGravity::HitCheckMapchip(CMapchip MapchipInf, int* retIdxNumX, int* retIdxNumY)
//{
//	//	D3DXVECTOR2 pos1, pos2;
//	D3DXVECTOR2 pos;
//
//	//	pos1 = pos2 = m_Position;	// ���S���W�ŏ�����
//	pos = m_Position;	// ���S���W�ŏ�����
//
//	// �}�b�v�`�b�v�Ɠ������Ă��邩����
//	switch (m_nDirection)	// �d�͂̌����ɂ���ē����蔻��̎d����ς���
//	{
//	case GRAVITY_DEFAULT:	// �������̂Ƃ�
//
//		// pos�ɂ͍����̍��W���i�[
//		pos.x -= m_ObjectSize.x * 0.5f;
//		pos.y += m_ObjectSize.y * 0.5f;
//
//		for (int yi = 0; yi < 2; yi++)	// �Ƃ肠����������Ă݂�
//		{
//			for (int xi = 0; xi < (m_ObjectSize.x / MapchipInf.GetMapchipSize().x); xi++)
//			{
//				pos.x += MapchipInf.GetMapchipSize().x * xi;	// ���W�̈ʒu���A�}�b�v�`�b�v�̃T�C�Y�������E��
//
//				// �����蔻��`�F�b�N
//				if (MapchipInf.GetMapchipNo(pos, retIdxNumX, retIdxNumY) == 1)
//				{
//					return (true);	// �������Ă���
//				}
//			}
//		}
//		break;
//
//	case GRAVITY_LEFT:
//
//		break;
//
//	default:
//		break;
//	}
//
//	// �������Ă��Ȃ�
//	return false;
//}



//=============================================================================
// �Z�b�^�[�֐�
//=============================================================================
void CGravity::SetGravityObjectPos(D3DXVECTOR2 Pos)
{
	m_Position = Pos;
}

void CGravity::SetGravityObjectSize(D3DXVECTOR2 Size)
{
	m_ObjectSize = Size;
}

void CGravity::SetGravityObjectDirection(int Direction)
{
	m_nDirection = Direction;
}

void CGravity::SetGravityWait(float GravityWait)
{
	m_GravityWait = GravityWait;
}

void CGravity::SetGravityFlag(bool Flag)
{
	// �t���O��"false"�̂Ƃ�
	if (Flag == false)
	{
		m_nFlameCount = 0;	// �t���[���J�E���g�����Z�b�g
	}

	m_bFall = Flag;
}

//=============================================================================
// �Q�b�^�[�֐�
//=============================================================================
D3DXVECTOR2 CGravity::GetGravityObjectPos()
{
	return m_Position;
}

D3DXVECTOR2 CGravity::GetGravityObjectSize()
{
	return m_ObjectSize;
}

int CGravity::GetGravityObjectDirection()
{
	return m_nDirection;
}

float CGravity::GetGravityWait()
{
	return m_GravityWait;
}

int CGravity::GetGravityFlameCnt()
{
	return m_nFlameCount;
}

bool CGravity::GetGravityFlag()
{
	return m_bFall;
}
