#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"
#include "component/shape.h"

#include <glm/glm.hpp>

namespace Natorium
{

extern natU32 s_Shape;


class SquareShape : public Shape
{
public:
					SquareShape();
	virtual			~SquareShape() {}

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt) {}
	virtual void	OnDeInit() {}

	static natU32	GetType() { return s_Shape; }

	natF32*			GetVertex(size_t &_size);

	glm::vec2		GetSize() { return m_size; }

	void			SetSize(glm::vec2& _size);
	void			SetColor(glm::vec4& _color);
	void			SetAlpha(natF32 _alpha);

private:
	size_t			m_length;
	glm::vec2		m_size;
	glm::vec4		m_color;
	natF32			m_vertex[32];

};




}