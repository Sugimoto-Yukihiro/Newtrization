//=============================================================================
//
// UI���� [userInterface.cpp]
// Author : ���{�K�G
//
//=============================================================================

#include "main.h"
#include "userInterface.h"

#include "game.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
#define CASE_DRAW_TOPLEFT	case GAMEUI_TEX_TYPE_HPgage: case GAMEUI_TEX_TYPE_HPgage_Cover:		// ���㌴�_�ŕ`�悷��e�N�X�`���̎��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11ShaderResourceView	*g_Texture[GAMEUI_TEX_TYPE_MAX] = { NULL };	// �e�N�X�`�����

// �e�N�X�`���̃t�@�C����
static char* g_TextureName[] = {
	"data/TEXTURE/UI/HP_gage/gage.png",			// GAMEUI_TEX_TYPE_HPgage
	"data/TEXTURE/UI/HP_gage/gage_cover.png",	// GAMEUI_TEX_TYPE_HPgage_Cover
};

//=============================================================================
// �R���X�g���N�^�E�f�X�g���N�^
//=============================================================================
CGameUI::CGameUI()	// �R���X�g���N�^
{

}

CGameUI::~CGameUI()	// �f�X�g���N�^
{

}



//=============================================================================
// ����������
//=============================================================================
void CGameUI::Init()
{
	// �e�N�X�`������
	CreateGameUITexture();

	// �e�N�X�`���N���X�̏���������
	for (int i = 0; i < GAMEUI_TEX_TYPE_MAX; i++)
	{
		// �������������s
		m_GameTexture[i].Init();	// ��U�[���ŏ�����
	}

	//------------------- �e�N�X�`���̏����ʂŃZ�b�g
	m_GameTexture[GAMEUI_TEX_TYPE_HPgage].SetTexPos( HP_GAGE_POS_TOPLEFT );	// �`��ʒu���Z�b�g�i����j
	m_GameTexture[GAMEUI_TEX_TYPE_HPgage].SetTexSize( HP_GAGE_SIZE );		// �T�C�Y���Z�b�g
	m_GameTexture[GAMEUI_TEX_TYPE_HPgage].SetTexColor( HP_GAGE_COLOR );		// �F���Z�b�g

	m_GameTexture[GAMEUI_TEX_TYPE_HPgage_Cover].SetTexPos( HP_GAGE_POS_TOPLEFT );	// �`��ʒu���Z�b�g�i����j
	m_GameTexture[GAMEUI_TEX_TYPE_HPgage_Cover].SetTexSize( HP_GAGE_SIZE );			// �T�C�Y���Z�b�g
}



//=============================================================================
// �I������
//=============================================================================
void CGameUI::Uninit()
{
	// �e�N�X�`�����
	ReleaseGameUITexture();

	// �e�N�X�`���N���X�̏I������
	for (int i = 0; i < GAMEUI_TEX_TYPE_MAX; i++)
	{
		m_GameTexture[i].Uninit();	// �I���������s
	}
}


//=============================================================================
// �X�V����
//=============================================================================
void CGameUI::Update()
{

	// �v���C���[��HP�̔䗦���v�Z���A�`�悷��Q�[�W�̕����Z�b�g
	{
		CPlayer PlayerInf;		// ���݂̃v���C���[�̏���ۑ�����C���X�^���X
		D3DXVECTOR2 GageSize;	// ���݂̃Q�[�W�̃T�C�Y
		float rate;				// �䗦

		PlayerInf = *GetGame()->GetPlayer();					// �v���C���[�̏����擾
		rate = PlayerInf.GetCurrentHP() / PlayerInf.GetHP();	// �v���C���[��HP�̔䗦���擾

		GageSize = m_GameTexture[GAMEUI_TEX_TYPE_HPgage].GetTexSize();	// ���݂̃Q�[�W�̑傫�����擾
		GageSize.x = HP_GAGE_WIDTH * rate;						// �Q�[�W�̕����A�䗦���������l�ɃZ�b�g

		// �ŏI�I�ȃQ�[�W�̑傫�����Z�b�g
		m_GameTexture[GAMEUI_TEX_TYPE_HPgage].SetTexSize(GageSize);	// �Z�b�g
	}



}



//=============================================================================
// �`�揈��
//=============================================================================
void CGameUI::Draw()
{
	// �S�Ẵe�N�X�`����`��
	for (int i = 0; i < GAMEUI_TEX_TYPE_MAX; i++)	// �Q�[�����
	{
		// ����ƒ��S�̂ǂ�������_�ŕ`�悷�邩�ɂ���ď�����ς���
		if (i <= GAMEUI_TEX_DRAW_TOPLEFT_MAXNO)	m_GameTexture[i].DrawTextureTopLeft(g_Texture[i]);	// �`�揈�����s�i���㌴�_�j
		else m_GameTexture[i].DrawTexture(g_Texture[i]);	// �`�揈�����s�i���S���_�j
	}
}



// �e�N�X�`���̐���
void CreateGameUITexture(void)
{
	// �S�Ẵe�N�X�`�����𐶐�
	for (int i = 0; i < GAMEUI_TEX_TYPE_MAX; i++)
	{
		CreateTexture(g_TextureName[i], &g_Texture[i]);	// �e�N�X�`������
	}
}

// �e�N�X�`���̉��
void ReleaseGameUITexture(void)
{
	// �S�Ẵe�N�X�`�����𐶐�
	for (int i = 0; i < GAMEUI_TEX_TYPE_MAX; i++)
	{
		ReleaseTexture(&g_Texture[i]);	// �e�N�X�`�����
	}
}