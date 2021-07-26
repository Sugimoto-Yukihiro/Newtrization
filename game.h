//=============================================================================
//
// �Q�[����ʏ��� [game.h]
// Author : ���{�K�G
//
//=============================================================================
#pragma once

#include "player.h"		// �v���C���[
#include "mapchip.h"	// �}�b�v�`�b�v

// �Q�[����ʏ����̊Ǘ����@�̑I��
//#define GAMEMODE_STRUCT
#define GAMEMODE_CLASS

// �N���X�Ǘ�
#ifdef GAMEMODE_CLASS

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

	//------------------- �Q�b�^�[�֐�
	D3DXVECTOR2 GetScrollPosition();
	CMapchip* GetMapchip();			// �}�b�v�`�b�v�̃C���X�^���X�ւ̃A�N�Z�X
	int GetGravityDirection();		// �d�͂̕������擾

	//------------------- �Z�b�^�[�֐�
	void SetScrollPosition(D3DXVECTOR2 Pos);	// �X�N���[�����W�̃Z�b�g
	void SetGravityDirection(int Direction);	// �Q�[���S�̂̏d�͂̕������Z�b�g

private:
	//------------------- �e�C���X�^���X
	CPlayer m_Player[PLAYER_MAX];		// �v���C���[�̃C���X�^���X
	CMapchip m_Mapchip;					// �}�b�v�`�b�v�̃T���v��

	//------------------- �����o�ϐ�
	D3DXVECTOR2 m_vScrollPos;			// �X�N���[�����W
	int m_GravityDirection;				// �d�͂̕���
	bool m_bIsTouchGrvityChange;		// �d�͕ύX�G���W���ɐG��Ă��邩�ǂ���


#ifdef _DEBUG
	bool	m_bPauseFlag;				// �|�[�YON/OFF
#endif // _DEBUG
};

#endif // GAMEMODE_CLASS

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//int HitCheckMapchip(CMapchip Mapchip, D3DXVECTOR2* CurrentPos, D3DXVECTOR2 OldPos, D3DXVECTOR2 HalfObjectSize);
int HitCheckMapchip(CMapchip Mapchip, D3DXVECTOR2* CurrentPos, D3DXVECTOR2 OldPos, bool Flag = true);




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
