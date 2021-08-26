//=============================================================================
//
// �G�l�~�[���� [enemy.h]
// Author : ��_�C��Y, ���{�K�G
//
//=============================================================================
#pragma once

#include "texture.h"	// �e�N�X�`���`�揈��
#include "gravity.h"	// �d�͏���

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// enum
//*****************************************************************************
enum
{
	ENEMY_TEX_01,			// �G�l�~�[�e�N�X�`��(TexNo�F0)
	ENEMY_TEX_LEFT,		// �G�l�~�[�e�N�X�`���i�E�����j

	ENEMY_TEX_PATTARN_MAX	// ���U���g��ʂŎg�p����Ă���e�N�X�`���̑���
};


//*****************************************************************************
// �N���X
//*****************************************************************************
class CEnemy : public CTexture	//, public CGravity
{
public:
	CEnemy();
	~CEnemy();

	void Init();
	void Update();
	void Draw(D3DXVECTOR2 ScrollPos);
//	void Uninit();

	// �w��̈ʒu�ɃG�l�~�[��u������
	bool SetEnemy(D3DXVECTOR2 Pos);	// �����F���̃G�l�~�[��u�������ꏊ

	void KillEnemy();	// ���̃G�l�~�[���E������

	// �����o�ϐ��ւ̃A�N�Z�T�[�֐�
	void SetPos(D3DXVECTOR2 Pos) { m_pos = Pos; };
	D3DXVECTOR2 GetPos() { return m_pos; };

	void SetTexNo(int TexNo) { m_texNo = TexNo; };
	bool GetTexNo() { return m_texNo; };

	void SetUse(bool Use) { m_use = Use; };
	bool GetUse() { return m_use; };

private:
	D3DXVECTOR2		m_pos;			// �|���S���̍��W
//	D3DXVECTOR3		m_rot;			// �|���S���̉�]��
//	float			m_w, m_h;		// ���ƍ���
//	float			m_time;			// ���`��Ԃ̎��ԊǗ��p
//	int				m_countAnim;	// �A�j���[�V�����J�E���g
//	int				m_patternAnim;	// �A�j���[�V�����p�^�[���i���o�[
	int				m_texNo;		// �e�N�X�`���ԍ�
	bool			m_left;			// true:���ֈړ�
	bool			m_use;			// true:�g���Ă���  false:���g�p

	/* �p�����Ă��邩�炱�̃C���X�^���X�͕K�v�Ȃ� */
//	CTexture m_Tex[ENEMY_TEX_PATTARN_MAX];	// �g�p�e�N�X�`��(���enum�̃p�^�[���������p��)
};



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEnemy(void);
void UninitEnemy(void);
//void UpdateEnemy(void);
//void DrawEnemy(void);

//ENEMY *GetEnemy(void);


