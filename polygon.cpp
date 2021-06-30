//=============================================================================
//
// �v���C���[���� [polygon.cpp]
// Author : 
//
//=============================================================================

#include "polygon.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//#define TEXTURE_NAME				"data/TEXTURE/bg000.png"	//�e�N�X�`����
//#define TEXTURE_NAME				"data/TEXTURE/oshi.png"		//�e�N�X�`����
#define TEXTURE_NAME				"data/TEXTURE/uramaru.jpg"	//�e�N�X�`����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void SetVertex(void);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;		// ���_���
static ID3D11ShaderResourceView		*g_Texture = NULL;			// �e�N�X�`�����

static int							g_TexNo;					// �e�N�X�`���ԍ�

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPolygon(void)
{
	ID3D11Device *pDevice = GetDevice();

	//�e�N�X�`������
	g_Texture = NULL;
	D3DX11CreateShaderResourceViewFromFile(
		GetDevice(),
		TEXTURE_NAME,
		NULL,
		NULL,
		&g_Texture,
		NULL);

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);

	// ���_�o�b�t�@�X�V
	SetVertex();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPolygon(void)
{
	// ���_�o�b�t�@�̉��
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}

	// �e�N�X�`���̉��
	if (g_Texture)
	{
		g_Texture->Release();
		g_Texture = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePolygon(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPolygon(void)
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
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);
}


//=============================================================================
// ���_�f�[�^�ݒ�
//=============================================================================
void SetVertex(void)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);
}
