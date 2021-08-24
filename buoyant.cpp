//==================================================================
//
// ���͉������� [buoyant.cpp]
// Auther : ���{�K�G
//
//==================================================================

#include "main.h"		// ���C��
#include "buoyant.h"	// ���͏����w�b�_�[
#include "collision.h"	// �����蔻��

//==================================================================
// �R���X�g���N�^�E�f�X�g���N�^
//==================================================================
CBuoyant::CBuoyant()	// �R���X�g���N�^
{
	Init();	// �����o�ϐ��̏������̂�
}

CBuoyant::~CBuoyant()	// �f�X�g���N�^
{

}

//==================================================================
// ����������
//==================================================================
void CBuoyant::Init(char* TextureName)
{
	//------------------- �����o�ϐ��̏�����
	m_Area = ZERO_VECTOR2;
	m_CenterPos = ZERO_VECTOR2;
	m_Direction = ZERO_VECTOR2;
	m_Force = 0.0f;
	m_bUse = false;		// ���g�p�ŏ�����

	// �e�N�X�`���̏�����
	m_Texture.Init();
	if (TextureName) m_Texture.CreateTextureInf(TextureName);	// �e�N�X�`�����̐���
}

//==================================================================
// �I������
//==================================================================
void CBuoyant::Uninit()
{
	//------------------- �����o�ϐ��̏I������
//	m_Area = ZERO_VECTOR2;
//	m_CenterPos = ZERO_VECTOR2;
//	m_Direction = ZERO_VECTOR2;
//	m_Force = 0.0f;
//	m_bUse = false;

	// �e�N�X�`���̏I������
	m_Texture.Uninit();
	m_Texture.ReleaseTextureInf();
}

//==================================================================
// �X�V����
//==================================================================
void CBuoyant::Update()
{

}

//==================================================================
// �`�揈��
//==================================================================
void CBuoyant::Draw(D3DXVECTOR2 ScrollPos)
{
	// �`��ʒu���Z�o
	m_Texture.SetTexPos(m_CenterPos - ScrollPos);	// �\�����W�n�ɃZ�b�g

	// �e�N�X�`���`��
	m_Texture.DrawTexture();
}


//****************************************************
// �֐���	�Fvoid AddBuoyandForce(D3DXVECTOR2 *Pos);
// ����		�F���͂�ΏۃI�u�W�F�N�g�ɉ����āA�ړ�������
// ����		�F�ΏۃI�u�W�F�N�g�̍��W
// �߂�l	�Fvoid
//****************************************************
void CBuoyant::AddBuoyandForce(D3DXVECTOR2 *Pos)
{
	// ���͂�������
	*Pos += m_Direction * m_Force;	// �^����́��i�����j*�i�͂̑傫���j
}

//****************************************************
// �֐���	�Fbool HitCheck(D3DXVECTOR2 *Pos, D3DXVECTOR2 Size);
// ����		�F�����Ɏw�肳�ꂽ�I�u�W�F�N�g�Ƃ̓����蔻��i��`�j���s���āA
//				�������Ă����炻�̃I�u�W�F�N�g�ɕ��͂�������
// ����		�F�ΏۃI�u�W�F�N�g�̒��S���W, �ΏۃI�u�W�F�N�g�̃T�C�Y
// �߂�l	�F�������Ă���itrue�j or �������Ă��Ȃ��ifalse�j
//****************************************************
bool CBuoyant::HitCheck(D3DXVECTOR2 *Pos, D3DXVECTOR2 Size)
{
	// �����蔻����s
	if ( CollisionBB(*Pos, m_CenterPos,
					Size, m_Area) )
	{	// �������Ă������̏���
		// ���͂�������
		AddBuoyandForce(Pos);

		// �������Ă���
		return(true);
	}

	// �������Ă��Ȃ�
	return(false);
}


//==================================================================
// �Z�b�^�[�֐�
//==================================================================
bool CBuoyant::SetBuoyandErea(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, D3DXVECTOR2 Dir, float Force)	// ���͉����G���A�̃Z�b�g
{
	// �g�p���Ȃ� false ��Ԃ�
	if (m_bUse) return(false);

	m_Area = Size;					// �͈͂��Z�b�g
	m_Texture.SetTexSize(m_Area);	// �e�N�X�`���̑傫�����Z�b�g
	m_CenterPos = Pos;				// ���S���W���Z�b�g
	m_Direction = Dir;				// �������Z�b�g
	m_Force = Force;				// �͂��Z�b�g
	m_bUse = true;					// �g�p���ɂ���

	// �F��Ԃ�����
	m_Texture.SetTexColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

	// ������Ԃ�
	return(true);
}

void CBuoyant::SetDirection(D3DXVECTOR2 Dir)	// ���͂̕������Z�b�g
{
	// �O�̂��߃m�[�}���C�Y���ăZ�b�g����
	D3DXVec2Normalize(&m_Direction, &Dir);
}
