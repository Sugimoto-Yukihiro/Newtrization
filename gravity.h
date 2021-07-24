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

	void Init();
//	void Update(CMapchip MapchipInf);
	void Update();
//	void Uninit();

//	bool HitCheckMapchip(CMapchip MapchipInf, int* retIdxNumX, int* retIdxNumY);	// �}�b�v�`�b�v�Ƃ̓����蔻������

	//------------------- �Z�b�^�[�֐�
	void SetGravityObjectPos(D3DXVECTOR2 Pos);
	void SetGravityObjectSize(D3DXVECTOR2 Size);
	void SetGravityObjectDirection(int Direction);
	void SetGravityWait(float GravityWait);
	void SetGravityFlag(bool Flag);

	void SetAnotherForce(float Force);

	//------------------- �Q�b�^�[�֐�
	D3DXVECTOR2 GetGravityObjectPos();
	D3DXVECTOR2 GetGravityObjectSize();
	int GetGravityObjectDirection();
	float GetGravityWait();
	float GetAnotherForce();
	int GetGravityFlameCnt();				// �o�߃t���[�����̎擾
	bool GetGravityFlag();					

private:
	//------------------- �����o�ϐ�
	D3DXVECTOR2 m_Position;		// ���̂̒��S���W
	D3DXVECTOR2 m_ObjectSize;	// ���̂̃T�C�Y
	int m_nDirection;		// �d�͂̌���
	float m_GravityWait;		// �d�͉����x
	float m_fForce;				// �d�͈ȊO�ɉ�����Ă����
	int m_nFlameCount;			// �o�ߎ���
	bool m_bFall;				// �d�͏����̃t���O
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
