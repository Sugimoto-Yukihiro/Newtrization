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


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11ShaderResourceView	*g_Texture = { NULL };	// �e�N�X�`�����

// �e�N�X�`���̃t�@�C����
static char *g_TextureName[] = {
	"data/TEXTURE/mapchip/mapchip_sample.png",	// MAPCHIP_STAGE_Sample
	"data/TEXTURE/mapchip/Mapchip.png",			// MAPCHIP_STAGE_Game
};


//=============================================================================
// �R���X�g���N�^�E�f�X�g���N�^
//=============================================================================
CMapchip::CMapchip()	// �R���X�g���N�^
{
	//------------------- �����o�ϐ��̏�����
	m_vChipSize = MAPCHIP_SIZE_DEFAULT;	// �P�̃`�b�v�̑傫�����Z�b�g�i�j
	m_nChipNumX = -1;					// �}�b�v�`�b�v�̗񐔂��Z�b�g
	m_nChipNumY = -1;					// �}�b�v�`�b�v�̗񐔂��Z�b�g

}

CMapchip::~CMapchip()	// �f�X�g���N�^
{

}



//=============================================================================
// ����������
//=============================================================================
void CMapchip::Init(char* pMapFileName, int TexDivX, int TexDivY, D3DXVECTOR2 ChipSize)
{
	//------------------- �e�N�X�`���֘A�̏�����
	CTexture::Init();
	SetTexDivideX(TexDivX);	// ���������w��
	SetTexDivideY(TexDivY);	// ���������w��

	//------------------- �����o�ϐ��̏�����
	m_vChipSize = ChipSize;	// �P�̃`�b�v�̑傫��

	// �}�b�v�`�b�v�z��̃Z�b�g
	if (pMapFileName == NULL)	// NULL�Ȃ�[���ŏ�����
	{
		for (int i = 0; i < MAPCHIP_NUM_MAX; i++) m_MapChipData[i] = 0;
		m_nChipNumX = 0;	// �}�b�v�`�b�v�̗񐔂̓[��
		m_nChipNumY = 0;	// �}�b�v�`�b�v�̍s���̓[��
	}
	else LoadMapchipData(pMapFileName);	// �}�b�v�`�b�v�f�[�^��ǂݍ���
}



//=============================================================================
// �I������
//=============================================================================
void CMapchip::Uninit()	// �S�Ă̕ϐ����O�N���A
{
	// �}�b�v�`�b�v�z��̃N���A
	for (int i = 0; i < MAPCHIP_NUM_MAX; i++) m_MapChipData[i] = 0;

	m_vChipSize = ZERO_VECTOR2;	// �`�b�v�̑傫�����N���A
	m_nChipNumX = 0;			// �}�b�v�`�b�v�̗񐔂��N���A
	m_nChipNumY = 0;			// �}�b�v�`�b�v�̍s�����N���A

	//------------------- �e�N�X�`���N���X�̏I������
	CTexture::Uninit();
}



//=============================================================================
// �X�V����
//=============================================================================
void CMapchip::Update()
{
	// �`��̊���W���X�V
//	SetBasePos(ScrollPosition);
}



//=============================================================================
// �`�揈��
//=============================================================================
void CMapchip::Draw()
{
	// �g�p����ϐ��̐錾
	D3DXVECTOR2 ScrollPos;
	float offset_x, offset_y;
	int numx, numy;
	int nDrawChipNumX, nDrawChipNumY;

	// �\�����W�̎擾("ScrollPos"���X�N���[�����W)
	ScrollPos = GetGame()->GetScrollPosition();

	numx = (int)(ScrollPos.x / GetMapchipSize().x) - 1;	// �X�N���[�����W��荶���i��ʊO�j�ɂ���}�b�v�`�b�v��
	numy = (int)(ScrollPos.y / GetMapchipSize().y) - 1;	// �X�N���[�����W���㑤�i��ʊO�j�ɂ���}�b�v�`�b�v��

	// �}�b�v�`�b�v�\�����W�̎Z�o
	offset_x = -ScrollPos.x;
	offset_y = -ScrollPos.y;

	// �`�悷��`�b�v�����Z�o
	nDrawChipNumX = SCREEN_WIDTH / (int)GetMapchipSize().x + numx;	// ������(x��)�̃`�b�v��
	nDrawChipNumY = SCREEN_HEIGHT / (int)GetMapchipSize().y + numy;	// �c����(y��)�̃`�b�v��

	// �}�b�v�`��
	for (int y = numy; y < nDrawChipNumY + 3; y++)	// 2�͒��r���[�ɏo�Ă���
	{
		for (int x = numx; x < nDrawChipNumX + 3; x++)
		{
			// �}�b�v�̔ԍ����擾
		//	int nChipId = m_MapChipData[(y + numy) * GetMapchipNumX() + (x + numx)];	// 
			int nChipId = m_MapChipData[y * GetMapchipNumX() + x];	// 

			// �`�b�v�ԍ���0�Ԃ̂Ƃ��͕`�悵�Ȃ�
			if(nChipId == 0) continue;

			// �`�b�v�̕`��ʒu���Z�o
			D3DXVECTOR2 ChipPos;
			ChipPos.y = (float)(offset_y + (GetMapchipSize().y * y));	// �w�i�̕\�����WY
			ChipPos.x = (float)(offset_x + (GetMapchipSize().x * x));	// �w�i�̕\�����WX

			// �`��
			DrawChip(ChipPos, nChipId);	// �`����W�����S�w��̂Ƃ�
		}
	}

}

// �`�b�v�P���̕`��
void CMapchip::DrawChip(D3DXVECTOR2 Pos, int Num)
{
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture);

	float tw = 1.0f / GetTexDivideX();	// �e�N�X�`���̕�
	float th = 1.0f / GetTexDivideY();	// �e�N�X�`���̍���
	float tx = (float)(Num % GetTexDivideX()) * tw;	// �e�N�X�`���̍���X���W
	float ty = (float)(Num / GetTexDivideX()) * th;	// �e�N�X�`���̍���Y���W

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetVertex(Pos.x, Pos.y, GetMapchipSize().x, GetMapchipSize().y, tx, ty, tw, th);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);
}



//=============================================================================
// �����o�֐�
//=============================================================================
//****************************************************
// ����		�F �}�b�v�`�b�v�z����A�t�@�C������ǂݍ���ŃZ�b�g
// ����		�F �}�b�v�`�b�v�̃t�@�C�����ichar�^�j
// �߂�l	�F ����(1), ���s(0)
//****************************************************
int CMapchip::LoadMapchipData(char* pFileName)
{
	// �G���[�`�F�b�N
	if (pFileName == NULL) 0;	// NULL�Ȃ玸�s��Ԃ�
 
	char* pLoad = NULL;	// �ǂݍ��񂾂��̂�ۑ����郁�����������|�C���^
	// Csv�t�@�C���́A�R�����g�������폜������Ԃ̂��̂�ǂݍ��݁i�J���}�ŋ�؂�ꂽ���l�f�[�^�𒊏o�j
	LoadCsvFile(pFileName, pLoad, 8, ",");

	// �J���}��؂�̐��l��ǂݎ���đ������
	SetMapChipData(pLoad);

	delete[] pLoad;
	return 1;	// ����
}




//=============================================================================
// �Z�b�^�[�֐�
//=============================================================================
//****************************************************
// ����		�F �}�b�v�`�b�v�z��̃Z�b�g
// ����		�F �}�b�v�`�b�v�̏��ichar�^�j
// �߂�l	�F ����(1), ���s(0)
//****************************************************
int CMapchip::SetMapChipData(const char* pCsvString)
{
	int nTokenCnt = 0;	// ���l��������g�[�N���̃J�E���g �� �}�b�v�`�b�v�̗�
	int nLinesCnt = 0;	// �s���̃J�E���g
	char* pCopyStr;		// �����̕�������R�s�[�����������������|�C���^
	char* pToken;		// strtok �Ő؂蔲�����g�[�N���������|�C���^

	// �����̕�������R�s�[
	pCopyStr = new char [ strlen(pCsvString) + NULL_SIZE ];	// �������m��
	memset(pCopyStr, '\0', strlen(pCsvString) + NULL_SIZE);	// ������
	memcpy(pCopyStr, pCsvString, strlen(pCsvString));		// ������R�s�[

	// �擪����A���Ɏ�����擾����
	pToken = pCopyStr;
	while (pToken = strtok(pToken, ","))
	{
		// ���s�R�[�h���������Ƃ�
		if (strrchr(pToken, '\n') != NULL)
		{
			nLinesCnt++;	// �}�b�v�`�b�v�̍s�������Z
		}

		m_MapChipData[nTokenCnt] = atoi(pToken);		// ���l���
		nTokenCnt++;		// �}�b�v�`�b�v�̗񐔂����Z

		pToken = NULL;		// ���̎�����擾���邽��NULL���Z�b�g
	}

	// �}�b�v�`�b�v�̗񐔂��Z�b�g
	SetMapchipNumX(nTokenCnt / nLinesCnt);

	// �}�b�v�`�b�v�̍s�����Z�b�g
	SetMapchipNumY(nLinesCnt);

	// �R�s�[����������̉��
	delete[] pCopyStr;

	return 0;	// ����
}

// �`��̊���W���Z�b�g
//void CMapchip::SetMapchipBasePos(D3DXVECTOR2 Pos)
//{
//	m_vChipBasePos = Pos;
//}

// �P�̃`�b�v�̑傫�����Z�b�g
void CMapchip::SetMapchipSize(D3DXVECTOR2 Size)
{
	m_vChipSize = Size;
}

// �}�b�v�`�b�v�̗񐔂��Z�b�g
void CMapchip::SetMapchipNumX(int Num)
{
	m_nChipNumX = Num;
}

// �}�b�v�`�b�v�̗񐔂��Z�b�g
void CMapchip::SetMapchipNumY(int Num)
{
	m_nChipNumY = Num;
}

// �w�肵���ӏ��̃}�b�v�`�b�v�ԍ���ύX����
void CMapchip::SetMapchipNo(int No, int X, int Y)
{
	m_MapChipData[(Y * m_nChipNumX) + X];	// �ԍ����i�[
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
D3DXVECTOR2 CMapchip::GetStageSize()
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

// �}�b�v�`�b�v�z��̗v�f��(�ꎟ��)���A���W�ɕϊ�
D3DXVECTOR2 CMapchip::GetMapchipPosition(int nIdxNo)
{
	// �g�p����ϐ��̐錾
//	D3DXVECTOR2 ans;
//	int X, Y;
//
//	X = nIdxNo % m_nChipNumX;	// �񐔂��Z�o
//	Y = nIdxNo / m_nChipNumX;	// �񐔂��Z�o
//
//	ans.x = m_vChipSize.x * X;	// X���W���Z�b�g
//	ans.y = m_vChipSize.y * Y;	// Y���W���Z�b�g
//
//	ans.x += m_vChipSize.x * 0.5f;	// �`�b�v�̔����̒����𑫂��ă`�b�v�̒��S���W�ɂ���
//	ans.y += m_vChipSize.y * 0.5f;	// �`�b�v�̔����̒����𑫂��ă`�b�v�̒��S���W�ɂ���
//
//	// �`�b�v�̒��S���W��Ԃ�
//	return ans;

	// �œK����
	return D3DXVECTOR2(	m_vChipSize.x * (nIdxNo % m_nChipNumX) + m_vChipSize.x * 0.5f,
						m_vChipSize.y * (nIdxNo / m_nChipNumX) + m_vChipSize.y * 0.5f );	// �`�b�v�̒��S���W��Ԃ�
}

//****************************************************
// ����		�F �w�肳�ꂽ���W�ɂ���`�b�v�ԍ����擾�B��2,3�����ɋA���Ă���ŏ��l�͂O
// ����		�F �C�ӂ̍��W, �}�b�v�`�b�v�̗v�f��(��)��Ԃ��|�C���^, �}�b�v�`�b�v�̗v�f��(�c)��Ԃ��|�C���^
// �߂�l	�F �������Ɏw�肳�ꂽ�ӏ��̃}�b�v�`�b�v�̔ԍ�
//****************************************************
int CMapchip::GetMapchipNo(D3DXVECTOR2 Pos, int* retIdxNumX, int* retIdxNumY)
{
	int nIdxX, nIdxY;	// ���̊֐����Ŏg�p����ϐ��̐錾

	nIdxX = (int)(Pos.x / m_vChipSize.x);	// �}�b�v�`�b�v���W��x�����߂�
	nIdxY = (int)(Pos.y / m_vChipSize.y);	// �}�b�v�`�b�v���W��y�����߂�

	// �}�b�v�`�b�v���W�� X, y ���ꂼ��̒l��Ԃ�
	if (retIdxNumX != NULL) *retIdxNumX = nIdxX;
	if (retIdxNumY != NULL) *retIdxNumY = nIdxY;

	return m_MapChipData[nIdxX + (nIdxY * m_nChipNumX)];	// ���߂����W�l����A�v�f�������߂āA���̐��l��Ԃ�
//	return m_MapChipData[ (int)(Pos.x / m_vChipSize.x) + (int)(Pos.y / m_vChipSize.y) * m_nChipNumX ];	// ������

}

// �}�b�v�`�b�v�e�N�X�`���̐���
void CreateMapchipTexture(int MapchipPattarn)
{
	// �e�N�X�`������
	CreateTexture(g_TextureName[MapchipPattarn], &g_Texture);
}

// �}�b�v�`�b�v�e�N�X�`���̉��
void ReleaseMapchipTexture(void)
{
	// �e�N�X�`�����
	ReleaseTexture(&g_Texture);
}
