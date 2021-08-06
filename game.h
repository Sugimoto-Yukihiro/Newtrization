//=============================================================================
//
// �Q�[����ʏ��� [game.h]
// Author : ���{�K�G
//
//=============================================================================
#pragma once

#include "player.h"		// �v���C���[
#include "mapchip.h"	// �}�b�v�`�b�v

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//------------------- �t�@�C���Ɋւ����`
#define GAME_MAP_DATA_1				"data/MAPCHIP/alpha_MAP.csv"	// �}�b�v���̃t�@�C����
#define PLAYER_SYMBOL				'P'		// �v���C���[�̋L��
#define ENEMY_SYMBOL				'E'		// �G�l�~�[�̋L��
/* �}�b�v�`�b�v�e�N�X�`���̕������@���@�Œ�l�Ƃ��� */
#define MAPCHIP_TEXTURE_DIVIDE_X	(4)		// �������̕�����
#define MAPCHIP_TEXTURE_DIVIDE_Y	(4)		// �c�����̕�����

//------------------- �X�N���[�����W�Ɋւ����`
#define SCROLL_SET_X	(SCREEN_CENTER_X)	// �X�N���[�����W�̃Z�b�g�ʒu
#define SCROLL_SET_Y	(SCREEN_CENTER_Y)	// �X�N���[�����W�̃Z�b�g�ʒu

//------------------- �Q�[�����I�u�W�F�N�g�Ɋւ����`
#define PLAYER_MAX		(1)			// �v���C���[��Max�l��


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CModeGame
{
public:
	//------------------- �����o�֐�
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void CollisionCheck();	// �����蔻��
	void ChangeGravityDirection(int Direction);	// �Q�[���S�̂̏d�͂̕�����ς���

	//�y���Ӂz�� ���̊֐����Ăяo���O�ɁA�S�ẴI�u�W�F�N�g�̏������������s�����ƁI
	int PutAllObject(const char* pCsvStr);	// �S�ẴI�u�W�F�N�g�̐ݒu
//	void PutAllObject(char* MapDataFile, int chipTexDivX, int chipTexDivY);	// �S�ẴI�u�W�F�N�g��z�u����i�}�b�v�`�b�v, �v���C���[, �G�l�~�[, �M�~�b�N... �ȂǂȂǁj
//	void PutPlayer(const char* csvMapData, char Symbol);	// csv�̃}�b�v�f�[�^����A�v���C���[��z�u����
//	void PutEnemy(const char* csvMapData, char Symbol);		// csv�̃}�b�v�f�[�^����A�G�l�~�[��z�u����
//	void PutGimmick(const char* csvMapData, char Symbol);	// csv�̃}�b�v�f�[�^����A�M�~�b�N��z�u����


	//------------------- �Q�b�^�[�֐�
	D3DXVECTOR2 GetScrollPosition();
	CMapchip* GetMapchip();			// �}�b�v�`�b�v�̃C���X�^���X�ւ̃A�N�Z�X
	CPlayer* GetPlayer();			// �v���C���[�̃C���X�^���X�ւ̃A�N�Z�X
	int GetGravityDirection();		// �d�͂̕������擾

	//------------------- �Z�b�^�[�֐�
	void SetScrollPosition(D3DXVECTOR2 Pos);	// �X�N���[�����W�̃Z�b�g

private:
	//------------------- �����o�֐�(private)


	//------------------- �e�C���X�^���X
	CPlayer	m_Player;				// �v���C���[�̃C���X�^���X
	CMapchip m_Mapchip;				// �}�b�v�`�b�v�̃T���v��

	//------------------- �����o�ϐ�
	D3DXVECTOR2 m_vScrollPos;		// �X�N���[�����W
	int m_GravityDirection;			// �d�͂̕���
	bool m_bIsTouchGrvityChange;	// �d�͕ύX�G���W���ɐG��Ă��邩�ǂ���


#ifdef _DEBUG
	bool	m_bPauseFlag;			// �|�[�YON/OFF
#endif // _DEBUG
};



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
int HitCheckMapchip(CMapchip Mapchip, D3DXVECTOR2* CurrentPos, D3DXVECTOR2 OldPos, bool FlagX = true, bool FlagY = true);
