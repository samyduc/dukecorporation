#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"
#include "component/shape.h"

#include <glm/glm.hpp>

#include <string>

namespace Natorium
{

extern natU32 s_Shape;

class Font;

class TextShape : public Shape
{
public:
					TextShape();
	virtual			~TextShape() {}

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt) {}
	virtual void	OnDeInit() {}

	static natU32	GetType() { return s_Shape; }

	void			Clone(Entity* _entity) const;

	size_t			GetVertexNumber() { return m_vertexNumber; }
	natF32*			GetVertex(size_t &_size);

	glm::vec2		GetSize() const { return m_size; }
	glm::vec4		GetColor() const { return m_color; }

	void			GetOffset(size_t& _vertexNumber, size_t& _color, size_t& _uv);

	void			SetVertex(natF32* _buffer, size_t &_size);
	void			SetSize(glm::vec2& _size);
	void			SetColor(glm::vec4& _color);
	void			SetAlpha(natF32 _alpha);

	natBool			IsAndRemoveDirty() {natBool ret = m_isDirty; m_isDirty = false; return ret; };

	void			SetText(std::wstring& _text, Font* _font);

public:
	std::wstring	m_text;
	Font*			m_font;
	glm::vec4		m_color;

private:
	natBool			m_isDirty;
	size_t			m_length;
	natF32*			m_vertex;
	size_t			m_vertexNumber;
	size_t			m_colorOffset;
	size_t			m_uvOffset;
	glm::vec2		m_size;

};




}