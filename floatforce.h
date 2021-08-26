//==================================================================
//
// ���͉������� [floatforce.h]
// Auther : ���{�K�G
//
//==================================================================
#pragma once

#include "texture.h"	// �e�N�X�`���`�揈��

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CFloatForce		// ���͉����N���X
{
public:
	CFloatForce();		// �R���X�g���N�^
	~CFloatForce();	// �f�X�g���N�^

	void Init(char* TextureName = NULL);	// ����������
	void Uninit();	// �I������
	void Update();	// �X�V����
	void Draw(D3DXVECTOR2 ScrollPos);	// �`�揈��

	void AddFloatForce(D3DXVECTOR2 *Pos);				// ���͂������Ĉړ�������
	bool HitCheck(D3DXVECTOR2 *Pos, D3DXVECTOR2 Size);	// �����蔻��

	//------------------- �Z�b�^�[�֐�
	bool SetFloatForceErea(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, D3DXVECTOR2 Dir, float Force, D3DXCOLOR Color);	// ���͉����G���A�̃Z�b�g

	void SetAreaSize(D3DXVECTOR2 Size) { m_Area = Size; };		// �G���A�̑傫�����擾
	void SetDirection(D3DXVECTOR2 Dir);							// ���͂̕������擾
	void SetCenterPos(D3DXVECTOR2 Pos) { m_CenterPos = Pos; };	// �G���A�̈ʒu���擾
	void SetForceValue(float Force) { m_Force = Force; };		// ���͂̑傫�����擾
	void SetUseFlag(bool Flag) { m_bUse = Flag; };				// �g�p�t���O�̎擾

	//------------------- �Q�b�^�[�֐�
	D3DXVECTOR2	GetAreaSize() { return m_Area; };		// �G���A�̑傫�����擾
	D3DXVECTOR2	GetCenterPos() { return m_CenterPos; };	// �G���A�̈ʒu���擾
	D3DXVECTOR2	GetDirection() { return m_Direction; };	// ���͂̕������擾
	float		GetForceValue() { return m_Force; };	// ���͂̑傫�����擾
	bool		GetUseFlag() { return m_bUse; };		// �g�p�t���O�̎擾

private:
	//------------------- �����o�ϐ�
	CTexture		m_Texture;		// �G���A�̕`��
	D3DXVECTOR2		m_Area;			// ���͉����G���A
	D3DXVECTOR2		m_CenterPos;	// ���͉����G���A�̒��S�_
	D3DXVECTOR2		m_Direction;	// ���͂̕����i�P�ʃx�N�g���j
	float			m_Force;		// ���͂̑傫��
	bool			m_bUse;			// ������g�p���Ă��邩
};

