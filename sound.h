//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 稲垣佑二郎, 杉本幸宏
//
//=============================================================================
#pragma once

#include <windows.h>
#include "xaudio2.h"	// サウンド処理で必要

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
enum 
{
	// BGM
	SOUND_LABEL_BGM_title_01,			// タイトルBGM_その１
	SOUND_LABEL_BGM_game_01,			// ゲームBGM_その１
	SOUND_LABEL_BGM_result_CLEAR,		// リザルトBGM_ゲームクリア
	SOUND_LABEL_BGM_result_FAILED,		// リザルトBGM_ゲームオーバー

	// SE
	SOUND_LABEL_SE_game_enemykill,		// エネミーkill時のSE
	SOUND_LABEL_SE_game_floatforce,		// 浮力加速時のSE
	SOUND_LABEL_SE_game_gravitychange,	// 重力変更時のSE
	SOUND_LABEL_SE_scenemove,			// シーン遷移時のSE

	SOUND_LABEL_MAX,
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
bool InitSound(HWND hWnd);
void UninitSound(void);
void PlaySound(int label);
void StopSound(int label);
void StopSound(void);

