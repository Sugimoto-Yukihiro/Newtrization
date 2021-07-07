//=============================================================================
//
// �Q�[����ʏ��� [game.h]
// Author : ���{�K�G
//
//=============================================================================
#pragma once

#include "player.h"
#include "mapchip.h"

// �Q�[����ʏ����̊Ǘ����@�̑I��
//#define GAMEMODE_STRUCT
#define GAMEMODE_CLASS

// �N���X�Ǘ�
#ifdef GAMEMODE_CLASS

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CGameMode
{
public:
	//------------------- �����o�֐�
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void CollisionCheck();	// �����蔻��

	//------------------- �Q�b�^�[�֐�
	D3DXVECTOR2 GetScrollPosition();
#ifdef _DEBUG
	bool GetPauseFlag();				// �|�[�Y�t���O�̎擾
#endif // _DEBUG

	//------------------- �Z�b�^�[�֐�
	void SetScrollPosition(D3DXVECTOR2 Pos);	// �X�N���[�����W�̃Z�b�g
#ifdef _DEBUG
	void SetPauseFlag(bool Flag);		// �|�[�Y�t���O�̃Z�b�g
#endif // _DEBUG

private:
	//------------------- �e�C���X�^���X
	CPlayer m_Player[PLAYER_MAX];		// �v���C���[�̃C���X�^���X
	CMapchip m_Mapchip[MAPCHIP_MAX];	// �}�b�v�`�b�v�̃T���v��

	//------------------- �����o�ϐ�
	D3DXVECTOR2 m_vScrollPos;			// �X�N���[�����W
#ifdef _DEBUG
	bool	m_bPauseFlag;				// �|�[�YON/OFF
#endif // _DEBUG
};

#endif // GAMEMODE_CLASS


// �\���̊Ǘ�
#ifdef GAMEMODE_STRUCT

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);

void SetScrollPosition(D3DXVECTOR2 Pos);
D3DXVECTOR2* GetScrollPosition();
#endif // GAMEMODE_STRUCT
