#include "component/textshape.h"

#include "base/entity.h"

#include "component/fontmanager.h"
#include "component/glrender.h"

namespace Natorium
{

TextShape::TextShape()
	: m_color(1.f, 1.f, 1.f, 1.f)
	, m_vertex(nullptr)
	, m_isDirty(true)
{

}

void TextShape::OnInit()
{
	SetText(m_text, m_font);
	SetColor(m_color);

	m_isDirty = true;
}

void TextShape::Clone(Entity* _entity) const
{
	TextShape* component = _entity->AddComponent<TextShape>();
	component->m_color = m_color;
}

void TextShape::SetText(std::wstring& _text, Font* _font)
{
	if(m_vertex)
	{
		delete m_vertex;
	}

	m_text = _text;
	m_font = _font;

	size_t text_size = m_text.size();

	size_t vertex_size = text_size * 4 * 4;
	size_t color_size = text_size * 4 * 4;
	size_t uv_size = text_size * 4 * 2;

	size_t total = vertex_size + color_size + uv_size;

	m_vertex = new natF32[total];
	memset(m_vertex, 0, total);

	natU32 advance = 0;
	natU32 i = 0;
	std::wstring::iterator c = m_text.begin();
	std::wstring::iterator const tmp_end = m_text.end();
 
	Font::char_info_t* ci;

			// Fill vertex data
			for(; c != tmp_end; ++c)
			{
				ci = &m_font->m_info.ch[*c];
 
				m_vertex[i+0] = ci->left+advance+ci->v[0].x;
				m_vertex[i+1] = ci->v[0].y + (m_font->m_info.max_height-ci->top);
				m_vertex[i+4] = ci->left+advance+ci->v[1].x;
				m_vertex[i+5] = ci->v[1].y + (m_font->m_info.max_height-ci->top);
				m_vertex[i+8] = ci->left+advance+ci->v[2].x;
				m_vertex[i+9] = ci->v[2].y + (m_font->m_info.max_height-ci->top);
				m_vertex[i+12] = ci->left+advance+ci->v[3].x;
				m_vertex[i+13] = ci->v[3].y + (m_font->m_info.max_height-ci->top);

				m_vertex[3] = 1.f;
				m_vertex[7] = 1.f;
				m_vertex[11] = 1.f;
				m_vertex[15] = 1.f;
 
				advance += ci->advance;
				i+=(4*4);
			}

			// Fill UV data
			natF32* uv = m_vertex + vertex_size + color_size;
			i = 0;
			c = m_text.begin();
			for(; c != tmp_end; ++c)
			{
				ci = &m_font->m_info.ch[*c];
 
				uv[i+0] = ci->uv[0].x;
				uv[i+1] = ci->uv[0].y;
				uv[i+2] = ci->uv[1].x;
				uv[i+3] = ci->uv[1].y;
				uv[i+4] = ci->uv[2].x;
				uv[i+5] = ci->uv[2].y;
				uv[i+6] = ci->uv[3].x;
				uv[i+7] = ci->uv[3].y;
 
				i+=(4*2);
			}

	// TODO : bad dependency to glrender here, maybe put it somewhere else
	GLRender* glrender = GetEntity()->GetComponent<GLRender>();
	assert(glrender != nullptr);
	glrender->SetTexture(m_font->m_texture);

	m_isDirty = true;
}

void TextShape::SetSize(glm::vec2& _size)
{
	// cannot change dynamically the size for the moment
	assert(false);
}

void TextShape::SetColor(glm::vec4& _color)
{
	m_color = _color;

	assert(m_vertex != nullptr);

	size_t text_size = m_text.size();

	size_t vertex_size = text_size * 4 * 4;
	size_t color_size = text_size * 4 * 4;
	
	natF32* color = m_vertex + vertex_size;

	natU32 i = 0;
	std::wstring::iterator c = m_text.begin();
	std::wstring::iterator const tmp_end = m_text.end();

	for(; c != tmp_end; ++c)
	{
		for(natU32 j = 0; j < 4*4; j=j+4)
		{
			color[i+j+0] = _color.r;
			color[i+j+1] = _color.g;
			color[i+j+2] = _color.b;
			color[i+j+3] = _color.a;
		}

		i+=(4*4);
	}

	m_isDirty = true;
}

void TextShape::SetAlpha(natF32 _alpha)
{
	// not implemented because of lazyness
	assert(false);
	/*m_vertex[19] = _alpha;
	m_vertex[23] = _alpha;
	m_vertex[27] = _alpha;
	m_vertex[21] = _alpha;*/

	m_isDirty = true;
}


natF32* TextShape::GetVertex(size_t &_size)
{
	assert(m_vertex != nullptr);
	_size = sizeof(m_vertex);
	return m_vertex;
}



}