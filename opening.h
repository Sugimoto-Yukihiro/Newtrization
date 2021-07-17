//=============================================================================
//
// �^�C�g����ʏ��� [opening.h]
// Author : ���Α�q
//
//=============================================================================
#pragma once

#include "texture.h"

// �I�[�v�j���O��ʏ����̊Ǘ����@�̑I��
//#define GAMEMODE_STRUCT
#define OPENINGMODE_CLASS

// �N���X�Ǘ�
#ifdef OPENINGMODE_CLASS

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CModeOpening
{
public:
	//------------------- �����o�֐�
	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	//------------------- �����o�ϐ�
	bool					m_bUse;						// true:�g���Ă���  false:���g�p
	int						m_nTexNo;					// �e�N�X�`���ԍ�
	float					m_fbeta;
	bool					m_bflag_beta;

	CTexture				m_Logo;
};
#endif // OPENINGMODE_CLASS

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void CreateOpeningTextureAndBuffer(void);
void ReleaseOpeningTextureAndBuffer(void);
void PresetDrawOpening(void);
// �\���̊Ǘ�
#ifdef OPENINGMODE_STRUCT

#endif // OPENINGMODE_STRUCT
