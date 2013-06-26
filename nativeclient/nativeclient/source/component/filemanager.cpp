#include "component/filemanager.h"

#include "base/entity.h"

#include <cassert>

#include <physfs.h>




namespace Natorium
{

extern char* s_exePath;

FileManager::FileManager()
{

}

FileManager::~FileManager()
{

}

void FileManager::OnInit()
{
	PHYSFS_init(s_exePath);
	assert( PHYSFS_isInit() > 0);

#if defined(WINDOWS_TARGET)
	if(PHYSFS_mount(".\\data\\", "/data", 0) == 0)
	{
		assert(false);
	}
#elif defined(EMSCRIPTEN_TARGET)
	PHYSFS_mount(".\\data\\data.zip", "data", 0);
#else

#endif

}

void FileManager::Clone(Entity* _entity) const
{
	FileManager* component = _entity->AddComponent<FileManager>();
}

void FileManager::OnTick(const natU64 _dt)
{

}

void FileManager::OnDeInit()
{
	PHYSFS_deinit();
}

natU8* FileManager::Read(const natChar* _filename, size_t* _size)
{
	PHYSFS_file* file = PHYSFS_openRead(_filename);
	assert(file);

	*_size = PHYSFS_fileLength(file);
	assert(*_size != 0);

	natU8* buffer = new natU8[*_size];
	PHYSFS_read(file, buffer, 1, static_cast<PHYSFS_uint32>(*_size));

	return buffer;
}


}