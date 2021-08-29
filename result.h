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
// �g�p�e�N�X�`���̈ꗗ
//*****************************************************************************
enum
{	// �Q�[���N���A���Ɏg�p���Ă�e�N�X�`��
	GAMECLEAR_TEX_bg,		// �w�i
	GAMECLEAR_TEX_logo,		// "Result"�̃��S

	TEXTURE_MAX_CLEAR
};

enum
{	// �Q�[���I�[�o�[���Ɏg�p���Ă�e�N�X�`��
	GAMEOVER_TEX_bg,		// �w�i
	GAMEOVER_TEX_logo,		// "GAMEOVER"�̃��S

	TEXTURE_MAX_GAMEOVER
};

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define RESULT_TEXTURE_MAX		(TEXTURE_MAX_CLEAR)	// �g�p����e�N�X�`���̍ő吔

//------------------- "Result"���S
#define RESULT_LOGO_SIZE		D3DXVECTOR2(700.0f, 200.0f)			// ���S�T�C�Y
#define RESULT_LOGO_POS			D3DXVECTOR2(480.0f, 150.0f)			// ���S�ʒu
#define RESULT_LOGO_COLOR		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)	// ���S�̐F

//------------------- �X�R�A�\��
#define RESULT_TEX_NAME_SCORE	"data/TEXTURE/score/0829_Score_Number.png"	// �X�R�A�̃e�N�X�`����
#define RESULT_TEX_SIZE_SCORE	D3DXVECTOR2(80.0f, 80.0f)		// �X�R�A�̕\���T�C�Y
#define RESULT_TEX_POS_SCORE	D3DXVECTOR2(480.0f + (80.0f * 2.0f), 320.0f)		// �X�R�A�̕\���ʒu

//------------------- "GANEOVER"�\��
#define RESULT_LOGO_GAMEOVER_SIZE	D3DXVECTOR2(900.0f, 500.0f)			// ���S�T�C�Y
#define RESULT_LOGO_GAMEOVER_POS	D3DXVECTOR2(480.0f, 320.0f)			// ���S�ʒu
#define RESULT_LOGO_GAMEOVER_COLOR	D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f)	// ���S�̐F


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
	void ScoreInit() { m_Score.Init(RESULT_TEX_NAME_SCORE, RESULT_TEX_SIZE_SCORE); } ;

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
	int m_nUseTexNum;	// �g�p���Ă���e�N�X�`���̐�
	bool m_CreaFlag;	// �Q�[���N���A�̃t���O
};
