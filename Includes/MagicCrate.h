#pragma once

#include "Main.h"
#include "Sprite.h" 

class MagicCrate {

public:
	enum DIRECTION
	{
		DIR_FORWARD = 1,
		DIR_BACKWARD = 2,
		DIR_LEFT = 4,
		DIR_RIGHT = 8,
	};

	enum ESpeedStates
	{
		SPEED_START,
		SPEED_STOP
	};

	MagicCrate(const BackBuffer* backBuffer);
	virtual ~MagicCrate();
	void					Update(float dt);
	void					Draw();
	void					Move();
	Vec2& Position();
	Vec2& Velocity();
	void					Explode();
	bool					AdvanceExplosion();
	bool is_down();
	Sprite* m_pSprite;

private:

	ESpeedStates			m_eSpeedState;
	float					m_fTimer;

	bool					m_bExplosion;
	AnimatedSprite* m_pExplosionSprite;
	int						m_iExplosionFrame;
	float add = 0.1;
	float add_s = 0.1;

};
