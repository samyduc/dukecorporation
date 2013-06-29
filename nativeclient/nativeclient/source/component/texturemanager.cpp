#include "component/texturemanager.h"

#include "base/entity.h"
#include "base/kernel.h"
#include "base/layer.h"
#include "base/component.h"
#include "base/hash.h"

#include "component/filemanager.h"
#include "component/glmanager.h"

#include <SOIL.h>

#include <cassert>


namespace Natorium
{



TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{

}

void TextureManager::OnInit()
{
	/*GLManager* glmanager = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<GLManager>();

	GLuint shader = glmanager->GetShaderProgram();

	glUseProgram(shader);

	glUseProgram(0);*/
}

void TextureManager::Clone(Entity* _entity) const
{
	TextureManager* component = _entity->AddComponent<TextureManager>();
}

void TextureManager::OnTick(const natU64 _dt)
{

}

void TextureManager::OnDeInit()
{
	for(textures_buf_t::iterator it = m_buffers.begin(); it != m_buffers.end(); ++it)
	{
		GLuint id = it->first;
		struct TextureSimple &texture = it->second;

		glDeleteTextures(1, &id);
		delete texture.m_buffer;
	}

	m_buffers.clear();
	m_textures.clear();
}

GLuint TextureManager::Get(const natChar* _path) const
{
	natU32 hash = Hash::Compute(_path);
	return Get(hash);
}

GLuint TextureManager::Get(natU32 _id) const
{
	GLuint ret = 0;
	textures_ref_t::const_iterator it = m_textures.find(_id);

	if(it != m_textures.end())
	{
		ret = it->second;
	}

	return ret;
}

void TextureManager::Load(const natChar* _path)
{
	natU32 hash = Hash::Compute(_path);

	GLuint ret = Get(hash);
	
	if(ret == 0)
	{
		FileManager* filemanager = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<FileManager>();
		assert(filemanager);

		size_t size;
		natU8 *buffer = filemanager->Read(_path, &size);
		struct TextureSimple texture_simple;
		texture_simple.m_buffer = buffer;
		texture_simple.m_size = size;
		m_buffers[hash] = texture_simple;

		ret = Load(buffer, size);
		m_textures[hash] = ret;
	}
}


GLuint TextureManager::Load(const natU8* _bytes, size_t _size)
{
	GLuint ret = SOIL_load_OGL_texture_from_memory(
		_bytes,
		static_cast<int>(_size),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT
	);

	return ret;
}



}