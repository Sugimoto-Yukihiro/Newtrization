//=============================================================================
//
// �^�C�g����ʏ��� [opening.cpp]
// Author : ���Α�q
//
//=============================================================================
#include "main.h"
#include "opening.h"

#include "renderer.h"
#include "input.h"		// �L�[�E�Q�[���p�b�h����
#include "fade.h"		// �t�F�[�h
//#include "sound.h"	// �T�E���h
#include "texture.h"	// �X�v���C�g����



//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_WIDTH				(SCREEN_WIDTH)	// �w�i�T�C�Y
#define TEXTURE_HEIGHT				(SCREEN_HEIGHT)	// 
#define TEXTURE_MAX					(1)				// �e�N�X�`���̐�

#define TEXTURE_WIDTH_LOGO			(480)			// ���S�T�C�Y
#define TEXTURE_HEIGHT_LOGO			(80)			// 

#define NEXT_MODE					MODE_TITLE		// ���̃��[�h
#define KEY_MODE_CHANGE				GetKeyboardTrigger(DIK_RETURN)
#define PAD_MODE_CHANGE				IsButtonTriggered(0, BUTTON_START) || IsButtonTriggered(0, BUTTON_B)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer				*g_VertexBuffer = NULL;				// ���_���
static ID3D11ShaderResourceView	*g_Texture[TEXTURE_MAX] = { NULL };	// �e�N�X�`�����

static char *g_TexturName[] = {
	"data/TEXTURE/bg_opening.jpg",
};

//=============================================================================
// ����������
//=============================================================================
void CModeOpening::Init()
{
	// �I�[�v�j���O�Ŏg�p����e�N�X�`���ƃo�b�t�@�𐶐�
	CreateOpeningTextureAndBuffer();

	m_Logo.Init();	// ���S�̏�����
	
}

//=============================================================================
// �I������
//=============================================================================
void CModeOpening::Uninit(void)
{
	// �e�N�X�`���ƃo�b�t�@�̉��
	ReleaseOpeningTextureAndBuffer();
}

//=============================================================================
// �X�V����
//=============================================================================
void CModeOpening::Update(void)
{
	//------------------- �L�[�E�Q�[���p�b�g�ł̓��͂Ŏ��̃��[�h��
	if (KEY_MODE_CHANGE)
	{// Enter��������A�X�e�[�W��؂�ւ���
		SetFade(FADE_OUT, NEXT_MODE);	// �t�F�[�h���Ď��̃��[�h��
	//	SetMode(NEXT_MODE);				// ���̃��[�h�ɃV�[���J��
	}
	// �Q�[���p�b�h�œ��͏���
	else if (PAD_MODE_CHANGE)
	{
		SetFade(FADE_OUT, NEXT_MODE);	// �t�F�[�h���Ď��̃��[�h��
	//	SetMode(NEXT_MODE);				// ���̃��[�h�ɃV�[���J��
	}

	if (m_bflag_beta == true)
	{
		m_fbeta -= 0.02f;
		if (m_fbeta <= 0.0f)
		{
			m_fbeta = 0.0f;
			m_bflag_beta = false;
		}
	}
	else
	{
		m_fbeta += 0.02f;
		if (m_fbeta >= 1.0f)
		{
			m_fbeta = 1.0f;
			m_bflag_beta = true;
		}
	}

#ifdef _DEBUG	// �f�o�b�O����\������
	//char *str = GetDebugStr();
	//sprintf(&str[strlen(str)], " PX:%.2f PY:%.2f", g_Pos.x, g_Pos.y);
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void CModeOpening::Draw(void)
{
	// �`��̑O����
	PresetDrawOpening();

	// �e�N�X�`���`��
	m_Logo.DrawTexture(g_VertexBuffer, g_Texture[0]);

}



void CreateOpeningTextureAndBuffer()
{
	//�e�N�X�`������
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		
	}

	// ���_�o�b�t�@����
	CreateVertexBuffer(&g_VertexBuffer);
}

void ReleaseOpeningTextureAndBuffer()
{
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (g_Texture[i])
		{
			g_Texture[i]->Release();
			g_Texture[i] = NULL;
		}
	}

}

void PresetDrawOpening(void)
{
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �}�g���N�X�ݒ�
	SetWorldViewProjection2D();

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);
}
