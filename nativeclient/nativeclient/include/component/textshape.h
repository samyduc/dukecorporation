#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"
#include "component/shape.h"

#include <glm/glm.hpp>

#include <string>

namespace Natorium
{

static natU32 s_TextShape = Hash::Compute("TextShape");

class Font;

class TextShape : public Shape
{
public:
					TextShape();
	virtual			~TextShape() {}

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt) {}
	virtual void	OnDeInit();

	static natU32	GetType() { return s_TextShape; }

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);

	size_t			GetVertexNumber() { return m_vertexNumber; }
	natF32*			GetVertex(size_t &_size);
	natU16*			GetIndices(size_t &_size);

	glm::vec2		GetSize() const { return m_size; }

	void			GetOffset(size_t& _vertexNumber, size_t& _indicesNumber, size_t& _color, size_t& _uv);

	void			SetVertex(natF32* _buffer, size_t &_size);
	void			SetIndices();
	void			SetSize(glm::vec2& _size);
	void			SetColor(glm::vec4& _color);
	void			SetAlpha(natF32 _alpha);

	natBool			IsAndRemoveDirty() {natBool ret = m_isDirty; m_isDirty = false; return ret; };

	void			SetText(std::string& _text);

public:
	std::string		m_text;
	ref_t			m_fontType;

private:
	glm::vec4		m_color;
	natBool			m_isDirty;
	size_t			m_length;
	natF32*			m_vertex;
	size_t			m_vertexNumber;
	natU16*			m_indices;
	size_t			m_indicesNumber;
	size_t			m_colorOffset;
	size_t			m_uvOffset;
	glm::vec2		m_size;
	size_t			m_bufferAllocated;
	Font*			m_font;
};




}