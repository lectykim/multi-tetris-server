﻿#include "pch.h"
#include "ServerPacketHandler.h"
#include "DeSerializer.h"
#include "Serializer.h"
char sendData[] = "Hello World";

class ServerSession : public PacketSession
{
public:
	~ServerSession()
	{
		cout << "~ServerSession" << endl;
	}

	virtual void OnConnected() override
	{

		cout << "Connected" << endl;

	}

	virtual void OnRecvPacket(BYTE* buffer, int len) override
	{
		shared_ptr<PacketSession> session = GetPacketSessionRef();
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

		//TODO : PacketId 대역 체크
		auto collection = DeSerilizer::DeSerialize(buffer, len);
		ServerPacketHandler::HandlePacket(session, collection);
	}

	virtual void OnSend(int len) override
	{
		//cout << "OnSend Len = " << len << endl;
	}

	virtual void OnDisconnected() override
	{
		cout << "Disconnected" << endl;
	}
};

int main()
{
	ServerPacketHandler::Init();
	this_thread::sleep_for(1s);

	shared_ptr<ClientService> service = make_shared<ClientService>(
		NetworkConnector(L"127.0.0.1", 7777),
		make_shared<IocpCore>(),
		static_cast<SessionFactory>(make_shared<ServerSession>),
		1
	);

	service->Start();
	for (int i = 0; i < 2; i++)
	{
		GThreadManager->Launch([=]()
			{
				while (true)
				{
					service->GetIocpCore()->Dispatch();
				}
			});
	}

	GThreadManager->Launch([=]() {

		while (true)
		{
			int menu = 0;
			cout << "1. create room, 2. enter room, 3: exit" << endl;

			cin >> menu;
			switch (menu)
			{
			case 1:
			{
				uint16_t roomId = 1;
				string id = "id";
				string password = "password";
				vector<PacketVariant> collection;
				collection.emplace_back(roomId);
				collection.emplace_back(id);
				collection.emplace_back(password);
				auto buffer = ServerPacketHandler::MakeSendBuffer(collection, PKT_CREATE_ROOM);
				service->Broadcast(buffer);
				break;
			}
			case 2:
			{
				break;
			}
			case 3:
			{
				service->CloseService();
				break;
			}
			default:
			{
				break;
			}
			}
		}
		});

	GThreadManager->Join();
}