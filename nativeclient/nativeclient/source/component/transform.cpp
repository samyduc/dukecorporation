
#include "component/transform.h"

#include "base/entity.h"

namespace Natorium
{


Transform::Transform()
	: m_scale(1.0f)
	, m_pos(0.0f)
	, m_rad(0.0f)
	, m_forward(0.0f)
{

}

Transform::~Transform()
{
}

void Transform::OnInit()
{

}

void Transform::OnTick(const natU64 _dt)
{
}

void Transform::OnDeInit()
{
}

glm::vec3 Transform::GetPos()
{
	Transform* parent = GetEntity()->GetParent()->GetComponent<Transform>();

	if(parent)
	{
		return m_pos + parent->GetPos();
	}
	else
	{
		return m_pos;
	}
}

glm::vec3 Transform::GetRad()
{
	Transform* parent = GetEntity()->GetParent()->GetComponent<Transform>();

	if(parent)
	{
		return m_rad + parent->GetRad();
	}
	else
	{
		return m_rad;
	}

}



}