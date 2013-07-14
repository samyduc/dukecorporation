#include "component/gameplay/lifecontroller.h"

#include "base/entity.h"
#include "base/kernel.h"

#include "component/shape.h"


namespace Natorium
{

LifeController::LifeController()
	: m_life(10)
	, m_currentLife(0)
{
}

LifeController::~LifeController()
{
}

void LifeController::OnInit()
{
	m_currentLife = m_life;
}

void LifeController::OnTick(const natU64 _dt)
{
}

void LifeController::OnDeInit()
{
}

void LifeController::TakeDamage(natS32 _damage)
{
	m_currentLife -= _damage;

	Shape* shape = GetEntity()->GetComponent<Shape>();
	glm::vec4 color = shape->GetColor();
	color.r = 1.f / (2 - natF32(m_currentLife) / natF32(m_life));
	shape->SetColor(color);
}



}