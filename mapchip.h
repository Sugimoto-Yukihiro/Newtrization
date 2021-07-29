//==================================================================
//
// �}�b�v�`�b�v���� [mapchip.h]
// Auther : ���{�K�G
//
//==================================================================
#pragma once

#include "texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAPCHIP_STATIC				// �}�b�v�`�b�v�z���ÓI�Ǘ�
//#define MAPCHIP_DYNAMIC			// �}�b�v�`�b�v�z��𓮓I�Ǘ�

#define MAPCHIP_SIZE_DEFAULT	D3DXVECTOR2(64.0f, 64.0f)		// �}�b�v�`�b�v�̃f�t�H���g�T�C�Y

/* "MAPCHIP_HIT_min" ~ "MAPCHIP_HIT_MAX" �̔ԍ��������蔻�葮�������}�b�v�`�b�v */
#define MAPCHIP_HIT_min		(1)		// �����蔻�葮���̃}�b�v�`�b�v�ԍ��̍ŏ��l
#define MAPCHIP_HIT_MAX		(9)		// �����蔻�葮���̃}�b�v�`�b�v�ԍ��̍ő�l

#define MAPCHIP_NUM_MAX_X	(64)	// �}�b�v�`�b�v�̍ő��
#define MAPCHIP_NUM_MAX_Y	(64)	// �}�b�v�`�b�v�̍ő�s��
#define MAPCHIP_NUM_MAX		(MAPCHIP_NUM_MAX_X * MAPCHIP_NUM_MAX_Y)	// �}�b�v�`�b�v�̍ő吔�i���v�j

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
	CMapchip();		// �R���X�g���N�^
	~CMapchip();	// �f�X�g���N�^

	//------------------- �����o�֐�
//	void Init();	// ������
	void Init(char* pMapFileName = NULL);	// ������

	void Uninit();	// �I������
	void Draw();	// �`�揈��
	void Update();	// �X�V����

//	void RotationMapChip(float Angle);		// �}�b�v�`�b�v�X�e�[�W�̉�]
	void DrawChip(D3DXVECTOR2 Pos, int Num);	// 1���̃`�b�v�̕`��
	int LoadMapchipData(char* pFileName);	// �}�b�v�`�b�v���̃t�@�C���ǂݍ���

#ifdef MAPCHIP_DYNAMIC
//	int ReleaseMapchip();					// �}�b�v�`�b�v���̉��
#endif // MAPCHIP_DYNAMIC

	//------------------- �Z�b�^�[�֐�
	int SetMapChipData(const char* pCsvString);	// �}�b�v�`�b�v�z����擾

//	void SetMapchipBasePos(D3DXVECTOR2 Pos);	// �`��̊���W���Z�b�g
	void SetMapchipSize(D3DXVECTOR2 Size);		// �P�̃`�b�v�̑傫�����Z�b�g
	void SetMapchipNumX(int Num);				// �}�b�v�`�b�v�̗񐔂��Z�b�g
	void SetMapchipNumY(int Num);				// �}�b�v�`�b�v�̗񐔂��Z�b�g
	void SetMapchipNo(int No, int X, int Y);	// �w�肵���ӏ��̃}�b�v�`�b�v�ԍ���ύX����
//	void SetRotationFlag(bool Flag);			// ��]�t���O�̃Z�b�g


	//------------------- �Q�b�^�[�֐�
	int* GetMapChipData();				// �}�b�v�`�b�v�z����擾
	D3DXVECTOR2 GetStageSize();			// �}�b�v�S�̂̑傫�����擾
	D3DXVECTOR2 GetMapchipSize();		// �P�̃`�b�v�̑傫�����擾
	int GetMapchipNumX();				// �}�b�v�`�b�v�̗񐔂��擾
	int GetMapchipNumY();				// �}�b�v�`�b�v�̗񐔂��擾
	int GetMapchipNo(int nIdxNo);		// �z��̗v�f�����w�肵�āA�}�b�v�`�b�v�ԍ����擾
									//	 �� �A���Ă��鐔�l�̍ŏ��l�͂O ��
	int GetMapchipNo(D3DXVECTOR2 Pos, int* retIdxNumX = NULL, int* retIdxNumY = NULL);	// �w�肳�ꂽ���W�ɂ���`�b�v�ԍ����擾
//	bool GetRotationFlag();				// ��]�t���O�̎擾

private:
	//------------------- �����o�ϐ�
//	D3DXVECTOR2		m_vChipBasePos;		// ���ۂɕ`�悷��}�b�v�`�b�v�̊�i�X�N���[�����W�j
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
