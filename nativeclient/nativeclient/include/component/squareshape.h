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

	void			Clone(Entity* _entity) const;

	natU32			GetVertexNumber() { return 4; }
	natF32*			GetVertex(size_t &_size);

	glm::vec2		GetSize() const { return m_size; }
	glm::vec4		GetColor() const { return m_color; }

	void			GetOffset(size_t& _vertexNumber, size_t& color, size_t& _uv);

	void			SetVertex(natF32* _buffer, size_t &_size) { (void)_buffer; (void)_size; assert(false); }
	void			SetSize(glm::vec2& _size);
	void			SetColor(glm::vec4& _color);
	void			SetAlpha(natF32 _alpha);
	void			SetTextureCoordinate(natF32 _repeat);

	natBool			IsAndRemoveDirty() {natBool ret = m_isDirty; m_isDirty = false; return ret; };

public:
	glm::vec2		m_size;
	glm::vec4		m_color;
	natF32			m_repeat;

private:
	natBool			m_isDirty;
	size_t			m_length;
	natF32			m_vertex[40];

};




}