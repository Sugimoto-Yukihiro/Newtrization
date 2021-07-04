//==================================================================
//
// �}�b�v�`�b�v���� [mapchip.cpp]
// Auther : ���{�K�G
//
//==================================================================

#include "main.h"
#include "renderer.h"
#include "mapchip.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_MAX		(1)		// �g�p�e�N�X�`���̐�


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer				*g_VertexBuffer = NULL;				// ���_���
static ID3D11ShaderResourceView	*g_Texture[TEXTURE_MAX] = { NULL };	// �e�N�X�`�����

static char *g_TexturName[] = {
	"data/TEXTURE/player.png",
};


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMapchip::CMapchip()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMapchip::~CMapchip()
{

}



//=============================================================================
// ����������
//=============================================================================
void CMapchip::Init()
{


}

void InitMapchip()
{
	// �e�N�X�`������
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

}



//=============================================================================
// �I������
//=============================================================================
void CMapchip::Uninit()
{

}

void UninitMapchip()
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
void CMapchip::Update()
{

}


void UpdateMapchip()
{

}



//=============================================================================
// �`�揈��
//=============================================================================
void CMapchip::Draw()
{

}


void DrawMapchip()
{

}



//=============================================================================
// �Q�b�^�[�֐�
//=============================================================================
// �w�肳�ꂽ���W�ɂ���`�b�v�ԍ����擾
int CMapchip::GetMapchipNo(D3DXVECTOR2 Pos)
{
	int cx = (int)Pos.x / m_vChipSize.x;
	int cy = (int)Pos.y / m_vChipSize.y;

	return m_pMapChipData[cx + (cy * m_nChipNumX)];
}

