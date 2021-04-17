#include "MagicCrate.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>    

MagicCrate::MagicCrate(const BackBuffer* backBuffer)
{
	m_pSprite = new Sprite("data/BonusCrateImg.bmp", "data/BonusCrateMask.bmp");
	m_pSprite->setBackBuffer(backBuffer);
	m_eSpeedState = SPEED_STOP;
	m_fTimer = 0;


	// Animation frame crop rectangle
	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = 128;
	r.bottom = 128;

	m_pExplosionSprite = new AnimatedSprite("data/explosion.bmp", "data/explosionmask.bmp", r, 15);
	m_pExplosionSprite->setBackBuffer(backBuffer);
	m_bExplosion = false;
	m_iExplosionFrame = 0;
}

MagicCrate::~MagicCrate()
{
	delete m_pSprite;
	delete m_pExplosionSprite;
}

void MagicCrate::Update(float dt)
{
	m_pSprite->update(dt);
	m_fTimer += dt;

}

void MagicCrate::Draw()
{
	if (!m_bExplosion)
		m_pSprite->draw();
	else
		m_pExplosionSprite->draw();
}

void MagicCrate::Move() {


	//this->m_pSprite->mPosition.x += this->add;
	this->m_pSprite->mPosition.y += this->add_s;

	if (this->m_pSprite->mPosition.x - m_pSprite->width() / 2 <= 0 || this->m_pSprite->mPosition.x + m_pSprite->width() / 2 >= 750) {
		this->add *= -0.5;

	}
	if (this->m_pSprite->mPosition.y - m_pSprite->height() / 2 <= 0 || this->m_pSprite->mPosition.y + m_pSprite->height() / 2 >= 530) {
		this->add_s *= -0.5;
	}

}

Vec2& MagicCrate::Position()
{
	return m_pSprite->mPosition;
}

Vec2& MagicCrate::Velocity()
{
	return m_pSprite->mVelocity;
}

void MagicCrate::Explode()
{
	m_pExplosionSprite->mPosition = m_pSprite->mPosition;
	m_pExplosionSprite->SetFrame(0);
	PlaySound("data/explosion.wav", NULL, SND_FILENAME | SND_ASYNC);
	m_bExplosion = true;
}

bool MagicCrate::AdvanceExplosion()
{
	if (m_bExplosion)
	{
		m_pExplosionSprite->SetFrame(m_iExplosionFrame++);
		if (m_iExplosionFrame == m_pExplosionSprite->GetFrameCount())
		{
			m_bExplosion = false;
			m_iExplosionFrame = 0;
			m_pSprite->mVelocity = Vec2(0, 0);
			m_eSpeedState = SPEED_STOP;
			return false;
		}
	}

	return true;
}

bool MagicCrate::is_down()
{
	if (m_pSprite->mPosition.y == GetSystemMetrics(SM_CYSCREEN) / 1.44)
		return true;
	else
		return false;
}