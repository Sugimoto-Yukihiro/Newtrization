//=============================================================================
//
// �ŏ��� [poison.h]
// Author : ���{�K�G
//
//=============================================================================
#pragma once

#include "mapchip.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPoison
{
public:
	CPoison();	// �R���X�g���N�^
	~CPoison();	// �f�X�g���N�^

	// ������
//	void Init(CMapchip* Mapchip = NULL, D3DXVECTOR2* myLegPos = NULL, float* myHP = NULL, float Attack = 0.0f);
	void Init(D3DXVECTOR2* myLegPos = NULL, float* myHP = NULL, float Attack = 0.0f, int Wait = 0);
	void Uninit();	// �I������
	void Update();	// �X�V����
//	void Draw();	// �`�揈��

	//------------------- �����o�֐�

	//------------------- �Z�b�^�[�֐�
	void SetFlameWait(int Flame) { m_nFlameWait = Flame; };	// ���t���[�������ɑ̗͂���邩�Z�b�g

	//------------------- �Q�b�^�[�֐�
	int GetFlameWait() { return m_nFlameCnt; };	// �̗͂����^�C�~���O���擾

private:
//	CMapchip*		m_pMapchipInf;	// ���g�p���Ă���}�b�v�`�b�v�̏��
	D3DXVECTOR2*	m_pLegPosition;	// �L�����N�^�̑��̍��W
	float*			m_pHitPointInf;	// �L�����N�^��HP���Ǘ����Ă��郁�����ւ̃|�C���^
	float			m_fAttack;		// �ł̍U����
	int				m_nFlameCnt;	// �o�ߎ��Ԃ̃J�E���g�i�P�ʂ̓t���[���j
	int				m_nFlameWait;	// �̗͂����^�C�~���O
};
