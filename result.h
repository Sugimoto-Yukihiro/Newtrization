//=============================================================================
//
// ���U���g��ʏ��� [result.h]
// Author : ���{�K�G
//
//=============================================================================
#pragma once

#include "texture.h"	// �e�N�X�`��
#include "score.h"		// �X�R�A


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_MAX_CLEAR		(4)
#define TEXTURE_MAX_GAMEOVER	(3)
#define RESULT_TEXTURE_MAX		TEXTURE_MAX_CLEAR

#define RESULT_TEX_NAME_SCORE	"data/TEXTURE/score/number.png"	// �X�R�A�̃e�N�X�`����
#define RESULT_TEX_SIZE_SCORE	D3DXVECTOR2(35.0f, 35.0f)		// �X�R�A�̕\���T�C�Y
#define RESULT_TEX_POS_SCORE	SCREEN_CENTER					// �X�R�A�̕\���ʒu

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CModeResult
{
public:
	void Init();	// ����������
	void Uninit();	// �I������
	void Update();	// �X�V����
	void Draw();	// �`�揈��

	// ���U���g�ŕ\������X�R�A�̃Z�b�g
	void SetResultScore(int Score) {m_Score.SetScore(Score); };

	// �Q�[���N���A�t���O�̃Z�b�g
	void SetCreaFlag(bool Flag) { m_CreaFlag = Flag; };

	// �Q�[���N���A���Ɏg�p����e�N�X�`���̐����E���
	void CreateTextureGameClear();
	void ReleaseTextureGameClear();

	// �Q�[���I�[�o�[���Ɏg�p����e�N�X�`���̐����E���
	void CreateTextureGameOver();
	void ReleaseTextureGameOver();

private:
	CTexture m_Texture[RESULT_TEXTURE_MAX];	// �e�N�X�`���C���X�^���X
	CScore m_Score;		// ���U���g�\������X�R�A
	bool m_CreaFlag;	// �Q�[���N���A�̃t���O
};
