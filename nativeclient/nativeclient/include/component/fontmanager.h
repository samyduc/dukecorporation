#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include <glm/glm.hpp>

#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>

#if defined(WINDOWS_TARGET)
//#include <Windows.h>
//#include <gl\GL.h>
#include <GL\glew.h>
#endif

#if defined(EMSCRIPTEN_TARGET)
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#endif

#include <vector>
#include <map>

namespace Natorium
{

static natU32 s_FontManager = Hash::Compute("FontManager");


class Font
{
public:
		struct char_info_t
		{
			int x;
			int y;
			int width;
			int height;
			int left;
			int top;
			int advance;
			int row;
 
			glm::vec2 uv[4];
			glm::vec3 v[4];
			uint8_t* bitmap;
		};
 
		struct font_info_t
		{
			int max_height;
			std::vector<Font::char_info_t> ch;
		};

		font_info_t	m_info;
		GLuint		m_texture;
};

class FontManager : public Component
{
public:
					FontManager();
	virtual			~FontManager();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_FontManager; }

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);

	void			Load(const natChar* _path, natU32 _fontSize);

	Font*			Get(const natChar* _path, natU32 _fontSize);
	Font*			Get(natU32 _id);

	natU32			Compute(const natChar* _path, natU32 _fontSize) const;

private:
	Font*			Load(const natU8* _buffer, size_t _size, natU32 _fontSize);
	natU32			next_p2( int a );
	void			fill_texture_data(size_t ch, Font::font_info_t* font, natU32 texture_width, natU8* texture_data);

private:
	typedef std::map<natU32, Font*> fonts_t;
	fonts_t			m_fonts;
	FT_Library		m_ft_library;

	const natU32	m_number_of_chars;
	const natU32	m_texture_max_width;

};

inline natU32 FontManager::next_p2( int a )
{
	int rval=1;
	while(rval<a) rval<<=1;
	return rval;
}


}