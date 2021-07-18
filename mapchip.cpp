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
#define MAPCHIP_SIZE_DEFAULT	D3DXVECTOR2(64.0f, 64.0f)		// �}�b�v�`�b�v�̃f�t�H���g�T�C�Y

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void PresetDrawMapchip();	// �`�悷��O����

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer				*g_VertexBuffer = NULL;						// ���_���
static ID3D11ShaderResourceView	*g_Texture = { NULL };	// �e�N�X�`�����

// �e�N�X�`���̃t�@�C����
static char *g_TextureName[] = {
	"data/TEXTURE/mapchip/mapchip_sample.png",		// MAPCHIP_STAGE_Sample
};


//=============================================================================
// �R���X�g���N�^�E�f�X�g���N�^
//=============================================================================
CMapchip::CMapchip()	// �R���X�g���N�^
{
	//------------------- �����o�ϐ��̏�����
//	SetMapchipBasePos(ZERO_VECTOR2);
	SetMapchipSize(MAPCHIP_SIZE_DEFAULT);	// �P�̃`�b�v�̑傫�����Z�b�g
	SetMapchipNumX(-1);				// �}�b�v�`�b�v�̗񐔂��Z�b�g
	SetMapchipNumY(-1);				// �}�b�v�`�b�v�̗񐔂��Z�b�g

}

CMapchip::~CMapchip()	// �f�X�g���N�^
{

}



//=============================================================================
// ����������
//=============================================================================
void CMapchip::Init()
{
	//------------------- �����o�ϐ��̏�����
	m_nChipNumX = 1;	// �}�b�v�`�b�v�̗�
	m_nChipNumY = 1;	// �}�b�v�`�b�v�̍s��

	//------------------- �e�N�X�`���֘A�̏�����
	SetTexDivideX(4);
	SetTexDivideY(4);


	// �}�b�v�`�b�v�z��̃Z�b�g
//	SetMapChipData(pTestMapChipData);
	LoadMapchipData("data/MAPCHIP/mapdata1.01.csv");
//	LoadMapchipData("data/MAPCHIP/mapdata1.02.csv");
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
	// �`��̊���W���X�V
//	SetBasePos(ScrollPosition);
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
	int numx, numy;
	int nDrawChipNumX, nDrawChipNumY;

	// �\�����W�̎擾("ScrollPos"���X�N���[�����W)
	ScrollPos = GetGame()->GetScrollPosition();

	numx = (int)(ScrollPos.x / GetMapchipSize().x) - 1;	// �X�N���[�����W��荶���i��ʊO�j�ɂ���}�b�v�`�b�v��
	numy = (int)(ScrollPos.y / GetMapchipSize().y) - 1;	// �X�N���[�����W���㑤�i��ʊO�j�ɂ���}�b�v�`�b�v��

	// �}�b�v�`�b�v�\�����W�̎Z�o
//	offset_x = GetMapchipSize().x - ScrollPos.x;
	offset_x = -ScrollPos.x;
//	offset_y = GetMapchipSize().y - ScrollPos.y;
	offset_y = -ScrollPos.y;

	// �`�悷��`�b�v�����Z�o
	nDrawChipNumX = SCREEN_WIDTH / (int)GetMapchipSize().x + numx;		// ������(x��)�̃`�b�v��
	nDrawChipNumY = SCREEN_HEIGHT / (int)GetMapchipSize().y + numy;	// �c����(y��)�̃`�b�v��

	// �}�b�v�`��
	for (int y = numy; y < nDrawChipNumY + 2; y++)
	{
		for (int x = numx; x < nDrawChipNumX + 2; x++)
		{
			// �}�b�v�̔ԍ����擾
		//	int nChipId = m_MapChipData[(y + numy) * GetMapchipNumX() + (x + numx)];	// 
			int nChipId = m_MapChipData[y * GetMapchipNumX() + x];	// 

			if(nChipId == 0) continue;

			// �`�b�v�̕`��ʒu���Z�o
			D3DXVECTOR2 ChipCenterPos;
			ChipCenterPos.y = (float)(offset_y + (GetMapchipSize().y * y));	// �w�i�̕\�����WY
			ChipCenterPos.x = (float)(offset_x + (GetMapchipSize().x * x));	// �w�i�̕\�����WX

			ChipCenterPos.y += GetMapchipSize().y * 0.5f;	// ���S���W�ɂ���
			ChipCenterPos.x += GetMapchipSize().x * 0.5f;	// ���S���W�ɂ���

			// �`��
			DrawChip(ChipCenterPos, nChipId);	// �`����W�����S�w��̂Ƃ�
		}
	}








	////------------------- �`�悷��}�b�v�`�b�v�̍ō��̃C���f�b�N�X�ԍ��̎Z�o
	//numx = (int)(ScrollPos.x / GetMapchipSize().x);		// �X�N���[�����W��荶���i��ʊO�j�ɂ���}�b�v�`�b�v��
	//numy = (int)(ScrollPos.y / GetMapchipSize().y);		// �X�N���[�����W���㑤�i��ʊO�j�ɂ���}�b�v�`�b�v��

	//// �`�悷��}�b�v�`�b�v�̍ō��̕\�����W�̎Z�o
	//offset_x = (numx * GetMapchipSize().x) - ScrollPos.x;	// ���ʒu
	//offset_y = (numy * GetMapchipSize().y) - ScrollPos.y;	// �c�ʒu

	//// �`�悷��`�b�v�����Z�o
	//nDrawChipNumX = SCREEN_WIDTH / (int)GetMapchipSize().x;		// ������(x��)�̃`�b�v��
	//nDrawChipNumY = SCREEN_HEIGHT / (int)GetMapchipSize().y;	// �c����(y��)�̃`�b�v��

	//// �}�b�v�`�b�v���ꖇ���K�v�������`��
	//for (iy = numy; iy < (numy + nDrawChipNumY); iy++)
	//{
	//	for (ix = numx; ix < (numx + nDrawChipNumX); ix++)
	//	{
	//		// �}�b�v�̔ԍ����擾
	//		int nChipId = m_MapChipData[ (iy * m_nChipNumX) + ix];

	//		// �`�b�v�ԍ����O�Ȃ�`�悵�Ȃ�
	//		if(nChipId == 0) continue;

	//		// �`�b�v�̕`��ʒu���Z�o
	//		D3DXVECTOR2 ChipCenterPos;
	//		ChipCenterPos.y = (float)(offset_y + (GetMapchipSize().y * iy));	// �w�i�̕\�����WY
	//		ChipCenterPos.x = (float)(offset_x + (GetMapchipSize().x  * ix));	// �w�i�̕\�����WX

	//		ChipCenterPos.y += GetMapchipSize().y * 0.5f;	// ���S���W�ɂ���
	//		ChipCenterPos.x += GetMapchipSize().x * 0.5f;	// ���S���W�ɂ���

	//		// �`��
	//		DrawChip(ChipCenterPos, nChipId);	// �`����W�����S�w��̂Ƃ�

	//	//	// �����蔻�菈���̃`�b�v�̏ꍇ �� �����蔻��̃}�b�v�`�b�v�ϐ���p��
	//	//	for (int i = 0; i < WALL_NUM_PATTARN; i++)
	//	//	{
	//	//		if (chip_id == WallNum[i])
	//	//		{
	//	//			// ���W��\�����W���烏�[���h���W�ɕϊ�
	//	//			VECTOR worldPos = ChipCenterPos;
	//	//			worldPos.ix += ScrollPos->ix;
	//	//			worldPos.y += ScrollPos->y;
	//	//			SetMapChipData(worldPos, chip_id, y, ix);	// �}�b�v�`�b�v�ϐ��ɏ�����
	//	//		}
	//	//	}

	//	}
	//}

}

// �`�b�v�̕`��
void CMapchip::DrawChip(D3DXVECTOR2 Pos, int Num)
{
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture);

	float tw = 1.0f / GetTexDivideX();	// �e�N�X�`���̕�
	float th = 1.0f / GetTexDivideY();	// �e�N�X�`���̍���
	float tx = (float)(Num % GetTexDivideX()) * tw;	// �e�N�X�`���̍���X���W
	float ty = (float)(Num / GetTexDivideX()) * th;	// �e�N�X�`���̍���Y���W

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSprite(g_VertexBuffer, Pos.x, Pos.y, GetMapchipSize().x, GetMapchipSize().y, tx, ty, tw, th);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);
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
	int nTokenCnt = 0;
	int nLinesCnt = 0;
	char* pCopyStr;
//	char* pLinesStr;
	char* pToken;

	// �����̕�������R�s�[
	pCopyStr = new char [ strlen(pCsvString) + NULL_SIZE ];	// �������m��
	memset(pCopyStr, '\0', strlen(pCsvString) + NULL_SIZE);	// ������
	memcpy(pCopyStr, pCsvString, strlen(pCsvString));		// ������R�s�[

	// �擪����A���Ɏ�����擾����
//	strtok(pCopyStr, ",");	// �擪�̎���
	pToken = pCopyStr;
	while (pToken = strtok(pToken, ","))
	{
		if (strrchr(pToken, '\n') != NULL)	// ���s�R�[�h���������Ƃ�
		{
			// �擪�̂P�����݂̂𒊏o
			char singleWord[2] = { "\0" };
			strncat(singleWord, pToken, 1);

			m_MapChipData[nTokenCnt] = atoi(singleWord);	// ���l���
			nTokenCnt++;	// �}�b�v�`�b�v�̗񐔂����Z
			nLinesCnt++;	// �}�b�v�`�b�v�̍s�������Z
		}
		else
		{
			m_MapChipData[nTokenCnt] = atoi(pToken);		// ���l���
			nTokenCnt++;	// �}�b�v�`�b�v�̗񐔂����Z
		}

		pToken = NULL;		// ���̎�����擾���邽��NULL���Z�b�g
	}

	// �}�b�v�`�b�v�̗񐔂��Z�b�g
	SetMapchipNumX(nTokenCnt / nLinesCnt);

	// �}�b�v�`�b�v�̍s�����Z�b�g
	SetMapchipNumY(nLinesCnt);


	// �}�b�v�`�b�v�̗񐔂��Z�o
//	SetMapchipNumX( (SerchWordOffset(pCsvString, '\n') + 1) / 2 );	// �J���}�̕�������������
//
//	// ��s�ڂ̕�������擾
////	pLinesStr = strtok(pCopyStr, "\n");
//	pLinesStr = pCopyStr;
//	do
//	{
//		char* pBuf = new char [ strlen(pLinesStr) + NULL_SIZE ];
//		strcpy(pBuf, pLinesStr);	// ������R�s�[
//
//		// �J���}�ɋ�؂�ꂽ�擪�̕������擾
//		pToken = strtok(pBuf, ",");		/* ���ꂪ�Q�s�ڈȍ~�ǂݎ��Ȃ������c!?�@���@strtok��static�ϐ����g�p���Ă��邩��I */
//		nTokenCnt = 0;	// �J�E���g���Z�b�g
//		do
//		{
//			// �g�[�N�������l�ł��邩���f
//		//	if (isdigit(pToken))
//			{
//				m_MapChipData[nTokenCnt] = atoi(pToken);	// ���l���
//
//				// �g�[�N�����̃J�E���g
//			//	nTokenCnt++;
//			}
//
//			// ���̎�����擾
//			pToken = strtok(NULL, ",");
//		} while (pToken != NULL);	// ���傪������Ȃ��Ȃ�܂ŌJ��Ԃ�
//
//		// �J�E���g�����g�[�N�������A�񐔂�ۑ����郁���o�ϐ��֑��
//	//	if (nTokenCnt > GetMapchipNumX()) SetMapchipNumX(nTokenCnt);
//
//		// �m�ۂ����q�[�v�̈�̃����������
//		delete[] pBuf;
//
//		// �s���̃J�E���g
//		nLinesCnt++;
//
//		// ���̍s�̕�������擾
//	//	pLinesStr = strtok(NULL, "\n");
//		pLinesStr += nTokenCnt;
//	} while (pLinesStr != NULL);
//
//	// �J�E���g�����s�����A�}�b�v�`�b�v�̍s����ۑ����郁���o�ϐ��֑��
//	SetMapchipNumY(nLinesCnt);


	// �R�s�[����������̉��
	delete[] pCopyStr;

	return 0;	// ����
}

// �}�b�v�`�b�v�z����A�t�@�C������ǂݍ���ŃZ�b�g
//****************************************************
// ����		�F �}�b�v�`�b�v�̃t�@�C�����ichar�^�j
// �߂�l	�F ����(1), ���s(0)
//****************************************************
int CMapchip::LoadMapchipData(char* pFileName)
{
	char* pLoad = NULL;
	LoadCsvFile(pFileName, pLoad, 8, ",");	// �ǂݍ���

	SetMapChipData(pLoad);

	delete[] pLoad;
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

// �}�b�v�`�b�v�z����擾
int* CMapchip::GetMapChipData()
{
	return m_MapChipData;
}

// �}�b�v�`�b�v�̗񐔂��擾
int CMapchip::GetMapchipNumX()
{
	return m_nChipNumX;
}

// �}�b�v�`�b�v�̍s�����擾
int CMapchip::GetMapchipNumY()
{
	return m_nChipNumY;
}

//****************************************************
// ����		�F �w�肳�ꂽ���W�ɂ���`�b�v�ԍ����擾
// ����		�F �C�ӂ̍��W, �}�b�v�`�b�v�̗v�f��(��)��Ԃ��|�C���^, �}�b�v�`�b�v�̗v�f��(�c)��Ԃ��|�C���^
// �߂�l	�F �������Ɏw�肳�ꂽ�ӏ��̃}�b�v�`�b�v�̔ԍ�
//****************************************************
int CMapchip::GetMapchipNo(D3DXVECTOR2 Pos, int* retIdxNumX, int* retIdxNumY)
{
	int cx = (int)(Pos.x / m_vChipSize.x);
	int cy = (int)(Pos.y / m_vChipSize.y);

	return m_MapChipData[cx + (cy * m_nChipNumX)];
}

// ��]�t���O�̎擾
//bool CMapchip::GetRotationFlag()
//{
//	return m_bRotFlag;
//}







void CreateMapchipTextureAndBuffer(int MapchipPattarn)
{
	// �e�N�X�`������
	CreateTexture(g_TextureName[MapchipPattarn], &g_Texture);

	// ���_�o�b�t�@����
	CreateVertexBuffer(&g_VertexBuffer);

}

void ReleaseMapchipTextureAndBuffer()
{
	ReleaseTexture(&g_Texture, &g_VertexBuffer);
}

void PresetDrawMapchip()
{
	PresetDraw2D(&g_VertexBuffer);
}