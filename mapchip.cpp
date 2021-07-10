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
//#define MAPCHIP_MAX		(1)		// �g�p�e�N�X�`���̐�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer				*g_VertexBuffer = NULL;				// ���_���
static ID3D11ShaderResourceView	*g_Texture[MAPCHIP_MAX] = { NULL };	// �e�N�X�`�����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void PresetDrawMapchip();	// �`�悷��O����

// �e�N�X�`���̃t�@�C����
static char *g_TextureName[] = {
	"data/TEXTURE/player.png",		// TexNo : 0
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



//=============================================================================
// �I������
//=============================================================================
void CMapchip::Uninit()
{

}



//=============================================================================
// �X�V����
//=============================================================================
void CMapchip::Update()
{

}



//=============================================================================
// �`�揈��
//=============================================================================
void CMapchip::Draw()
{
	// �`�悷��O�ɌĂяo��
	PresetDrawMapchip();

	D3DXVECTOR2 ScrollPos;
	float offset_x, offset_y;
	int numx, numy, nDrawChipNumX, nDrawChipNumY;

	// �\�����W�̎擾("ScrollPos"���X�N���[�����W)
//	ScrollPos.x = GetPlayerPos().x - SCROLL_SET_X;	// �����͉��B��Œ����I
//	ScrollPos.x = GetPlayerPos().x - SCROLL_SET_X;	// �����͉��B��Œ����I
	ScrollPos.x = 0.0f;	// �����͉��B��Œ����I
	ScrollPos.x = 0.0f;	// �����͉��B��Œ����I

	//------------------- �`�悷��}�b�v�`�b�v�̍ō��̃C���f�b�N�X�ԍ��̎Z�o
	numx = (int)(ScrollPos.x / GetMapchipSize().x);		// �X�N���[�����W��荶���i��ʊO�j�ɂ���}�b�v�`�b�v��
	numy = (int)(ScrollPos.y / GetMapchipSize().y);		// �X�N���[�����W���㑤�i��ʊO�j�ɂ���}�b�v�`�b�v��

	// �`�悷��}�b�v�`�b�v�̍ō��̕\�����W�̎Z�o
	offset_x = (numx * GetMapchipSize().x) - ScrollPos.x;	// ���ʒu
	offset_y = (numy * GetMapchipSize().y) - ScrollPos.y;	// �c�ʒu

	// �`�悷��`�b�v�����Z�o
	nDrawChipNumX = SCREEN_WIDTH / (int)GetMapchipSize().x;	// ������(x��)�̃`�b�v��
	nDrawChipNumY = SCREEN_HEIGHT / (int)GetMapchipSize().y;	// �c����(y��)�̃`�b�v��

	// �}�b�v�`�b�v���ꖇ���`��
	for (int iy = numy; iy < (numy + nDrawChipNumY); iy++)
	{
		for (int ix = numx; ix < (numx + nDrawChipNumX); ix++)
		{
			// �}�b�v�̔ԍ����擾
			int nChipId = m_pMapChipData[ (iy * m_nChipNumX) + ix];

			// �`�b�v�̕`��ʒu���Z�o
			D3DXVECTOR2 ChipCenterPos;
			ChipCenterPos.y = (float)(offset_y + (GetMapchipSize().y * iy));		// �w�i�̕\�����WY
			ChipCenterPos.x = (float)(offset_x + (GetMapchipSize().x  * ix));	// �w�i�̕\�����WX

			ChipCenterPos.y += GetMapchipSize().y * 0.5f;
			ChipCenterPos.x += GetMapchipSize().x * 0.5f;

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



//=============================================================================
// �Z�b�^�[�֐�
//=============================================================================
// �}�b�v�`�b�v�z����擾
void SetMapChipData(const char* pCsvFile)
{
	
}

// ��]�t���O�̃Z�b�g
//void CMapchip::SetRotationFlag(bool Flag)
//{
//	m_bRotFlag = Flag;
//}

//=============================================================================
// �Q�b�^�[�֐�
//=============================================================================
// �}�b�v�S�̂̑傫�����擾
D3DXVECTOR2 CMapchip::GetMapSize()
{
	D3DXVECTOR2 ans;
	ans.x = m_vChipSize.x * m_nChipNumX;	// �����i�[
	ans.y = m_vChipSize.y * m_nChipNumY;	// �������i�[

	return ans;
}

// �P�̃`�b�v�̑傫�����擾
D3DXVECTOR2 CMapchip::GetMapchipSize()
{
	return m_vChipSize;
}

// �}�b�v�`�b�v�z����擾
int* CMapchip::GetMapChipData()
{
	return m_pMapChipData;
}

// �}�b�v�`�b�v�̗񐔂��擾
int CMapchip::GetMapchipNumX()
{
	return m_nChipNumX;
}

// �w�肳�ꂽ���W�ɂ���`�b�v�ԍ����擾
int CMapchip::GetMapchipNo(D3DXVECTOR2 Pos)
{
	int cx = (int)(Pos.x / m_vChipSize.x);
	int cy = (int)(Pos.y / m_vChipSize.y);

	return m_pMapChipData[cx + (cy * m_nChipNumX)];
}

// ��]�t���O�̎擾
//bool CMapchip::GetRotationFlag()
//{
//	return m_bRotFlag;
//}







void CreateMapchipTextureAndBuffer()
{
	// �e�N�X�`������
	for (int i = 0; i < MAPCHIP_MAX; i++)
	{
		CreateTexture(g_TextureName[i], &g_Texture[i]);
	}

	// ���_�o�b�t�@����
	CreateVertexBuffer(&g_VertexBuffer);

}

void ReleaseMapchipTextureAndBuffer()
{
	for (int i = 0; i < MAPCHIP_MAX; i++)
	{
		ReleaseTexture(&g_Texture[i], &g_VertexBuffer);
	}

}

void PresetDrawMapchip()
{
	PresetDraw2D(&g_VertexBuffer);
}