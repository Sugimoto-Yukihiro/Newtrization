//=============================================================================
//
// �d�͏��� [gravity.h]
// Author : ��_�C��Y, ���{�K�G
//
//=============================================================================
#pragma once

//#include "mapchip.h"	// �}�b�v�`�b�v����

//*****************************************************************************
// �}�N����`
//*****************************************************************************



//*****************************************************************************
// �񋓌^
//*****************************************************************************
enum
{
	GRAVITY_DEFAULT, 
	GRAVITY_LEFT,

	GRAVITY_DIRECTION_MAX
};


//*****************************************************************************
// �N���X
//*****************************************************************************
class CGravity
{
public:
	CGravity();		// �R���X�g���N�^
	~CGravity();	// �f�X�g���N�^

	void Init();	// ������
	void Update();	// �X�V

	//------------------- �Z�b�^�[�֐�
	void SetGravityObjectPos(D3DXVECTOR2 Pos);		// ���W�̃Z�b�g
	void SetGravityObjectSize(D3DXVECTOR2 Size);	// �傫���̃Z�b�g
	void SetGravityObjectDirection(int Direction);	// ���̃I�u�W�F�N�g�̏d�͂̌������Z�b�g
	void SetGravityWait(float GravityWait);			// ���̃I�u�W�F�N�g�ɂ�����d�͂̑傫�����Z�b�g
	void SetGravityFlag(bool Flag);					// �d�͏������s���t���O�̃Z�b�g

//	void SetAnotherForce(float Force);

	//------------------- �Q�b�^�[�֐�
	D3DXVECTOR2 GetGravityObjectPos();	// ���W�̎擾
	D3DXVECTOR2 GetGravityObjectSize();	// �傫���̎擾
	int GetGravityFlameCnt();			// �o�߃t���[�����̎擾
	int GetGravityObjectDirection();	// ���̃I�u�W�F�N�g�̏d�͂̌������Z�b�g
	float GetGravityWait();				// ���̃I�u�W�F�N�g�ɂ�����d�͂̑傫�����Z�b�g
	bool GetGravityFlag();				// �d�͏������s���t���O�̃Z�b�g

//	float GetAnotherForce();

private:
	//------------------- �����o�ϐ�
	D3DXVECTOR2 m_Position;		// ���̂̒��S���W
	D3DXVECTOR2 m_ObjectSize;	// ���̂̃T�C�Y
	int m_nDirection;			// �d�͂̌���
	float m_GravityWait;		// �d�͉����x
//	float m_fForce;				// �d�͈ȊO�ɉ�����Ă����
	int m_nFlameCount;			// �o�ߎ���
	bool m_bFall;				// �d�͏����̃t���O
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
