//=============================================================================
//
// �Q�[����ʏ��� [game.cpp]
// Author : ���{�K�G
//
//=============================================================================
#include "main.h"
#include "game.h"

#include "bg.h"			// �w�i
//#include "bullet.h"	// �o���b�g
#include "camera.h"		// �J��������
#include "collision.h"	// �Փ˔���
#include "enemy.h"		// �G�l�~�[
#include "fade.h"		// �t�F�[�h
#include "input.h"		// �L�[�E�Q�[���p�b�h���͏���
//#include "particle.h"	// �p�[�e�B�N��
#include "player.h"		// �v���C���[
#include "renderer.h"	// �����_�����O����
//#include "score.h"	// �X�R�A
#include "sound.h"		// �T�E���h

//#include "debugproc.h"	// �f�o�b�O�\��

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NEXT_MODE					MODE_RESULT		// ���̃��[�h
#define KEY_MODE_CHANGE				GetKeyboardTrigger(DIK_RETURN)
#define PAD_MODE_CHANGE				IsButtonTriggered(0, BUTTON_START) || IsButtonTriggered(0, BUTTON_B)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void CheckHit(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//static int	g_ViewPortType_Game = TYPE_FULL_SCREEN;

static bool	g_bPauseFlag = false;	// �|�[�YON/OFF

//=============================================================================
// ����������
//=============================================================================
HRESULT InitGame(void)
{
//	g_ViewPortType_Game = TYPE_FULL_SCREEN;

	// �w�i�̏���������
	InitBg();

	// �v���C���[�̏�����
	InitPlayer();

	// �G�l�~�[�̏�����
	InitEnemy();

	// �e�̏�����
//	InitBullet();

	// �X�R�A�̏�����
//	InitScore();

	// �p�[�e�B�N���̏�����
//	InitParticle();

	// BGM�Đ�
//	PlaySound(SOUND_LABEL_BGM_sample001);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGame(void)
{
	// �p�[�e�B�N���̏I������
//	UninitParticle();

	// �X�R�A�̏I������
//	UninitScore();

	// �e�̏I������
//	UninitBullet();

	// �G�l�~�[�̏I������
	UninitEnemy();

	// �v���C���[�̏I������
	UninitPlayer();

	// �w�i�̏I������
	UninitBg();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGame(void)
{
	//------------------- �L�[�E�Q�[���p�b�g�ł̓��͂Ŏ��̃��[�h��
	if (KEY_MODE_CHANGE)
	{// Enter��������A�X�e�[�W��؂�ւ���
		SetFade(FADE_OUT, NEXT_MODE);	// �t�F�[�h���Ď��̃��[�h��
	//	SetMode(NEXT_MODE);				// ���̃��[�h�ɃV�[���J��
	}
	// �Q�[���p�b�h�œ��͏���
	else if (PAD_MODE_CHANGE)
	{
		SetFade(FADE_OUT, NEXT_MODE);	// �t�F�[�h���Ď��̃��[�h��
	//	SetMode(NEXT_MODE);				// ���̃��[�h�ɃV�[���J��
	}

	// �|�[�Y�t���O��true�Ȃ珈�����s��Ȃ��B
	if(g_bPauseFlag == true) return;

	// �v���C���[�̍X�V����
	UpdatePlayer();

	// �G�l�~�[�̍X�V����
	UpdateEnemy();

	// �e�̍X�V����
//	UpdateBullet();

	// �p�[�e�B�N���̍X�V����
//	UpdateParticle();

	// �����蔻�菈��
	CheckHit();

	// �X�R�A�̍X�V����
//	UpdateScore();

	// �w�i�̍X�V����
	UpdateBg();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGame(void)
{
	// �w�i�̕`�揈��
	DrawBg();

	// �e�X�g�摜�\��
//	DrawPolygon();

	// �G�l�~�[�̕`�揈��
	DrawEnemy();

	// �v���C���[�̕`�揈��
	DrawPlayer();

	// �e�̕`�揈��
//	DrawBullet();

	// �p�[�e�B�N���̕`�揈��
//	DrawParticle();

	// �X�R�A�̕`�揈��
//	DrawScore();
}

//=============================================================================
// �����蔻�菈��
//=============================================================================
void CheckHit(void)
{
	//ENEMY *enemy = GetEnemy();		// �G�l�~�[�̃|�C���^�[��������
	//PLAYER *player = GetPlayer();	// �v���C���[�̃|�C���^�[��������
	//BULLET *bullet = GetBullet();	// �e�̃|�C���^�[��������

	// �G�ƃv���C���[�L����
	//for (int i = 0; i < MAX_ENEMY; i++)
	//{
	//	//�G�̗L���t���O���`�F�b�N����
	//	if (enemy[i].use == false)
	//		continue;

	//	//BC�̓����蔻��
	//	if (CollisionBC(GetPlayer()->pos, enemy[i].pos,
	//		player->rsize, enemy[i].rsize))
	//	{
	//		// �G�L�����N�^�[�͓|�����
	//		enemy[i].use = false;
	//		ReleaseShadow(enemy[i].shadowIdx);
	//	}
	//}

	// �v���C���[�̒e�ƓG
	//for (int i = 0; i < MAX_BULLET; i++)
	//{
	//	//�e�̗L���t���O���`�F�b�N����
	//	if (bullet[i].use == false)
	//		continue;

	//	// �G�Ɠ������Ă邩���ׂ�
	//	for (int j = 0; j < MAX_ENEMY; j++)
	//	{
	//		//�G�̗L���t���O���`�F�b�N����
	//		if (enemy[j].use == false)
	//			continue;

	//		//BC�̓����蔻��
	//		if (CollisionBC(bullet[i].pos, enemy[j].pos,
	//			bullet[i].fWidth, enemy[j].rsize))
	//		{
	//			// �����������疢�g�p�ɖ߂�
	//			bullet[i].use = false;
	//			ReleaseShadow(bullet[i].shadowIdx);

	//			// �G�L�����N�^�[�͓|�����
	//			enemy[j].use = false;
	//			ReleaseShadow(enemy[j].shadowIdx);

	//			// �X�R�A�𑫂�
	//			AddScore(10);
	//		}
	//	}

	//}


	// �G�l�~�[���S�����S�������ԑJ��
	//int enemy_count = 0;
	//for (int i = 0; i < MAX_ENEMY; i++)
	//{
	//	if (enemy[i].use == false) continue;
	//	enemy_count++;
	//}

	// �G�l�~�[���O�C�H
	//if (enemy_count == 0)
	//{
	//	SetFade(FADE_OUT, MODE_RESULT);
	//}

}


