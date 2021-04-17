
#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(const BackBuffer * pBackBuffer)
{
	m_pSprite = new Sprite("data/enemyBulletImg.bmp", "data/enemyBulletMask.bmp");
	m_pSprite->setBackBuffer(pBackBuffer);
	m_eSpeedState = SPEED_STOP;
	m_fTimer = 0;

	// Animation frame crop rectangle
	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = 128;
	r.bottom = 128;

	
}

EnemyBullet::~EnemyBullet()
{
	delete m_pSprite;
}

void EnemyBullet::Update(float dt)
{
	
	m_pSprite->update(dt);

	double v = m_pSprite->mVelocity.Magnitude();

	m_fTimer += dt;

	
}

void EnemyBullet::Draw()
{
	
	m_pSprite->draw();
	
}

Vec2& EnemyBullet::Position()
{
	return m_pSprite->mPosition;
}

Vec2& EnemyBullet::Velocity()
{
	return m_pSprite->mVelocity;
}

bool EnemyBullet::Shoot()
{
	add = 0.1;
	add_s = 0.1;
	
	this->m_pSprite->mPosition.y += this->add_s;

	if (this->m_pSprite->mPosition.x - m_pSprite->width() / 2 <= 0 || this->m_pSprite->mPosition.x + m_pSprite->width() / 2 >= 750) {
		this->add *= -0.5;

	}
	if (this->m_pSprite->mPosition.y - m_pSprite->height() / 2 <= 0 || this->m_pSprite->mPosition.y + m_pSprite->height() / 2 >= 530) {
		this->add_s *= -0.5;
	}

	if (m_pSprite->mPosition.y > 490)
	{
		this->add = 0;
		this->add_s = 0;
		m_pSprite->mVelocity.y = 0;
		return true;
	}
	return false;
}