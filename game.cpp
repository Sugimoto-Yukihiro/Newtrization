//=============================================================================
//
// �Q�[����ʏ��� [game.cpp]
// Author : ���{�K�G
//
//=============================================================================
#include "main.h"
#include "renderer.h"	// �����_�����O����
#include "game.h"

#include "bg.h"			// �w�i
//#include "bullet.h"	// �o���b�g
#include "camera.h"		// �J��������
#include "collision.h"	// �Փ˔���
#include "enemy.h"		// �G�l�~�[
#include "fade.h"		// �t�F�[�h
#include "input.h"		// �L�[�E�Q�[���p�b�h���͏���
//#include "particle.h"	// �p�[�e�B�N��

//#include "score.h"	// �X�R�A
#include "sound.h"		// �T�E���h

#include "debugproc.h"	// �f�o�b�O�\��

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NEXT_MODE		MODE_RESULT		// ���̃��[�h

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************



//=============================================================================
// ����������
//=============================================================================
void CModeGame::Init()
{
	//------------------- �����o�ϐ��̏�����
	m_vScrollPos = ZERO_VECTOR2;			// �X�N���[�����W�̏�����
	m_GravityDirection = GRAVITY_DEFAULT;	// �d�͕����̏�����
	m_bIsTouchGrvityChange = false;			// "false"�i�G���W���ɐG��Ă��Ȃ��j�ŏ�����
#ifdef _DEBUG
	// �|�[�Y�t���O�̏�����
	m_bPauseFlag = false;	// "false"�i�{�[�Y�����j�ŏ�����
#endif // _DEBUG

	//------------------- �ȍ~�A�Q�[�����[�h�N���X���̃C���X�^���X�̏�����
	// �w�i�̏�����
	InitBg();

	// �v���C���[�̏�����
	CreatePlayerTexture();	// �e�N�X�`���E���_�o�b�t�@����
//	for(int i =0; i < PLAYER_MAX; i++)
	{
		m_Player.Init();	// �������������s
	}

	// �}�b�v�`�b�v�̏�����
	CreateMapchipTexture(MAPCHIP_STAGE_Sample);	// �e�N�X�`���E���_�o�b�t�@����
	m_Mapchip.Init(MAPCHIP_TEXTURE_DIVIDE_X, MAPCHIP_TEXTURE_DIVIDE_Y);		// �������������s

	// �G�l�~�[�̏�����
	InitEnemy();

	// �e�̏�����
//	InitBullet();

	// �X�R�A�̏�����
//	InitScore();

	// �p�[�e�B�N���̏�����
//	InitParticle();

	// �I�u�W�F�N�g�̔z�u & �}�b�v�`�b�v�̃Z�b�g
	PutAllObject(GAME_MAP_DATA_1);
//	PutAllObject(GAME_MAP_DATA_1, MAPCHIP_TEXTURE_DIVIDE_X, MAPCHIP_TEXTURE_DIVIDE_Y);

	// �v���C���[�̈ʒu�����܂�������A�X�N���[�����W���Z�b�g
	{
		D3DXVECTOR2 pos;	// �ꎞ�I�ȕϐ�
		pos.x = m_Player.GetPosition().x - SCROLL_SET_X;	// �X�N���[�����W<x>�ɒl����
		pos.x = (pos.x < 0.0f) ? 0.0f : pos.x;	// �X�N���[�����W<x>�����Ȃ�u0�v�Ƀ��Z�b�g�A���̐��Ȃ炻�̂܂�
		pos.x = (pos.x + SCREEN_WIDTH > m_Mapchip.GetStageSize().x) ? m_Mapchip.GetStageSize().x - SCREEN_WIDTH : pos.x;	// ��ʉE��̓_�����[���h�̒[�ɗ�����"STAGE_W"�̒l�Ƀ��Z�b�g

		pos.y = m_Player.GetPosition().y - SCROLL_SET_Y;	// �X�N���[�����W<y>�ɒl����
		pos.y = (pos.y < 0.0f) ? 0.0f : pos.y;	// �X�N���[�����W<y>���Ȃ�u0�v�Ƀ��Z�b�g�A���̐��Ȃ炻�̂܂�
		pos.y = (pos.y + SCREEN_HEIGHT > m_Mapchip.GetStageSize().y) ? m_Mapchip.GetStageSize().y - SCREEN_HEIGHT : pos.y;	// ��ʉE��̓_�����[���h�̒[�ɗ�����"STAGE_H"�̒l�Ƀ��Z�b�g

		// ���W���Z�b�g
		m_vScrollPos = pos;
	}

	// BGM�Đ�
//	PlaySound(SOUND_LABEL_BGM_sample001);

	// 2D�̒��_�o�b�t�@����
//	CreateVertexBuffer();

}



//=============================================================================
// �I������
//=============================================================================
void CModeGame::Uninit(void)
{
	// ���_�o�b�t�@���
//	ReleaseVertexBuffer();

	// �p�[�e�B�N���̏I������
//	UninitParticle();

	// �X�R�A�̏I������
//	UninitScore();

	// �e�̏I������
//	UninitBullet();

	// �}�b�v�`�b�v�̏I������
	ReleaseMapchipTexture();	// �e�N�X�`�����

	// �G�l�~�[�̏I������
	UninitEnemy();

	// �v���C���[�̏I������
	ReleasePlayerTexture();	// �e�N�X�`�����
//	for (int i = 0; i < PLAYER_MAX; i++)
//	{
//		(m_Player + i)->Uninit();
//	}

	// �w�i�̏I������
	UninitBg();

}



//=============================================================================
// �X�V����
//=============================================================================
void CModeGame::Update(void)
{
#ifdef _DEBUG
	// �|�[�Y�L�[�������ꂽ��t���O�𑀍삷��
	if( KEY_PAUSE ) m_bPauseFlag = (m_bPauseFlag) ? false : true;
								//  m_bPauseFlag�́H  "true"�Ȃ�"false" ��  :  "false"�Ȃ�"true" ��  �Z�b�g����
	// �|�[�Y�t���O��true�Ȃ珈�����s��Ȃ��B
	if (m_bPauseFlag) return;

	// ���X�^�[�g�̃L�[�������ꂽ�Ƃ�
	if (KEY_RESTART_GAMEMODE)
	{
		CModeGame::Uninit();	// �Q�[�����[�h�̉��
		CModeGame::Init();		// �Q�[�����[�h�̏�����
	}

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

	// �d�͕����̕ύX
	if (KEY_CHANGE_GRAVITY)
	{
		m_GravityDirection = (m_GravityDirection + 1) % GRAVITY_DIRECTION_MAX;
		ChangeGravityDirection(m_GravityDirection);
	}

#endif // _DEBUG


	// �}�b�v�`�b�v�̍X�V����
	m_Mapchip.Update();

	// �v���C���[�̍X�V����
//	for (int i = 0; i < PLAYER_MAX; i++)
	{
		m_Player.Update();	// �v���C���[�̍X�V�������s
	}

	// �G�l�~�[�̍X�V����
	UpdateEnemy();

	// �e�̍X�V����
//	UpdateBullet();

	// �p�[�e�B�N���̍X�V����
//	UpdateParticle();

	// �����蔻�菈��
	CollisionCheck();

	// �X�R�A�̍X�V����
//	UpdateScore();

	// �w�i�̍X�V����
	UpdateBg();

}

//=============================================================================
// �`�揈��
//=============================================================================
void CModeGame::Draw()
{
	// �`��O�̏����������s
	PresetDraw2D();

	// �w�i�̕`�揈��
	DrawBg();

	// �}�b�v�`�b�v�̕`��
	m_Mapchip.Draw();

	// �G�l�~�[�̕`�揈��
//	DrawEnemy();

	// �v���C���[�̕`�揈��
//	for (int i = 0; i < PLAYER_MAX; i++)
	{
		m_Player.Draw();	// �v���C���[�`��
	}

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
void CModeGame::CollisionCheck()
{
	// �v���C���[�ƃ}�b�v�`�b�v�̓����蔻��
	{
		// �v���C���[���W�̃}�b�v�`�b�v���擾���āA���̒l�ɂ���ď�����ς���
		switch ( m_Mapchip.GetMapchipNo(m_Player.GetPosition()) )	// �v���C���[���W�̃}�b�v�`�b�v���擾
		{
			// �d�͕ύX�G���W���ɐG�ꂽ�Ƃ�
		case 10: case 12:
			// �d�͕����̕ύX
			if (!m_bIsTouchGrvityChange)	// ���߂ďd�͑��u�ɐG�ꂽ���̈�񂾂��s��
			{
				m_GravityDirection = (m_GravityDirection + 1) % GRAVITY_DIRECTION_MAX;	// �d�͂̕�����ύX
				ChangeGravityDirection(m_GravityDirection);	// �d�͕����Z�b�g

				m_bIsTouchGrvityChange = true;	// �d�͑��u�ɐG��Ă��܂���
			}
			break;

			// �S�[���ɒ������Ƃ�
		case 11:
			SetFade(FADE_OUT, NEXT_MODE);		// �t�F�[�h���Ď��̃��[�h�i���U���g��ʁj��
			break;

		default:
			// �d�͑��u�ɐG��Ă��܂���
			m_bIsTouchGrvityChange = false;		// �t���O��"false"�ɃZ�b�g
			break;
		}

	}

}

//****************************************************
// ����		�F �}�b�v�`�b�v�Ƃ̓����蔻����Ƃ�A���W�̒������s��
// ����		�F �}�b�v�`�b�v���, ���݂̍��W, �ړ��O�̍��W, ���W�������s�����ǂ����̃t���O(X��), ���W�������s�����ǂ����̃t���O(Y��)
// �߂�l	�F �y������z���������`�b�v�̔ԍ��@�@�y�O��z�u-1�v
//****************************************************
int HitCheckMapchip(CMapchip Mapchip, D3DXVECTOR2* CurrentPos, D3DXVECTOR2 OldPos, bool FlagX, bool FlagY)
{
	int nCurX, nCurY, nCurNo;
	int nOldX, nOldY, nOldNo;

	// ���݂̍��W�̃`�b�v�ԍ��ƁA�}�b�v�`�b�v���W�n�ł̈ʒu�����߂�
	nCurNo = Mapchip.GetMapchipNo(*CurrentPos, &nCurX, &nCurY);	// �ړ���̏��
	nOldNo = Mapchip.GetMapchipNo(OldPos, &nOldX, &nOldY);		// �ړ��O�̏��

	// �`�b�v�Ɠ������Ă��邩����
	// �ړ���̍��W�ɂ���}�b�v�`�b�v�ԍ����A�����蔻�葮���������Ă����� �� �������Ă���
	if (MAPCHIP_HIT_min <= nCurNo && nCurNo <= MAPCHIP_HIT_MAX)	// �ړ���̍��W�ɂ���}�b�v�`�b�v�ԍ����A�uMAPCHIP_HIT_min�v�ƁuMAPCHIP_HIT_MAX�v�̊Ԃ̂Ƃ�
	{	// �}�b�v�`�b�v�Ɠ������Ă��鎞�̏���
		//========= 1.���W�𒲐�
	//	if(Flag)	// ���W�������s���t���O�������Ă�����A���W�������s��
		{
			// x��
			if ( (nCurX - nOldX) != 0 && FlagX)	// �����Ȃ��Ƃ��͒�������K�v���Ȃ�
			{
				// �܂��́A�`�b�v �� �ړ��O���W(�v���C���[) �̈ʒu�֌W�𒲂ׂ�
				int isLeft = (nOldX < nCurX);	// �ړ��O���W�������ɂ���Ƃ��́u1�v�ɂȂ�
	
				if (isLeft)
				{	// �ړ��O���W�������̎�
				//	CurrentPos->x = (Mapchip.GetMapchipSize().x * nCurX) - HalfObjectSize.x;
					CurrentPos->x = (Mapchip.GetMapchipSize().x * nCurX);			// ���W�����i�����o�������j

					/* ��̖��߂������ƁA�����[�v���ɁAisLeft=0����ƂȂ�A����ʂ����Ⴄ */
					CurrentPos->x -= 0.5f;		// ������΍�́A��肽���Ȃ����ǉ��}���u
				}
				else
				{
				//	CurrentPos->x = (Mapchip.GetMapchipSize().x * (nCurX + 1)) + HalfObjectSize.x;
					CurrentPos->x = (Mapchip.GetMapchipSize().x * (nCurX + 1) );	// ���W�����i�����o�������j
				}
			}

			// y��
			if ( (nCurY - nOldY) != 0 && FlagY)	// �����Ȃ��Ƃ��͒�������K�v���Ȃ�
			{
				// �܂��́A�`�b�v �� �ړ��O���W(�v���C���[) �̈ʒu�֌W�𒲂ׂ�
				int isTop = (nOldY < nCurY);	// �ړ��O���W���㑤�ɂ���Ƃ��́u1�v�ɂȂ�

				if (isTop)
				{	// �ړ��O���W�������̎�
				//	CurrentPos->y = (Mapchip.GetMapchipSize().y * nCurY) - HalfObjectSize.y;
					CurrentPos->y = (Mapchip.GetMapchipSize().y * nCurY);		// ���W�����i�����o�������j

					/* ��̖��߂������ƁA�����[�v���ɁAisTop =0 ����ƂȂ�A����ʂ����Ⴄ */
					CurrentPos->y -= 0.5f;		// ������΍�́A��肽���Ȃ����ǉ��}���u
				}
				else
				{
				//	CurrentPos->y = (Mapchip.GetMapchipSize().y * (nCurY + 1)) + HalfObjectSize.y;
					CurrentPos->y = (Mapchip.GetMapchipSize().y * (nCurY + 1));	// ���W�����i�����o�������j
				}
			}
		}

		//========= 2.���������`�b�v�̔ԍ���Ԃ�
		return nCurNo;
	}

	// �������Ă��Ȃ����@�� �u-1�v��Ԃ�
	return (-1);
}



//=============================================================================
// �I�u�W�F�N�g�̔z�u����
//=============================================================================
/*******************************************************************************
�֐���	:	int PutAllObject(const char* pCsvStr)
����		:	�}�b�v�z��̐擪�A�h���X
�߂�l	:	������1		���s��0
����		:	�S�ẴI�u�W�F�N�g�̃Z�b�g
			�y���Ӂz���̊֐����Ăяo���O�ɁA�S�ẴI�u�W�F�N�g�̏������������s�����ƁI
*******************************************************************************/
int CModeGame::PutAllObject(const char* pCsvMapFile)
{
	// ���̊֐����Ŏg�p����ϐ��̐錾
	char* pLoadedMapData = NULL;	// �}�b�v����Csv�t�@�C���̓ǂݍ��ݐ�
	char* p = NULL;					// strtok_s�p�̃|�C���^
	char* pToken = NULL;			// strtok_s�Œ��o�����g�[�N���������|�C���^
	int nTokenCnt = 0;				// �i�[�����g�[�N���̐����J�E���g����ϐ��i�� �}�b�v�`�b�v�z��̗v�f���j

	// Csv�t�@�C���́A�R�����g�������폜������Ԃ̂��̂�ǂݍ��݁i�J���}�ŋ�؂�ꂽ���l�f�[�^�𒊏o�j
	if ( LoadCsvFile(pCsvMapFile, pLoadedMapData, 8, ",") < 0)	// �������Ԃ��ꂽ��A�ǂݍ��ݎ��s
	{	// csv�t�@�C���̃��[�h���s���i�G���[�`�F�b�N�j
		return 0;	// ���s��Ԃ�
	}

	// �}�b�v�`�b�v�f�[�^���Z�b�g
	{
		m_Mapchip.SetMapChipData(pLoadedMapData);
	}

	// �S�ẴI�u�W�F�N�g���Z�b�g
	{
		pToken = strtok_s(pLoadedMapData, ",", &p);			// �J���}�ɋ��܂ꂽ������𒊏o
		do
		{
			// �I�u�W�F�N�g�̐ݒu�L�������������Ƃ��̏���
			if (strrchr(pToken, PLAYER_SYMBOL) != NULL)		// �v���C���[�̐ݒu�L�������݂��邩���ׂ�
			{
				// �v���C���[��ݒu
				m_Player.SetPlayer( m_Mapchip.GetMapchipPosition(nTokenCnt) );	// 'P'�̑��݂���`�b�v�̒��S�Ƀv���C���[���Z�b�g
			}
			else if (strrchr(pToken, ENEMY_SYMBOL) != NULL)	// �G�l�~�[�̐ݒu�L�������݂��邩���ׂ�
			{
				// �G�l�~�[��ݒu

			}
			else {	// �����Ȃ���

			}

			// �g�[�N�����i���݂̃}�b�v�`�b�v�z��̗v�f���j�̃J�E���g
			nTokenCnt++;

			// ���̕�����̃u���b�N���i�[
			pToken = strtok_s(NULL, ",", &p);
		} while (pToken != NULL);	// ������Ȃ��Ȃ�܂ŌJ��Ԃ�
	}

	return 1;	// ������Ԃ�
}

// �S�ẴI�u�W�F�N�g�̃Z�b�g
//void CModeGame::PutAllObject(char* MapDataFile, int chipTexDivX, int chipTexDivY)
//{
//	char* pLoad = NULL;	// �ǂݍ��ݐ�
//	// Csv�t�@�C���́A�R�����g�������폜������Ԃ̂��̂�ǂݍ��݁i�J���}�ŋ�؂�ꂽ���l�f�[�^�𒊏o�j
//	LoadCsvFile(MapDataFile, pLoad, 8, ",");	// csv�t�@�C���̃��[�h
//	m_Mapchip.SetMapChipData(pLoad);			// �}�b�v�`�b�v�f�[�^���Z�b�g
//
//	// �v���C���[��G�l�~�[�����z�u
//	PutPlayer(pLoad);	// �v���C���[��z�u
////	PutEnemy(pLoad);	// �G�l�~�[��z�u
//
//}

// csv�̃}�b�v�f�[�^����A�v���C���[��z�u����
//void CModeGame::PutPlayer(const char* csvMapData, char Symbol)
//{
//	int X, Y;	// �}�b�v�`�b�v���W�n�ł�,�@�v���C���[�̈ʒu
//	const char* SymbolPlace = NULL;
//	SymbolPlace = strrchr(csvMapData, Symbol);	// �v���C���[�̃V���{�������邩����
//}



//=============================================================================
// �Q�b�^�[�֐�
//=============================================================================
// �X�N���[�����W�̃Z�b�g
D3DXVECTOR2 CModeGame::GetScrollPosition()
{
	return m_vScrollPos;
}

// �}�b�v�`�b�v�ւ̃A�N�Z�X
CMapchip* CModeGame::GetMapchip()
{
	return &m_Mapchip;	// �}�b�v�`�b�v�̏���Ԃ�
}

// �}�b�v�`�b�v�ւ̃A�N�Z�X
CPlayer* CModeGame::GetPlayer()
{
	return &m_Player;	// �v���C���[�̏���Ԃ�
}

// �d�͕����̎擾
int CModeGame::GetGravityDirection()
{
	return m_GravityDirection;	// �Q�[���S�̂̏d�͕����̏���Ԃ�
}

//=============================================================================
// �Z�b�^�[�֐�
//=============================================================================
// �X�N���[�����W�̎擾
void CModeGame::SetScrollPosition(D3DXVECTOR2 Pos)
{
	m_vScrollPos = Pos;
}

// �Q�[���S�̂̏d�͂̕������Z�b�g
void CModeGame::ChangeGravityDirection(int Direction)
{
	/* �d�͏����N���X���p�����Ă���S�ẴI�u�W�F�N�g�́A�d�͕����̌�����ύX */
	// �v���C���[
//	for (int i = 0; i < PLAYER_MAX; i++)	// ��������Ƃ� �� ����for���̃R�����g���O���� m_Player[i]�ɕς���
	{
		//if (!m_Player.GetUseFlag()) return;			// �v���C���[�����g�p�Ȃ�s��Ȃ�
		m_Player.SetGravityObjectDirection(Direction);	// �v���C���[�̏d�͕������Z�b�g
		m_Player.SetSize(D3DXVECTOR2(m_Player.GetSize().y, m_Player.GetSize().x));	// �T�C�Y�l�����ւ�
	}
	
	// �ς���������ɂ���ď����ς���
	if (m_GravityDirection == GRAVITY_LEFT)			// �������֕ς�������̏���
	{
		m_Player.SetTexRotation(D3DXToRadian(0));	// ��]�l���������񃊃Z�b�g
		m_Player.SetTexRotation(D3DXToRadian(90));	// �v���C���[�e�N�X�`����90����]
	//	m_Player.SetSize(D3DXVECTOR2(m_Player->GetSize().y, m_Player->GetSize().x));	// �T�C�Y������ւ�
	}
	else if (m_GravityDirection == GRAVITY_DEFAULT)	// �f�t�H���g�֕ς�������̏���
	{
		m_Player.SetTexRotation(D3DXToRadian(0));	// ��]�l�����Z�b�g
	}



}
