#pragma once

#include "main.h"

enum DIRECTION
{
	GLAVITY_DEFAULT, 
	GLAVITY_LEFT
};


// �N���X��`
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




// cpp��
void CGravity::Update(DIRECTION Direction)
{
	if (Direction == GLAVITY_DEFAULT)
	{
		// �d�͂Ńv���C���[�����ɓ���������
		m_Position.y += m_GravityWait * m_nFlameCount;
	}
	else if (Direction == GLAVITY_LEFT)
	{
		// �d�͂Ńv���C���[�����ɓ���������
		m_Position.x -= m_GravityWait * m_nFlameCount;
	}
}