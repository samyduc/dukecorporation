
#include "component/transform.h"

#include "base/entity.h"

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Natorium
{


Transform::Transform()
	: m_scale(1.0f)
	, m_pos(0.0f)
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

glm::quat Transform::GetRot()
{
	Transform* parent = GetEntity()->GetParent()->GetComponent<Transform>();

	if(parent)
	{
		return m_rot * parent->GetRot();
	}
	else
	{
		return m_rot;
	}
}

void Transform::ComputeTransformMatrix(glm::mat4& _mat)
{
	Transform* parent = GetEntity()->GetParent()->GetComponent<Transform>();

	if(parent)
	{
		parent->ComputeTransformMatrix(_mat);
	}

	// translation
	_mat = glm::translate(_mat, m_pos);

	// rotation
	_mat *= glm::toMat4(m_rot);

	// scale ?
}

}