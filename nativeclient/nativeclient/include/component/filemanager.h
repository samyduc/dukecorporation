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

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);

	natU8*			Read(const natChar* _filename, size_t* _size);


private:

};




}