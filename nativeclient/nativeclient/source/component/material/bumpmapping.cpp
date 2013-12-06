#include "component/material/bumpmapping.h"

#include "component/shape.h"

namespace Natorium
{

BumpMapping::BumpMapping()
{

}

BumpMapping::~BumpMapping()
{

}

static ref_t s_ShaderBumpMapping = Hash::Compute("bumpmapping");

void BumpMapping::OnInit()
{
	m_shaderType = s_ShaderBumpMapping;

	GLManager* glmanager = GetEntity()->GetKernel()->GetLayer(Layer::s_LayerManager)->GetRootEntity()->GetComponent<GLManager>();
	assert(glmanager);

	m_program = glmanager->GetProgram(m_shaderType);
	assert(m_program);

	TextureManager* texturemanager = GetEntity()->GetKernel()->GetLayer(Layer::s_LayerManager)->GetRootEntity()->GetComponent<TextureManager>();
	assert(texturemanager);

	if(m_diffuseRef != 0)
	{
		m_diffuse = texturemanager->Get(m_diffuseRef);
	}

	m_normal = texturemanager->Get(m_normalRef);

	Shape* shape = GetShapeFromRender();
	shape->SetColor(m_diffuseColor);
}

void BumpMapping::OnTick(const natU64 _dt)
{

}

void BumpMapping::OnDeInit()
{

}


void BumpMapping::EnableAndSetVertexAttribute(size_t _colorOffset, size_t _uvOffset) 
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(natF32)*_colorOffset));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(natF32)*_uvOffset));
}

void BumpMapping::DisableVertexAttribute() 
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void BumpMapping::BindTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D , m_diffuse);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D , m_normal);
}

void BumpMapping::UnBindTexture()
{
	glBindTexture(GL_TEXTURE_2D , 0);
}

}