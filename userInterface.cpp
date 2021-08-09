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
static ID3D11ShaderResourceView	*g_Texture[UI_TEX_TYPE_MAX] = { NULL };	// �e�N�X�`�����

// �e�N�X�`���̃t�@�C����
static char* g_TextureName[] = {
	"data/TEXTURE/UI/HP_gage/gage.png",			// UI_TEX_TYPE_HPgage
	"data/TEXTURE/UI/HP_gage/gage_cover.png",	// UI_TEX_TYPE_HPgage_Cover
//	"data/TEXTURE/player/player01_Back_Not_Invisible.png",	// TexNo : 1

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
	for (int i = 0; i < UI_TEX_TYPE_MAX; i++)
	{
		// �������������s
		m_Texture[i].Init();	// ��U�[���ŏ�����
	}

	//------------------- �e�N�X�`���̏����ʂŃZ�b�g
	m_Texture[UI_TEX_TYPE_HPgage].SetTexPos(D3DXVECTOR2(HP_GAGE_WIDTH * 0.5f, HP_GAGE_HEIGHT * 0.5f));
	m_Texture[UI_TEX_TYPE_HPgage].SetTexSize( D3DXVECTOR2(HP_GAGE_WIDTH, HP_GAGE_HEIGHT) );
	m_Texture[UI_TEX_TYPE_HPgage].SetTexColor( HP_GAGE_COLOR );

	D3DXVECTOR2 Pos = m_Texture[UI_TEX_TYPE_HPgage].GetTexPos();
	Pos.x *= 0.5f;
		m_Texture[UI_TEX_TYPE_HPgage_Cover].SetTexPos(Pos);
	m_Texture[UI_TEX_TYPE_HPgage_Cover].SetTexSize( D3DXVECTOR2(HP_GAGE_COVER_WIDTH, HP_GAGE_COVER_HEIGHT) );

}



//=============================================================================
// �I������
//=============================================================================
void CGameUI::Uninit()
{
	// �e�N�X�`�����
	ReleaseGameUITexture();

	// �e�N�X�`���N���X�̏I������
	for (int i = 0; i < UI_TEX_TYPE_MAX; i++)
	{
		m_Texture[i].Uninit();	// �I���������s
	}
}


//=============================================================================
// �X�V����
//=============================================================================
void CGameUI::Update()
{

	// �v���C���[��HP�̔䗦���v�Z���A�Q�[�W�̒�����ݒ�
	{
		CPlayer PlayerInf;
		D3DXVECTOR2 GageSize;	// ���݂̃Q�[�W�̃T�C�Y
		float rate;				// �䗦

		PlayerInf = *GetGame()->GetPlayer();	// �v���C���[�̏����擾
		rate = PlayerInf.GetCurrentHP() / PlayerInf.GetHP();	// �v���C���[��HP�̔䗦���擾

		GageSize = m_Texture[UI_TEX_TYPE_HPgage].GetTexSize();	// ���݂̃Q�[�W�̑傫�����擾
		GageSize.x = HP_GAGE_WIDTH * rate;		// �Q�[�W�̕����A�䗦���������l�ɃZ�b�g

		// �ŏI�I�ȃQ�[�W�̑傫�����Z�b�g
		m_Texture[UI_TEX_TYPE_HPgage].SetTexSize(GageSize);	// �Z�b�g
	}



}



//=============================================================================
// �`�揈��
//=============================================================================
void CGameUI::Draw()
{
	// �S�Ẵe�N�X�`����`��
	for (int i = 0; i < UI_TEX_TYPE_MAX; i++)
	{
		m_Texture[i].DrawTexture(g_Texture[i]);	// �`�揈�����s
	}
}



// �e�N�X�`���̐���
void CreateGameUITexture(void)
{
	// �S�Ẵe�N�X�`�����𐶐�
	for (int i = 0; i < UI_TEX_TYPE_MAX; i++)
	{
		CreateTexture(g_TextureName[i], &g_Texture[i]);	// �e�N�X�`������
	}
}

// �e�N�X�`���̉��
void ReleaseGameUITexture(void)
{
	// �S�Ẵe�N�X�`�����𐶐�
	for (int i = 0; i < UI_TEX_TYPE_MAX; i++)
	{
		ReleaseTexture(&g_Texture[i]);	// �e�N�X�`�����
	}
}