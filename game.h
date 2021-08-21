//=============================================================================
//
// �Q�[����ʏ��� [game.h]
// Author : ���{�K�G
//
//=============================================================================
#pragma once

#include "player.h"			// �v���C���[
#include "mapchip.h"		// �}�b�v�`�b�v
#include "userInterface.h"	// UI
#include "sideblack.h"		// ��ʒ[����

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//------------------- �t�@�C���Ɋւ����`
#define GAME_MAP_DATA_TEST			"data/MAPCHIP/alpha_MAP.csv"	// �}�b�v���̃t�@�C����
//#define GAME_MAP_DATA_1				"data/MAPCHIP/alpha_MAP.csv"	// �}�b�v���̃t�@�C����
#define GAME_MAP_DATA_1				"data/MAPCHIP/MAP.csv"	// �}�b�v���̃t�@�C����
#define PLAYER_SYMBOL				'P'		// �v���C���[�̋L��
#define ENEMY_SYMBOL				'E'		// �G�l�~�[�̋L��

//------------------- �}�b�v�`�b�v�Ɋւ����`
#define TEXTURE_NAME_MAPCHIP		"data/TEXTURE/mapchip/Mapchip.png"
#define TEXTURE_NAME_MAPCHIP_DEBUG	"data/TEXTURE/mapchip/number.png"

/* �}�b�v�`�b�v�e�N�X�`���̕������@���@�Œ�l�Ƃ��� */
#define MAPCHIP_TEXTURE_DIVIDE_X	(5)		// �������̕�����
#define MAPCHIP_TEXTURE_DIVIDE_Y	(16)	// �c�����̕�����

#define MAPCHIP_DEBUG_TEXTURE_DIVIDE_X	(5)	// �������̕�����
#define MAPCHIP_DEBUG_TEXTURE_DIVIDE_Y	(6)	// �c�����̕�����


// �ǔ���̃}�b�v�`�b�v�ԍ�
/* "MAPCHIP_HIT_min" ~ "MAPCHIP_HIT_MAX" �̔ԍ��������蔻�葮�������}�b�v�`�b�v */
#define MAPCHIP_HIT_min				(1)		// �ǔ��葮���̃}�b�v�`�b�v�ԍ��̍ŏ��l
#define MAPCHIP_HIT_MAX				(9)		// �ǔ��葮���̃}�b�v�`�b�v�ԍ��̍ő�l

// �ł̃}�b�v�`�b�v�ԍ�
/* "MAPCHIP_POISON_min" ~ "MAPCHIP_POISON_MAX" �̔ԍ����Ŕ��葮�������}�b�v�`�b�v */
#define MAPCHIP_POISON_min			(18)	// �Ŕ��葮���̃}�b�v�`�b�v�ԍ��̍ŏ��l
#define MAPCHIP_POISON_MAX			(19)	// �Ŕ��葮���̃}�b�v�`�b�v�ԍ��̍ő�l

// �G���W���̃}�b�v�`�b�v�ԍ�
/* "MAPCHIP_CANGE_GRAVITY_min" ~ "MAPCHIP_CANGE_GRAVITY_MAX" �̔ԍ����d�͕ύX���葮�������}�b�v�`�b�v */
#define MAPCHIP_CANGE_GRAVITY_min	(10)	// �d�͕ύX���葮���̃}�b�v�`�b�v�ԍ��̍ŏ��l
#define MAPCHIP_CANGE_GRAVITY_MAX	(17)	// �d�͕ύX���葮���̃}�b�v�`�b�v�ԍ��̍ő�l
//#define CASE_CANGE_GRAVITY_NO		case 12:

// �S�[���̃}�b�v�`�b�v�ԍ�
/* "MAPCHIP_GOAL_min" ~ "MAPCHIP_GOAL_MAX" �̔ԍ����S�[�����葮�������}�b�v�`�b�v */
#define MAPCHIP_GOAL_min			(20)	// �S�[�����葮���̃}�b�v�`�b�v�ԍ��̍ŏ��l
#define MAPCHIP_GOAL_MAX			(20)	// �S�[�����葮���̃}�b�v�`�b�v�ԍ��̍ő�l
//#define CASE_GOAL_NO				case 13:

//------------------- �X�N���[�����W�Ɋւ����`
#define SCROLL_SET_X	(SCREEN_CENTER_X * 0.5f)	// �X�N���[�����W�̃Z�b�g�ʒu
#define SCROLL_SET_Y	(SCREEN_CENTER_Y)			// �X�N���[�����W�̃Z�b�g�ʒu

//------------------- �Q�[�����I�u�W�F�N�g�Ɋւ����`
#define PLAYER_MAX					(1)			// �v���C���[��Max�l��
#define PLAYER_TEXTURE_NAME			"data/TEXTURE/player/player01.png"		// �v���C���[�̃e�N�X�`���̃t�@�C����


//------------------- �V�l�}�`�b�N����
#define TEXTURE_NAME_SIDEBLACK		"data/TEXTURE/SideBlack/CinemaScope.png"	// �e�N�X�`���̃t�@�C����

//------------------- �t�@�C���[�u�[�c
#define FIREBOOTS_BULLET_TEXNAME	"data/TEXTURE/Bullet/bullet01.png"	// �t�@�C���[�u�[�c����o���o���b�g�̃e�N�X�`����
#define FIREBOOTS_BULLET_WIDTH		(50.0f)
#define FIREBOOTS_BULLET_HEIGHT		(50.0f)
#define FIREBOOTS_BULLET_SIZE		D3DXVECTOR2(FIREBOOTS_BULLET_WIDTH, FIREBOOTS_BULLET_HEIGHT)	// �e�̃T�C�Y
#define FIREBOOTS_BULLET_SPEED		(13.0f)		// �t�@�C���[�u�[�c����o���o���b�g�̑��x

//------------------- ��
#define POISON_ATTACK_VALUE			(3.0f)		// �ł̈�񂠂���̍U����
#define POISON_FLAME_WAIT			(6)			// ���t���[��������ł̍U�����s����
#define POISON_PLAYER_CHANGE_ALPHA	(0.03f)		// �ŏ�Ԏ��́A�v���C���[�̓����x��ς���l

//------------------- ���̑��Q�[�����Ŏg�p����p�����[�^
#define DEFAULT_GRAVITY_WAIT	(0.55f)		// �d�͂̒l(�f�t�H���g�̎�)
#define LEFT_GRAVITY_WAIT		(0.55f)		// �d�͂̒l(�������̎�)


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CModeGame
{
public:
//	CModeGame();
//	~CModeGame();

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

#ifdef _DEBUG
	bool GetPauseFlag() { return m_bPauseFlag; };			// �|�[�YON/OFF
	bool GetMapchipDebugFlag() { return m_bMapchipDebug; };	// �}�b�v�`�b�v�̃f�o�b�O�\��
#endif // _DEBUG


	//------------------- �Z�b�^�[�֐�
	void SetScrollPosition(D3DXVECTOR2 Pos);	// �X�N���[�����W�̃Z�b�g

private:
	//------------------- �����o�֐�(private)


	//------------------- �e�C���X�^���X
	CGameUI m_GameUI;				// �Q�[��UI
	CPlayer	m_Player;				// �v���C���[�̃C���X�^���X
	CMapchip m_Mapchip;				// �}�b�v�`�b�v
	CSideBlack m_SideBlack;			// ��ʒ[�̍���������

#ifdef _DEBUG
	CMapchip m_DebugMapchip;				// �f�o�b�O�\���p�}�b�v�`�b�v
#endif // _DEBUG


	//------------------- �����o�ϐ�
	D3DXVECTOR2 m_vScrollPos;		// �X�N���[�����W
	int m_GravityDirection;			// �d�͂̕���
	bool m_bIsTouchGrvityChange;	// �d�͕ύX�G���W���ɐG��Ă��邩�ǂ���


#ifdef _DEBUG
	bool	m_bPauseFlag;			// �|�[�YON/OFF
	bool	m_bMapchipDebug;		// �}�b�v�`�b�v�̃f�o�b�O�\��
#endif // _DEBUG
};



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
int HitCheckMapchip(CMapchip Mapchip, D3DXVECTOR2* CurrentPos, D3DXVECTOR2 OldPos, bool FlagX = true, bool FlagY = true);
