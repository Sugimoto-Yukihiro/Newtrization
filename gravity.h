//=============================================================================
//
// �d�͏��� [gravity.h]
// Author : ��_�C��Y, ���{�K�G
//
//=============================================================================
#pragma once

#include "mapchip.h"	// �}�b�v�`�b�v����

//*****************************************************************************
// �}�N����`
//*****************************************************************************



//*****************************************************************************
// �񋓌^
//*****************************************************************************
enum DIRECTION
{
	GRAVITY_DEFAULT, 
	GRAVITY_LEFT
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
	void Update(CMapchip MapchipInf);
//	void Uninit();

	bool HitCheckMapchip(CMapchip MapchipInf, int* retIdxNumX, int* retIdxNumY);	// �}�b�v�`�b�v�Ƃ̓����蔻������

	//------------------- �Z�b�^�[�֐�
	void SetGravityObjectPos(D3DXVECTOR2 Pos);
	void SetGravityObjectSize(D3DXVECTOR2 Size);
	void SetGravityObjectDirection(DIRECTION Direction);
	void SetGravityWait(float GravityWait);
	void SetGravityFlag(bool Flag);

	//------------------- �Q�b�^�[�֐�
	D3DXVECTOR2 GetGravityObjectPos();
	D3DXVECTOR2 GetGravityObjectSize();
	DIRECTION GetGravityObjectDirection();
	float GetGravityWait();
	int GetGravityFlameCnt();
	bool GetGravityFlag();

private:
	D3DXVECTOR2 m_Position;		// ���̂̒��S���W
	D3DXVECTOR2 m_ObjectSize;	// ���̂̃T�C�Y
	DIRECTION m_nDirection;		// �d�͂̌���
	float m_GravityWait;		// �d�͉����x
	int m_nFlameCount;			// �o�ߎ���
	bool m_bFall;				// �d�͏����̃t���O
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
