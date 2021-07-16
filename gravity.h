#pragma once

#include "main.h"

enum DIRECTION
{
	GLAVITY_DEFAULT, 
	GLAVITY_LEFT
};


// クラス定義
class CGravity
{
public:
	void Init();
	void Update(DIRECTION Direction);
//	void Uninit();

private:
	D3DXVECTOR2 m_Position;
	float m_GravityWait;
	int m_nFlameCount;

};




// cpp内
void CGravity::Update(DIRECTION Direction)
{
	if (Direction == GLAVITY_DEFAULT)
	{
		// 重力でプレイヤーを下に動かす処理
		m_Position.y += m_GravityWait * m_nFlameCount;
	}
	else if (Direction == GLAVITY_LEFT)
	{
		// 重力でプレイヤーを左に動かす処理
		m_Position.x -= m_GravityWait * m_nFlameCount;
	}
}