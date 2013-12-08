#include "component/netdukemanager.h"

#include "netduke.h"


namespace Natorium
{

NetDukeManager::NetDukeManager()
	: m_netduke(nullptr)
	, m_listeningPort(0)
	, m_isTCP(false)
{

}

NetDukeManager::~NetDukeManager()
{

}

void NetDukeManager::OnInit()
{
	assert(m_netduke == nullptr);
	m_netduke = new NetDuke::NetDuke();
	m_netduke->Init();

	NetDuke::Peer peer;
	peer.SetIPv4Addr("0.0.0.0");
	peer.SetPort(m_listeningPort);

	if(m_isTCP)
	{
		m_netduke->GetTransport().InitTCPStack(peer);
	}
	else
	{
		m_netduke->GetTransport().InitUDPStack(peer);
	}
}

void NetDukeManager::OnTick(const natU64 _dt)
{
	assert(m_netduke);
	m_netduke->Tick();
}

void NetDukeManager::OnDeInit()
{
	assert(m_netduke);
	m_netduke->DeInit();

	delete m_netduke;
	m_netduke = nullptr;
}





}