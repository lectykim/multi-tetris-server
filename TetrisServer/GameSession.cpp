#include "pch.h"
#include "GameSession.h"
#include "DeSerialization.h"
void GameSession::OnConnected()
{
	
}

void GameSession::OnDisconnected()
{
}

void GameSession::OnRecvPacket(BYTE* buffer, int len)
{
	shared_ptr<PacketSession> session = GetPacketSessionRef();
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

	
}

void GameSession::OnSend(int len)
{
}
