//=============================================================================
//
// �d�͏��� [gravity.h]
// Author : ��_�C��Y, ���{�K�G
//
//=============================================================================
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �񋓌^
//*****************************************************************************
enum
{
	GRAVITY_DEFAULT,		// �d�͉�����
	GRAVITY_LEFT,			// �d�͍�����

	GRAVITY_DIRECTION_MAX	// ���p�^�[����
};


//*****************************************************************************
// �N���X
//*****************************************************************************
class CGravity
{
public:
	CGravity();		// �R���X�g���N�^
	~CGravity();	// �f�X�g���N�^

	void Init(D3DXVECTOR2 Pos = D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2 Size = D3DXVECTOR2(0.0f, 0.0f), float GravWait = 0.0f, int Direction = 0);	// ������
	void Uninit();	// �I������
	void Update();	// �X�V

	//------------------- �Z�b�^�[�֐�
	void SetGravityObjectPos(D3DXVECTOR2 Pos);		// ���W�̃Z�b�g
	void SetGravityObjectSize(D3DXVECTOR2 Size);	// �傫���̃Z�b�g
	void SetGravityWait(float GravityWait);			// ���̃I�u�W�F�N�g�ɂ�����d�͂̑傫�����Z�b�g
	void SetGravitySpeed(float Speed);				// ���̃I�u�W�F�N�g�̑������Z�b�g
	void SetGravityObjectDirection(int Direction);	// ���̃I�u�W�F�N�g�̏d�͂̕������Z�b�g
	void SetGravityFlag(bool Flag);					// �d�͏������s���t���O�̃Z�b�g

	//------------------- �Q�b�^�[�֐�
	D3DXVECTOR2	GetGravityObjectPos();			// ���W�̎擾
	D3DXVECTOR2	GetGravityObjectSize();			// �傫���̎擾
	float		GetGravityWait();				// ���̃I�u�W�F�N�g�ɂ�����d�͂̑傫�����擾
	float		GetGravitySpeed();				// ���̃I�u�W�F�N�g�̑������擾
	int			GetGravityObjectDirection();	// ���̃I�u�W�F�N�g�̏d�͂̌������擾
	int			GetGravityFlameCnt();			// �o�ߎ��ԁi�t���[���j���̎擾
	bool		GetGravityFlag();				// �d�͏������s���t���O�̎擾

private:
	//------------------- �����o�ϐ�
	D3DXVECTOR2	m_Position;		// ���̂̒��S���W
	D3DXVECTOR2	m_ObjectSize;	// ���̂̃T�C�Y
	float		m_GravityWait;	// �d�͂̑傫��
	float		m_fVerocity;	// �y�d�͑傫�� * �o�ߎ��ԁz �ɂ���ē�����A���̕��̂̑��x
	int			m_nDirection;	// �d�͂̌���
	int			m_nFlameCount;	// �o�ߎ��ԁi�P�ʂ̓t���[���j
	bool		m_bFall;		// �d�͏����̃t���O
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
