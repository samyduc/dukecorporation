#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"


namespace Natorium
{

static natU32 s_FileManager = Hash::Compute("s_FileManager");


class FileManager : public Component
{
public:
					FileManager();
	virtual			~FileManager();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_FileManager; }

	void			Clone(Entity* _entity) const;

	natU8*			Read(const natChar* _filename, size_t* _size);


private:

};




}