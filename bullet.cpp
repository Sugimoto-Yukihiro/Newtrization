//==================================================================
//
// �o���b�g���� [bullet.cpp]
// Auther : ���{�K�G
//
//==================================================================

#include "main.h"
#include "bullet.h"

#include "game.h"	// �Q�[��
#include "debugproc.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^�E�f�X�g���N�^
//=============================================================================
CBullet::CBullet()	// �R���X�g���N�^
{
	Init();	// ������
}

CBullet::~CBullet()	// �f�X�g���N�^
{

}



//=============================================================================
// ����������
// ����	�F	�e�N�X�`���̃t�@�C����, ��������, �c������, �A�j���[�V������Wait�l
//=============================================================================
void CBullet::Init(char* pTextureName, int TexDivX, int TexDivY, int AnimWait)
{
	//�e�N�X�`������
	if ( pTextureName ) CreateTexture(pTextureName, &m_Texture);

	// �����o�ϐ��̏�����
	m_Texture = NULL;
	m_TexBullet.Init();	// �e�N�X�`���̏�����
	m_Position = ZERO_VECTOR2;
	m_Move = ZERO_VECTOR2;
	m_fAttack = 0.0f;
	m_bUse = false;		// false(���g�p)�ŏ�����

	// �A�j���[�V�������̃Z�b�g
	m_TexBullet.SetTexDivideX(TexDivX);	// �������i���j
	m_TexBullet.SetTexDivideY(TexDivY);	// �������i�c�j
	m_TexBullet.SetAnimWait(AnimWait);	// �A�j���[�V�����̐؂�ւ��t���[���l
}



//=============================================================================
// �I������
//=============================================================================
void CBullet::Uninit()
{
	// �����o�ϐ��̏I������
	m_bUse = false;		// false(���g�p)�ɃZ�b�g
	m_fAttack = 0.0f;
	m_Move = ZERO_VECTOR2;
	m_Position = ZERO_VECTOR2;
	m_TexBullet.Uninit();	// �e�N�X�`���̏I������

	// �e�N�X�`�����
	ReleaseTexture(m_Texture);
	m_Texture = NULL;	// ��������̂�NULL���Z�b�g
}



//=============================================================================
// �X�V����
// ����	�F	�X�e�[�W�̑傫��
//=============================================================================
void CBullet::Update()
{
	// ���̃o���b�g���g���Ă��Ȃ��Ȃ�I��
	if (!m_bUse) return;

	// �A�j���[�V����
	m_TexBullet.UpdateAnimIndex(0, m_TexBullet.GetTexDivideX() * m_TexBullet.GetTexDivideY());	// �ŏ�����Ō�܂ň�C�ɃA�j���[�V����

	// �ړ��𔽉f
	m_Position += m_Move;

	PrintDebugProc("�y�o���b�g���W�zX: %f, Y: %f\n", m_Position.x, m_Position.y);

}



//=============================================================================
// �`�揈��
// ����	�F	�X�N���[�����W
//=============================================================================
void CBullet::Draw(D3DXVECTOR2 ScrollPos)
{
	// ���̃o���b�g���g���Ă��Ȃ��Ȃ�I��
	if (!m_bUse) return;

	//------------------- �e�N�X�`���`��
	m_TexBullet.SetTexPos(m_Position - ScrollPos);	// �\�����W�̃Z�b�g
	m_TexBullet.DrawTexture(m_Texture);				// �`��
}



//=============================================================================
// �o���b�g�̔��ːݒ�
//=============================================================================
bool CBullet::SetBullet(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, D3DXVECTOR2 Move, float Attack, float HP)
{
	// ���Ɏg�p���Ȃ玸�s��Ԃ�
	if (m_bUse) return (false);

	m_Position = Pos;	// �o��������ʒu���Z�b�g
	m_TexBullet.SetTexSize(Size);	// �`�悷��T�C�Y���Z�b�g
	m_Move = Move;		// �ړ��ʂ��Z�b�g
	m_fAttack = Attack;	// �U���͂��Z�b�g
	m_bUse = true;		// true(�g�p��)���Z�b�g

	// ������Ԃ�
	return (true);
}

//=============================================================================
// �g�p���o���b�g�̉��
//=============================================================================
bool CBullet::UnsetBullet()
{
	// ���ɖ��g�p�Ȃ玸�s��Ԃ�
	if (!m_bUse) return (false);

	// ���g�p�ɂ���
	m_bUse = false;

	// ������Ԃ�
	return (true);
}