#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include "component/material/material.h"


namespace Natorium
{

static ref_t s_MonoTexture = Hash::Compute("MonoTexture");

class MonoTexture : public Material
{
public:
					MonoTexture();
	virtual			~MonoTexture();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static ref_t	GetType() { return s_MonoTexture; }

	virtual void	Clone(Entity* _entity, ref_t _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);

	void			EnableAndSetVertexAttribute(size_t _colorOffset, size_t _uvOffset);
	void			DisableVertexAttribute();
	void			BindTexture();
	void			UnBindTexture();

	void			SetMainTexture(GLuint _texture) { m_textureRef = 0; m_texture = _texture; }

public:
	ref_t			m_textureRef;
	glm::vec4		m_color;

private:
	GLuint			m_texture;


};




}