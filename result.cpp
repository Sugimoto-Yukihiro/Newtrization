//=============================================================================
//
// ���U���g��ʏ��� [result.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "result.h"

#include "fade.h"		// �t�F�[�h����
#include "input.h"		// �L�[�E�Q�[���p�b�h���͏���
#include "renderer.h"	// �����_�����O����
//#include "sound.h"	// �T�E���h
#include "sprite.h"		// �X�v���C�g
//#include "score.h"	// �X�R�A

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
static ID3D11Buffer				*g_VertexBuffer = NULL;		// ���_���
static ID3D11ShaderResourceView	*g_Texture[TEXTURE_MAX] = { NULL };	// �e�N�X�`�����

static char *g_TexturName[] = {
	"data/TEXTURE/bg_result.png",
	//"data/TEXTURE/result_logo.png",
	//"data/TEXTURE/number16x32.png",
};

static bool						g_Use;						// true:�g���Ă���  false:���g�p
static float					g_w, g_h;					// ���ƍ���
static D3DXVECTOR3				g_Pos;						// �|���S���̍��W
static int						g_TexNo;					// �e�N�X�`���ԍ�

//=============================================================================
// ����������
//=============================================================================
HRESULT InitResult(void)
{
	ID3D11Device *pDevice = GetDevice();

	//�e�N�X�`������
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		g_Texture[i] = NULL;
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TexturName[i],
			NULL,
			NULL,
			&g_Texture[i],
			NULL);
	}


	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);


	// �ϐ��̏�����
	g_Use   = true;
	g_w     = TEXTURE_WIDTH;
	g_h     = TEXTURE_HEIGHT;
	g_Pos   = D3DXVECTOR3(g_w/2, 50.0f, 0.0f);
	g_TexNo = 0;

	// BGM�Đ�
//	PlaySound(SOUND_LABEL_BGM_sample002);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitResult(void)
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

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResult(void)
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

#ifdef _DEBUG	// �f�o�b�O����\������
	//char *str = GetDebugStr();
	//sprintf(&str[strlen(str)], " PX:%.2f PY:%.2f", g_Pos.x, g_Pos.y);
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResult(void)
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

	// ���U���g�̔w�i��`��
	{
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[0]);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	//	SetSprite(g_VertexBuffer, 0.0f, 0.0f, g_w, g_h, 0.0f, 0.0f, 1.0f, 1.0f);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetVertex(g_VertexBuffer, 0.0f, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);


		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
	}

	//// ���U���g�̃��S��`��
	//{
	//	// �e�N�X�`���ݒ�
	//	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[1]);

	//	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	//	SetSprite(g_VertexBuffer, g_Pos.x, g_Pos.y, TEXTURE_WIDTH_LOGO, TEXTURE_HEIGHT_LOGO, 0.0f, 0.0f, 1.0f, 1.0f);

	//	// �|���S���`��
	//	GetDeviceContext()->Draw(4, 0);
	//}


	// �X�R�A�\��
	//{
	//	// �e�N�X�`���ݒ�
	//	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[2]);

	//	// ��������������
	//	int number = GetScore();
	//	for (int i = 0; i < SCORE_DIGIT; i++)
	//	{
	//		// ����\�����錅�̐���
	//		float x = (float)(number % 10);

	//		// �X�R�A�̈ʒu��e�N�X�`���[���W�𔽉f
	//		float pw = 16*4;			// �X�R�A�̕\����
	//		float ph = 32*4;			// �X�R�A�̕\������
	//		float px = 600.0f - i*pw;	// �X�R�A�̕\���ʒuX
	//		float py = 300.0f;			// �X�R�A�̕\���ʒuY

	//		float tw = 1.0f / 10;		// �e�N�X�`���̕�
	//		float th = 1.0f / 1;		// �e�N�X�`���̍���
	//		float tx = x * tw;			// �e�N�X�`���̍���X���W
	//		float ty = 0.0f;			// �e�N�X�`���̍���Y���W

	//		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	//		SetSpriteColor(g_VertexBuffer, px, py, pw, ph, tx, ty, tw, th,
	//			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//		// �|���S���`��
	//		GetDeviceContext()->Draw(4, 0);

	//		// ���̌���
	//		number /= 10;
	//	}

	//}

}




