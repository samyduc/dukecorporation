#include "component/material/monotexture.h"

#include "component/glrender.h"
#include "component/shape.h"

#include <cassert>

namespace Natorium
{

MonoTexture::MonoTexture()
	: m_color(1.f, 1.f, 1.f, 1.f)
	, m_textureRef(0)
	, m_texture(0)
{

}

MonoTexture::~MonoTexture()
{

}

static ref_t s_Monotexture = Hash::Compute("monotexture");

void MonoTexture::OnInit()
{
	m_shaderType = s_Monotexture;

	GLManager* glmanager = GetEntity()->GetKernel()->GetLayer(Layer::s_LayerManager)->GetRootEntity()->GetComponent<GLManager>();
	assert(glmanager);

	m_program = glmanager->GetProgram(m_shaderType);
	assert(m_program);

	TextureManager* texturemanager = GetEntity()->GetKernel()->GetLayer(Layer::s_LayerManager)->GetRootEntity()->GetComponent<TextureManager>();
	assert(texturemanager);

	if(m_textureRef != 0)
	{
		m_texture = texturemanager->Get(m_textureRef);
	}

	Shape* shape = GetShapeFromRender();
	shape->SetColor(m_color);
}

void MonoTexture::OnTick(const natU64 _dt)
{

}

void MonoTexture::OnDeInit()
{

}



void MonoTexture::EnableAndSetVertexAttribute(size_t _colorOffset, size_t _uvOffset) 
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(natF32)*_colorOffset));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(natF32)*_uvOffset));
}

void MonoTexture::DisableVertexAttribute() 
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void MonoTexture::BindTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D , m_texture);
}

void MonoTexture::UnBindTexture()
{
	glBindTexture(GL_TEXTURE_2D , 0);
}

}