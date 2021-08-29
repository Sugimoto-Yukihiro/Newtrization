//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : ���{�K�G
//
//=============================================================================

#include "main.h"
#include "renderer.h"
#include "score.h"

//=============================================================================
// ����������
//=============================================================================
void CScore::Init(char* pTexName, D3DXVECTOR2 TexSize)
{
	m_nScore = 0;	// �X�R�A�̏�����

	// �e�N�X�`���̏�����
	m_Texture.Init();
	m_Texture.SetTexSize(TexSize);			// �T�C�Y���w��
	m_Texture.SetTexDivideX(10);			// �����������w��

	m_Texture.CreateTextureInf(pTexName);	// �e�N�X�`������

}

//=============================================================================
// �I������
//=============================================================================
void CScore::Uninit()
{
	m_Texture.ReleaseTextureInf();	// �e�N�X�`�����
}

//=============================================================================
// �X�V����
//=============================================================================
void CScore::Update(int FlameCnt)
{
	if ((FlameCnt % 60) == 0)
	{	// 1�b�o�߂�����X�R�A�����Z
		AddScore(1);
	}

}

//=============================================================================
// �`�揈��
// �����F �`�悷����W�i�ŉE�j
//=============================================================================
void CScore::Draw(D3DXVECTOR2 Pos)
{
	// ���݂̃X�R�A�l���擾
	int number = m_nScore;

	// ��������������
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// (number�̒���)�\�����錅�̐���
		int x = 0;
		x = (number % 10);

		// �X�R�A�̕`��ʒu�𔽉f
		{
			D3DXVECTOR2 DrawPos;
			DrawPos.x = Pos.x - (m_Texture.GetTexSize().x * i);	// �X�R�A�̕\���ʒuX
			DrawPos.y = Pos.y;	// �X�R�A�̕\���ʒuY

			// �`��ʒu���Z�b�g
			m_Texture.SetTexPos(DrawPos);
		}

		// �e�N�X�`�����W�𔽉f
		{
			m_Texture.SetCurrentAnim(x);
		}

		// �e�N�X�`���`��
		m_Texture.DrawTexture();

		// ���̌���
		number /= 10;
	}


}

//****************************************************
// ����		�F �X�R�A�̉��Z
// ����		�F ���Z����l�i���Z���\�j
// �߂�l	�F void
//****************************************************
void CScore::AddScore(int add)
{
	m_nScore += add;

	// �ő�l�𒴂��Ă邩�`�F�b�N
	if (m_nScore > SCORE_MAX)
	{
		m_nScore = SCORE_MAX;	// �J�E���g�X�g�b�v(�\����ƁA�V�X�e�����̗����̐��l�����Z�b�g����Ă�)
	}

}
