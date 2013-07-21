#include "component/fontmanager.h"

#include "base/entity.h"
#include "base/kernel.h"
#include "base/layer.h"

#include "component/filemanager.h"


#include <sstream>

namespace Natorium
{

FontManager::FontManager()
	: m_number_of_chars(512)
	, m_texture_max_width(2048)
{

}

FontManager::~FontManager()
{

}

void FontManager::OnInit()
{
	FT_Error error = FT_Init_FreeType( &m_ft_library );
	assert(error == 0);
}


void FontManager::OnTick(const natU64 _dt)
{

}

void FontManager::OnDeInit()
{
	// TODO: free a lot of stuff
	// WARNING : it leaks for the moment

	FT_Done_FreeType(m_ft_library);
}

Font* FontManager::Get(const natChar* _path, natU32 _fontSize)
{
	natU32 hash = Compute(_path, _fontSize);
	return Get(hash);
}

Font* FontManager::Get(natU32 _id)
{
	Font* ret = nullptr;
	fonts_t::iterator it = m_fonts.find(_id);

	if(it != m_fonts.end())
	{
		ret = it->second;
	}

	return ret;
}

natU32 FontManager::Compute(const natChar* _path, natU32 _fontSize)
{
	std::ostringstream oss;
	oss << _path << ':' << _fontSize;
	return Hash::Compute(oss.str().c_str());
}

void FontManager::Load(const natChar* _path, natU32 _fontSize)
{
	natU32 hash = Compute(_path, _fontSize);

	Font* font = Get(hash);
	
	if(font == nullptr)
	{
		FileManager* filemanager = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<FileManager>();
		assert(filemanager);

		size_t size;
		natU8 *buffer = filemanager->Read(_path, &size);

		font = Load(buffer, size, _fontSize);
		m_fonts[hash] = font;

		delete buffer;
	}
}

// algorithm courtesy of http://damianpaz.wordpress.com/2011/10/09/load-truetype-fonts-with-freetype2-and-build-an-opengl-vertex-array-to-render-text/
Font* FontManager::Load(const natU8* _buffer, size_t _size, natU32 _fontSize)
{
	Font* font = new Font();
	FT_Face ft_face;

	if(FT_New_Memory_Face(m_ft_library, (const FT_Byte*)_buffer, static_cast<FT_Long>(_size), 0, &ft_face))
	{
		assert(false);
	}

	// Set the font size
	FT_Set_Char_Size(ft_face, _fontSize << 6, _fontSize << 6, 96, 96);

	//Initialize the char_info array
	font->m_info.ch.resize(m_number_of_chars);
	font->m_info.max_height = 0;

	// Variables to hold the size the texture must have to hold all the bitmaps
	natU32 max_width = 0;
	natU32 max_rows = 0;

	// Create all the characters
	for(size_t ch=0; ch<m_number_of_chars; ++ch)
	{
		//Load the Glyph for our character.
		if(FT_Load_Glyph( ft_face, FT_Get_Char_Index( ft_face, static_cast<FT_Long>(ch) ), FT_LOAD_NO_HINTING ))
		{
			assert(false);
		}
 
		//Move the face's glyph into a Glyph object.
		FT_Glyph glyph;
		if(FT_Get_Glyph( ft_face->glyph, &glyph ))
		{
			assert(false);
		}

		//Convert the glyph to a bitmap.
		FT_Glyph_To_Bitmap( &glyph, FT_RENDER_MODE_NORMAL, 0, 1 );
		FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;
 
		//This reference will make accessing the bitmap easier
		FT_Bitmap& bitmap=bitmap_glyph->bitmap;
 
		//Get a pointer to the char info for easy access
		Font::char_info_t* char_info = &font->m_info.ch[ch];
		char_info->width = bitmap.width;
		char_info->height = bitmap.rows;

		//Allocate memory for the bitmap data.
		char_info->bitmap = new natU8[2 * char_info->width * char_info->height];
		natU8* char_bmp = char_info->bitmap;
 
		// Fill the bitmap data
		for(size_t j=0; j <char_info->height;++j)
		{
			for(size_t i=0; i < char_info->width; ++i)
			{
				char_bmp[2*(i+j*char_info->width)]= char_bmp[2*(i+j*char_info->width)+1] =
					(i>=bitmap.width || j>=bitmap.rows) ?
					0 : bitmap.buffer[i + bitmap.width*j];
			}
		}

		// Accumulate the width of the bitmaps. Increase the rows if we reached the width of the texture
		max_width += char_info->width;
		if (max_width>m_texture_max_width-1)
		{
			max_width = char_info->width;
			max_rows++;
		}

		// Determine what's the maximum height a given character might have
		if (char_info->height>font->m_info.max_height)
		{
			font->m_info.max_height = char_info->height;
		}
 
		// Store information about this character. We will use this to print it.
		char_info->row = max_rows;
		char_info->left = bitmap_glyph->left;
		char_info->top = bitmap_glyph->top;
		char_info->advance = ft_face->glyph->advance.x >> 6;
		char_info->x = max_width - char_info->width;
	}		

	// Multiply the maximum height a character might have by the amount of rows and calculate the proper (power of two) height the texture must have.
	natU32 texture_height = next_p2(font->m_info.max_height*(max_rows+1));
 
	// Create the temporary buffer for the texture
	natU8* texture_data = new natU8[m_texture_max_width*texture_height*2];

	// Fill the texture, set the vertex and uv array values and delete the bitmap
	for(size_t ch=0; ch<m_number_of_chars; ++ch)
	{
		Font::char_info_t* char_info = &font->m_info.ch[ch];
 
		char_info->y = font->m_info.max_height*char_info->row;
 
		fill_texture_data(ch, &font->m_info, m_texture_max_width,  texture_data);
 
		//(x,h)
		char_info->uv[0].x = (natF32)char_info->x/m_texture_max_width;
		char_info->uv[0].y = (natF32)(char_info->y+char_info->height)/texture_height;
		char_info->v[0].x = 0.0f;
		char_info->v[0].y = (natF32)char_info->height;
 
		//(x,y)
		char_info->uv[1].x = (natF32)char_info->x/m_texture_max_width;              
		char_info->uv[1].y = (natF32)char_info->y/texture_height;
		char_info->v[1].x = 0.0f;
		char_info->v[1].y = 0.0f;
 
		//(w,y)
		char_info->uv[2].x = (natF32)(char_info->x+char_info->width)/m_texture_max_width;
		char_info->uv[2].y = (natF32)(natF32)char_info->y/texture_height;
		char_info->v[2].x = (natF32)char_info->width;
		char_info->v[2].y = 0.0f;
 
		//(w,h)
		char_info->uv[3].x = (natF32)(char_info->x+char_info->width)/m_texture_max_width;
		char_info->uv[3].y = (natF32)(char_info->y+char_info->height)/texture_height;
		char_info->v[3].x = (natF32)char_info->width;
		char_info->v[3].y = (natF32)char_info->height;
 
		delete [] font->m_info.ch[ch].bitmap;
	}

	// todo : maybe use texture manager
	// Create the texture and delete the temporary buffer
	glGenTextures(1, &font->m_texture);
	glBindTexture( GL_TEXTURE_2D, font->m_texture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
 
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, m_texture_max_width, texture_height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, texture_data);
	delete [] texture_data;
 
	FT_Done_Face(ft_face);

	return font;
}

void FontManager::fill_texture_data(size_t ch, Font::font_info_t* font, natU32 texture_width, natU8* texture_data)
{
	Font::char_info_t* char_info = &font->ch[ch];
	natU8* char_bmp = char_info->bitmap;
 
	size_t bmp_pos = 0;
	size_t tex_pos = 0;
 
	natU32 char_x = char_info->x;
	natU32 char_y = char_info->y;
	natU32 char_width = char_info->width;
	natU32 char_height = char_info->height;
 
	for(size_t bmp_y=0; bmp_y<char_height; ++bmp_y)
	{
		for(size_t bmp_x=0; bmp_x<char_width; ++bmp_x)
		{
			bmp_pos = 2 * ( bmp_x + bmp_y * char_width);
			tex_pos = 2 * ( (char_x + bmp_x) + ( (char_y + bmp_y) * texture_width) );
 
			texture_data[tex_pos] = char_bmp[bmp_pos];
			texture_data[tex_pos+1] = char_bmp[bmp_pos+1];
		}
	}
}




}