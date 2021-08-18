//==================================================================
//
// �o���b�g���� [bullet.cpp]
// Auther : ���{�K�G
//
//==================================================================
#pragma once

#include "texture.h"

//*****************************************************************************
// enum
//*****************************************************************************


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBullet
{
public:
	CBullet();	// �R���X�g���N�^
	~CBullet();	// �f�X�g���N�^

	void Init(char* pTextureName = NULL, int TexDivX = 1, int TexDivY = 1, int AnimWait = 0);	// ����������
	void Uninit();						// �I������
	void Update();						// �X�V����
	void Draw(D3DXVECTOR2 ScrollPos);	// �`�揈��

	bool SetBullet(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, D3DXVECTOR2 Move, float Attack, float HP);
	bool UnsetBullet();	// �g�p���Ă���o���b�g�̉��


	//------------------- �Z�b�^�[�֐�
	void SetPosition(D3DXVECTOR2 Pos) { m_Position = Pos; };	// �o���b�g�̈ʒu���Z�b�g
	void SetSize(D3DXVECTOR2 Size) { m_TexBullet.SetTexSize(Size); };			// �o���b�g�̑傫�����Z�b�g
	void SetMove(D3DXVECTOR2 Move) { m_Move = Move; };			// �o���b�g�̈ړ��ʂ��Z�b�g
	void SetAttack(float Attack) { m_fAttack = Attack; };		// �o���b�g�̍U���͂��Z�b�g
//	void SetHP(float HP) { m_fHitPoint = HP; } ;				// �o���b�g��HP����Z�b�g
//	void SetBulletType(int Type) { m_nBulletType = Type; } ;	// �o���b�g�̎�ނ��Z�b�g


	//------------------- �Q�b�^�[�֐�
	D3DXVECTOR2 GetPosition() { return m_Position; };	// �o���b�g�̈ʒu���擾
	D3DXVECTOR2 GetSize() { return m_TexBullet.GetTexSize(); };		// �o���b�g�̑傫�����擾
	D3DXVECTOR2 GetMove() { return m_Move; };			// �o���b�g�̈ړ��ʂ��擾
	float GetAttack() { return m_fAttack; };			// �o���b�g�̍U���͂��擾
//	float GetHP() { return m_fHitPoint; } ;				// �o���b�g��HP���擾
//	int GetBulletType() { return m_nBulletType; } ;		// �o���b�g�̎�ނ��擾
	bool GetUseFlag() { return m_bUse; };				// �o���b�g�̎g�p�t���O���擾


private:
	ID3D11ShaderResourceView	*m_Texture;	// �e�N�X�`�����
	CTexture		m_TexBullet;	// �e�N�X�`���N���X�̃C���X�^���X
	D3DXVECTOR2		m_Position;		// �o���b�g�̍��W
//	D3DXVECTOR2		m_Size;			// �o���b�g�̑傫��
	D3DXVECTOR2		m_Move;			// �o���b�g��1�t���[��������̈ړ���
	float			m_fAttack;		// �o���b�g�̍U����
//	float			m_fHitPoint;	// �o���b�g��HP
//	int				m_nBulletType;	// �o���b�g�̎��
	bool			m_bUse;			// �o���b�g�̎g�p�t���O
};



