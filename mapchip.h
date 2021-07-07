//==================================================================
//
// �}�b�v�`�b�v���� [mapchip.h]
// Auther : ���{�K�G
//
//==================================================================
#pragma once

#include "texture.h"

enum
{
	STAGE_NONE = -1,

	MAPCHIP_STAGE_Sample,
//	STAGE_Tutorial,

	MAPCHIP_MAX
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

	int LoadMapchip(char* pChipFileName);	// �}�b�v�`�b�v���̓ǂݍ���
	int ReleaseMapchip();					// �}�b�v�`�b�v���̉��
	void RotationMapChip(float Angle);		// �}�b�v�`�b�v�X�e�[�W�̉�]

	//------------------- �Z�b�^�[�֐�
//	void SetMapchipPos(D3DXVECTOR2 Pos);
//	void SetMapchipNum(int Num);
	void SetRotationFlag(bool Flag);	// ��]�t���O�̃Z�b�g

	//------------------- �Q�b�^�[�֐�
//	D3DXVECTOR2 GetMapchipPos();
	D3DXVECTOR2 GetMapSize();			// �}�b�v�S�̂̑傫�����擾
	D3DXVECTOR2 GetMapchipSize();		// �P�̃`�b�v�̑傫�����擾
	int* GetMapChipData();				// �}�b�v�`�b�v�z����擾
	int GetMapchipNumX();				// �}�b�v�`�b�v�̗񐔂��擾
	int GetMapchipNo(D3DXVECTOR2 Pos);	// �w�肳�ꂽ���W�ɂ���`�b�v�ԍ����擾
	bool GetRotationFlag();				// ��]�t���O�̎擾

private:
	//------------------- �����o�ϐ�
//	D3DXVECTOR2		m_vMChipPosition;	// ���W
	D3DXVECTOR2		m_vChipSize;		// �P�̃`�b�v�̑傫��
	int*			m_pMapChipData;		// �}�b�v�`�b�v���
	int				m_nChipNumX;		// �}�b�v�`�b�v�̗�
	int				m_nChipNumY;		// �}�b�v�`�b�v�̍s��
	int				m_nChipNo;			// �}�b�v�`�b�v�̔ԍ�
	bool			m_bRotFlag;			// �X�e�[�W�̉�]�t���O
//	bool			m_bUse;				// ���̃}�b�v�`�b�v�ϐ����g���Ă��邩

};


//*****************************************************************************
// �v���g�^�C�v��`
//*****************************************************************************
void InitMapchip();
void UninitMapchip();
void UpdateMapchip();
void DrawMapchip();