#pragma once
#include"..\[Server]\Common.h"
#include"Novice.h"

class ClientInterface : public Network::net::client_interface<GameMsg>
{
protected:
	
	uint32_t nPlayerID;
	uint32_t nAvatarID;
	uint32_t nRoomID = 0;
	double PingCount = 0;
	PlayerInfo playerInfo;
	std::unordered_map<uint32_t, PlayerInfo> mapObjects;
	bool bWaitingforConnection = true;

private:
	std::string IPAddressLocal = "127.0.0.1";
	std::string IPAddress1 = "172.20.10.2";


public:
	uint32_t GetID()
	{
		return nPlayerID;
	}
	void PingServer()
	{
		Network::net::message<GameMsg> msg;
		msg.header.id = GameMsg::Server_GetPing;

		std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
		msg << timeNow;
	Send(msg);
	}

	bool OnUserCreate()
	{
		if (Connect(IPAddressLocal, 60000))
		{
			return true;
		}
		return false;
	}

	bool OnUserUpdate()
	{
		if (IsConnected())
		{
			while (!Incoming().empty())
			{
				auto msg = Incoming().pop_front().msg;

				switch (msg.header.id)
				{
					case (GameMsg::Client_Accepted):
					{
						Novice::ScreenPrintf(10, 10, "Server Accepted client - you're in");
						Network::net::message<GameMsg> msg;
						msg.header.id = GameMsg::Client_RegisterWithServer;
						
						msg << playerInfo;
						Send(msg);
						break;
					}

					case(GameMsg::Client_AssignID):
					{
						//Server is assigning us our ID
						msg >> nPlayerID;
						Novice::ScreenPrintf(10, 30, "Assigned Client ID = ", nPlayerID);
						break;
					}

					case(GameMsg::Client_AssignAvatar):
					{
						//Server is assigning us our ID
						msg >> nAvatarID;
						Novice::ScreenPrintf(10, 30, "Assigned Avatar ID = ", nAvatarID);
						break;
					}

					case(GameMsg::Game_AddPlayer):
					{
						PlayerInfo playerInfo;
						msg >> playerInfo;
						mapObjects.insert_or_assign(playerInfo.nUniqueID, playerInfo);

						if (playerInfo.nUniqueID == nPlayerID)
						{
							//Not waiting for connection any longer
							bWaitingforConnection = false;
						}
						break;
					}

					case(GameMsg::Game_RemovePlayer):
					{
						uint32_t nRemovalID = 0;
						msg >> nRemovalID;
						mapObjects.erase(nRemovalID);
						break;

					}
					case(GameMsg::Game_UpdatePlayer):
					{
						PlayerInfo playerInfo;
						msg >> playerInfo;
						mapObjects.insert_or_assign(playerInfo.nUniqueID, playerInfo);
						break;
					}
					case GameMsg::Server_GetPing:
					{
						//Calculate the ping
						std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
						std::chrono::system_clock::time_point timeThen;
						msg >> timeThen;
						PingCount = std::chrono::duration<double>(timeNow - timeThen).count();

						break;
					}
				}
			}
		}
		if (bWaitingforConnection)
		{
			Novice::ScreenPrintf(500, 770, "Waiting to connect...");
		}
		//Send player info
		Network::net::message<GameMsg> Update;
		Update.header.id = GameMsg::Game_UpdatePlayer;
		Update << mapObjects[nPlayerID];
		Send(Update);

		return true;
	}

	
};

