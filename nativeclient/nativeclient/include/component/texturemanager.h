#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#if defined(WINDOWS_TARGET)
//#include <Windows.h>
//#include <gl\GL.h>
#include <GL\glew.h>
#endif

#if defined(EMSCRIPTEN_TARGET)
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#endif


#include <string>
#include <map>

namespace Natorium
{

static natU32 s_TextureManager = Hash::Compute("TextureManager");


struct TextureSimple
{
	natU8*	m_buffer;
	size_t	m_size;
};

struct PreloadTextureSimple
{
	std::string m_path;
	size_t		m_option;
};

enum TextureOptions
{
	FLAG_MIPMAPS = 2,
	FLAG_INVERT_Y = 16,
	FLAG_COMPRESS_TO_DXT = 32,
	FLAG_TEXTURE_REPEATS = 33
};

class TextureManager : public Component
{
public:
					TextureManager();
	virtual			~TextureManager();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_TextureManager; }

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);

	void			InitFromDirectory(const natChar* _path);

	void			Preload(const natChar* _path, size_t _options=FLAG_MIPMAPS | FLAG_INVERT_Y | FLAG_COMPRESS_TO_DXT | FLAG_TEXTURE_REPEATS);
	GLuint			Load(const natChar* _path, size_t _options=FLAG_MIPMAPS | FLAG_INVERT_Y | FLAG_COMPRESS_TO_DXT | FLAG_TEXTURE_REPEATS);

	GLuint			Get(const natChar* _path);
	GLuint			Get(natU32 _id);

protected:
	GLuint			Load(const natU8* _bytes, size_t _size, size_t _options);

private:
	typedef std::map<tex_t, GLuint> textures_ref_t;
	textures_ref_t	m_textures;

	typedef std::map<tex_t, struct PreloadTextureSimple> textures_path_t;
	textures_path_t m_preloads;

	typedef std::map<GLuint, struct TextureSimple> textures_buf_t;
	textures_buf_t	m_buffers;

};




}