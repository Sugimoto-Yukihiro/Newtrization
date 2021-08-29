//=============================================================================
//
// �X�R�A���� [score.h]
// Author : ���{�K�G
//
//=============================================================================
#pragma once

#include "texture.h"	// �e�N�X�`��

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	SCORE_MAX			(99999)		// �X�R�A�̍ő�l
#define	SCORE_DIGIT			(5)			// �\������ő包��
#define	DIGIT_DECIMAL		(1)			// �\�����鏬���_�ȉ��̌���

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CScore
{
public:

	//------------------- �����o�֐�
	void Init(char* pTexName, D3DXVECTOR2 TexSize);	// ������
	void Uninit();	// �I������
	void Update(int FlameCnt);	// �X�V����
	void Draw(D3DXVECTOR2 Pos);	// �`�揈��

	// �X�R�A�̉��Z
	void AddScore(int Add);

	// �X�R�A�𒼐ڑ��
	void SetScore(int Score) { m_nScore = Score; };

	// ���݂̃X�R�A���擾
	int GetScore() { return m_nScore; };

private:
	CTexture m_Texture;
	int m_nScore;	// ���݂̃X�R�A
};
