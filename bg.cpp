//=============================================================================
// �w�i���� [bg.cpp]
// Author : ���{�K�G
//=============================================================================
#include "main.h"
#include "bg.h"

#include "renderer.h"
#include "texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NUM			(1)			// �g�p�e�N�X�`���̐�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;		// ���_���
static ID3D11ShaderResourceView		*g_Texture[TEXTURE_NUM] = { NULL };			// �e�N�X�`�����

static int							g_TexNo;					// �e�N�X�`���ԍ�

// �e�N�X�`���̃t�@�C����
static char* g_TextureName[] = {
	"data/TEXTURE/bg_game.jpg",
};

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBg(void)
{
	ID3D11Device *pDevice = GetDevice();

	//�e�N�X�`������
	for (int i = 0; i < TEXTURE_NUM; i++)
	{
		g_Texture[i] = NULL;
		D3DX11CreateShaderResourceViewFromFile(
			GetDevice(),
			g_TextureName[i],
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

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBg(void)
{
	// ���_�o�b�t�@�̉��
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}

	for (int i = 0; i < TEXTURE_NUM; i++)
	{
		// �e�N�X�`���̉��
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
void UpdateBg(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBg(void)
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

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[0]);

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetVertex(g_VertexBuffer, 0.0f, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);
}
