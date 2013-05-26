
#include "component/transform.h"

namespace Natorium
{


Transform::Transform()
{
}

Transform::~Transform()
{
}

void	Transform::OnInit()
{
	m_pos_x = 0.f;
	m_pos_y = 0.f;
	m_pos_z = 0.f;

	m_rad_x = 0.f;
	m_rad_y = 0.f;
	m_rad_z = 0.f;
}

void	Transform::OnTick(natU64 _dt)
{
}

void	Transform::OnDeInit()
{
}





}