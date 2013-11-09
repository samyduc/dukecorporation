#include "component/material/monocolor.h"

#include "component/glrender.h"
#include "component/shape.h"

namespace Natorium
{

MonoColor::MonoColor()
	: m_color(1.f, 1.f, 1.f, 1.f)
{

}

MonoColor::~MonoColor()
{

}

static ref_t s_Position = Hash::Compute("position");

void MonoColor::OnInit()
{
	m_shaderType = s_Position;

	GLManager* glmanager = GetEntity()->GetKernel()->GetLayer(Layer::s_LayerManager)->GetRootEntity()->GetComponent<GLManager>();
	assert(glmanager);

	m_program = glmanager->GetProgram(m_shaderType);
	assert(m_program);

	Shape* shape = GetShapeFromRender();
	shape->SetColor(m_color);
}

void MonoColor::OnTick(const natU64 _dt)
{

}

void MonoColor::OnDeInit()
{

}



void MonoColor::EnableAndSetVertexAttribute(size_t _colorOffset, size_t _uvOffset) 
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(natF32)*_colorOffset));
}

void MonoColor::DisableVertexAttribute() 
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void MonoColor::BindTexture()
{
}

void MonoColor::UnBindTexture()
{
}


}