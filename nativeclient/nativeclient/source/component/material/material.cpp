#include "component/material/material.h"

#include "component/shape.h"
#include "component/glrender.h"

namespace Natorium
{

Material::Material()
	: m_program(0)
	, m_shaderType()
{

}

Material::~Material()
{

}

void Material::OnInit()
{

}

void Material::OnTick(const natU64 _dt)
{

}

void Material::OnDeInit()
{

}

Shape* Material::GetShapeFromRender()
{
	Shape* ret;
	GLRender* glrender = GetEntity()->GetComponent<GLRender>();

	ret = glrender->GetShape();
	
	if(!ret)
	{
		ret = static_cast<Shape*>(GetEntity()->GetComponentByType(glrender->m_shapeType));
	}

	return ret;
}

}