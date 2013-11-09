#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include "component/material/material.h"


namespace Natorium
{

static ref_t s_BumpMapping = Hash::Compute("BumpMapping");

class BumpMapping : public Material
{
public:
					BumpMapping();
	virtual			~BumpMapping();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static ref_t	GetType() { return s_BumpMapping; }

	virtual void	Clone(Entity* _entity, ref_t _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);

	void			EnableAndSetVertexAttribute(size_t _colorOffset, size_t _uvOffset);
	void			DisableVertexAttribute();
	void			BindTexture();
	void			UnBindTexture();

public:


private:



};




}