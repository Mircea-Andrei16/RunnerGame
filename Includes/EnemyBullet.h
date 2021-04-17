
#ifndef _ENEMYBULLET_H_
#define _ENEMYBULLET_H_

#include "Main.h"
#include "Sprite.h"

class EnemyBullet{
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


	EnemyBullet(const BackBuffer* pBackBuffer);
	virtual ~EnemyBullet();

	
	void					Update(float dt);
	void					Draw();
	bool					Shoot();
	Vec2& Position();
	Vec2& Velocity();
	Sprite* m_pSprite;


private:

	ESpeedStates			m_eSpeedState;
	float					m_fTimer;
	float add = 0.1;
	float add_s = 0.1;

};

#endif // _EnemyBullet_H_
