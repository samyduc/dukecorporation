#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"


namespace NetDuke
{
	class NetDuke;
}

namespace Natorium
{

static ref_t s_NetDukeManager = Hash::Compute("NetDukeManager");



class NetDukeManager : public Component
{
public:
					NetDukeManager();
	virtual			~NetDukeManager();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static ref_t	GetType() { return s_NetDukeManager; }

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);



public:
	natBool			m_isTCP;
	natU16			m_listeningPort;

private:
	NetDuke::NetDuke* m_netduke;


};




}