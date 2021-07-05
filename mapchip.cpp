//==================================================================
//
// �}�b�v�`�b�v���� [mapchip.cpp]
// Auther : ���{�K�G
//
//==================================================================

#include "main.h"
#include "renderer.h"
#include "mapchip.h"	// �}�b�v�`�b�v
#include "game.h"		// �Q�[�����

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
	D3DXVECTOR2 ScrollPos;
	float offset_x, offset_y;
	int numx, numy, nDrawChipNumX, nDrawChipNumY;

	// �\�����W�̎擾("ScrollPos"���X�N���[�����W)
	ScrollPos = GetScrollPos();

	// �`�悷��}�b�v�`�b�v�̍ō��̕\�����W�̎Z�o
	offset_x = numx * m_vChipSize.x - ScrollPos->x;	// ���ʒu
	offset_y = numy * m_vChipSize.y - ScrollPos->y;	// �c�ʒu


	//------------------- �`�悷��}�b�v�`�b�v�̍ō��̃C���f�b�N�X�ԍ��̎Z�o
	numx = (int)ScrollPos->x / m_vChipSize.x;		// �X�N���[�����W��荶���i��ʊO�j�ɂ���}�b�v�`�b�v��
	numy = (int)ScrollPos->y / m_vChipSize.y;		// �X�N���[�����W���㑤�i��ʊO�j�ɂ���}�b�v�`�b�v��

	// �`�悷��`�b�v�����Z�o
	nDrawChipNumX = SCREEN_WIDTH / m_vChipSize.x;	// ������(x��)�̃`�b�v��
	nDrawChipNumY = SCREEN_HEIGHT / m_vChipSize.y;	// �c����(y��)�̃`�b�v��

	// �}�b�v�`�b�v���ꖇ���`��
	for (int iy = numy; iy < (numy + nDrawChipNumY); iy++)
	{
		for (int ix = numx; ix < (numx + nDrawChipNumX); ix++)
		{
			// �}�b�v�̔ԍ����擾
			int nChipId = m_pMapChipData[ (iy * m_nChipNumX) + ix];

			// �`�b�v�̕`��ʒu���Z�o
			D3DXVECTOR2 ChipCenterPos;
			ChipCenterPos.y = (float)(offset_y + (m_vChipSize.y * iy));		// �w�i�̕\�����WY
			ChipCenterPos.x = (float)(offset_x + (m_vChipSize.x  * ix));	// �w�i�̕\�����WX

			ChipCenterPos.y += m_vChipSize.y * 0.5f;
			ChipCenterPos.x += m_vChipSize.x * 0.5f;

			// �`��
			DrawTexture(g_VertexBuffer, g_Texture[m_nTexNo]);	// �`����W�����S�w��̂Ƃ�

		//	// �����蔻�菈���̃`�b�v�̏ꍇ �� �����蔻��̃}�b�v�`�b�v�ϐ���p��
		//	for (int i = 0; i < WALL_NUM_PATTARN; i++)
		//	{
		//		if (chip_id == WallNum[i])
		//		{
		//			// ���W��\�����W���烏�[���h���W�ɕϊ�
		//			VECTOR worldPos = ChipCenterPos;
		//			worldPos.ix += ScrollPos->ix;
		//			worldPos.y += ScrollPos->y;
		//			SetMapChipData(worldPos, chip_id, y, ix);	// �}�b�v�`�b�v�ϐ��ɏ�����
		//		}
		//	}

		}
	}

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

