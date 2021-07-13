//==================================================================
//
// �}�b�v�`�b�v���� [mapchip.h]
// Auther : ���{�K�G
//
//==================================================================
#pragma once

#include "texture.h"


#define MAPCHIP_STATIC		// �}�b�v�`�b�v����ÓI�Ǘ�
//#define MAPCHIP_DYNAMIC		// �}�b�v�`�b�v���𓮓I�Ǘ�

#define MAPCHIP_NUM_MAX_X	(64)
#define MAPCHIP_NUM_MAX_Y	(64)
#define MAPCHIP_NUM_MAX		(MAPCHIP_NUM_MAX_X * MAPCHIP_NUM_MAX_Y)

enum
{
	STAGE_NONE = -1,

	MAPCHIP_STAGE_Sample,
//	STAGE_Tutorial,

	MAPCHIP_PATTARN_MAX
};

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CMapchip : public CTexture
{
public:
	CMapchip();			// �R���X�g���N�^
	~CMapchip();		// �f�X�g���N�^

	//------------------- �����o�֐�
	void Init();		// ������
	void Uninit();		// �I������
	void Draw();		// �`�揈��
	void Update();		// �X�V����
//	void RotationMapChip(float Angle);		// �}�b�v�`�b�v�X�e�[�W�̉�]
	void DrawChip(D3DXVECTOR2 Pos, int Num);	// �`�b�v�̕`��

	int LoadMapchipData(char* pFileName);	// �}�b�v�`�b�v���̃t�@�C���ǂݍ���


#ifdef MAPCHIP_DYNAMIC
//	int ReleaseMapchip();					// �}�b�v�`�b�v���̉��
#endif // MAPCHIP_DYNAMIC

	//------------------- �Z�b�^�[�֐�
	int SetMapChipData(const char* pCsvString);	// �}�b�v�`�b�v�z����擾

	void SetMapchipBasePos(D3DXVECTOR2 Pos);
	void SetMapchipSize(D3DXVECTOR2 Size);	// �P�̃`�b�v�̑傫�����擾
	void SetMapchipNumX(int Num);				// �}�b�v�`�b�v�̗񐔂��擾
	void SetMapchipNumY(int Num);				// �}�b�v�`�b�v�̗񐔂��擾
//	void SetRotationFlag(bool Flag);			// ��]�t���O�̃Z�b�g


	//------------------- �Q�b�^�[�֐�
	int* GetMapChipData();				// �}�b�v�`�b�v�z����擾
	D3DXVECTOR2 GetStageSize();			// �}�b�v�S�̂̑傫�����擾

	D3DXVECTOR2 GetMapchipSize();		// �P�̃`�b�v�̑傫�����擾
	int GetMapchipNumX();				// �}�b�v�`�b�v�̗񐔂��擾
	int GetMapchipNumY();				// �}�b�v�`�b�v�̗񐔂��擾
	int GetMapchipNo(D3DXVECTOR2 Pos);	// �w�肳�ꂽ���W�ɂ���`�b�v�ԍ����擾
//	bool GetRotationFlag();				// ��]�t���O�̎擾

private:
	//------------------- �����o�ϐ�
	D3DXVECTOR2		m_vChipBasePos;		// ���ۂɕ`�悷��}�b�v�`�b�v�̊�i�X�N���[�����W�j
	D3DXVECTOR2		m_vChipSize;		// �P�̃`�b�v�̑傫��

#ifdef MAPCHIP_STATIC
	int				m_MapChipData[MAPCHIP_NUM_MAX];	// �}�b�v�`�b�v���
#endif // MAPCHIP_STATIC

#ifdef MAPCHIP_DYNAMIC
	int*			m_MapChipData;		// �}�b�v�`�b�v���
#endif // MAPCHIP_DYNAMIC

	int				m_nChipNumX;		// �}�b�v�`�b�v�̗�
	int				m_nChipNumY;		// �}�b�v�`�b�v�̍s��
//	bool			m_bRotFlag;			// �X�e�[�W�̉�]�t���O

};



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void CreateMapchipTextureAndBuffer(int MapchipPattarn);
void ReleaseMapchipTextureAndBuffer();


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
#ifdef _DEBUG
static char* pTestMapChipData = {
	"1,2,3\n2,2,2\n3,3,3\n12,22,32\n22,22,22"
};
#endif // _DEBUG
