#include"Common.h"
#include<unordered_map>

class GameServer : public::Network::net::server_interface<GameMsg>
{
private:
	bool Player1_ = false;
	bool Player2_ = false;

public:
	GameServer(uint16_t nPort) : Network::net::server_interface<GameMsg>(nPort)
	{

	}
	std::unordered_map<uint16_t, PlayerInfo> m_mapPlayerRoster;
	std::vector<uint32_t> m_vGarbageIDs;

protected:
	bool OnClientConnect(std::shared_ptr<Network::net::connection<GameMsg>> client) override
	{
		//Allow all
		return true;
	}

	void OnClientValidated(std::shared_ptr<Network::net::connection<GameMsg>> client) override
	{
		//If client is validated
		//Send them a message informing they can continue to communicate
		Network::net::message<GameMsg> msg;
		msg.header.id = GameMsg::Client_Accepted;
		client->Send(msg);
	}

	void OnClientDisconnect(std::shared_ptr<Network::net::connection<GameMsg>> client) override
	{
		if (client)
		{
			if (m_mapPlayerRoster.find(client->GetID()) == m_mapPlayerRoster.end())
			{
				//Client never added to server
				//Just let it dissapear
			}
			else
			{
				auto& pd = m_mapPlayerRoster[client->GetID()];
				std::cout << "[REMOVED]:" + std::to_string(pd.nUniqueID) + "\n";
				m_mapPlayerRoster.erase(client->GetID());
				m_vGarbageIDs.push_back(client->GetID());

				std::cout << "[REMAINING]: ";
				for (auto& object : m_mapPlayerRoster)
				{
					std::cout << "[" << object.first << "]" << " ";
				}
			}
		}
	}

	void OnMessage(std::shared_ptr<Network::net::connection<GameMsg>> client, Network::net::message<GameMsg>& msg) override
	{
		if (!m_vGarbageIDs.empty())
		{
			for (auto pid : m_vGarbageIDs)
			{
				Network::net::message<GameMsg> m;
				m.header.id = GameMsg::Game_RemovePlayer;
				m << pid;
				std::cout << "\nRemoving " << pid << "\n";
				MessageAllClients(m);
			}
			m_vGarbageIDs.clear();
		}

		switch (msg.header.id)
		{
			case GameMsg::Client_RegisterWithServer:
			{
				PlayerInfo playerInfo;
				msg >> playerInfo;
				playerInfo.nUniqueID = client->GetID();
				if (playerInfo.nUniqueID % 2 == 0)
				{
					playerInfo.p_Pos = { 50.0f,50.0f };
					playerInfo.p_respawnPos = { 50.0f,50.0f };
					//Hp Initialize
					playerInfo.p_Hp.barPercentage = 200.0f;
					playerInfo.p_Hp.currentHp = 10.0f;
					playerInfo.p_Hp.maxHp = 10.0f;
					playerInfo.p_Hp.saveHp = 200.0f;
					playerInfo.p_Hp.receivedDamage = 0.0f;
					playerInfo.p_Hp.cooldown = 0.0f;
					playerInfo.animObj.maxFrame = 2;
					playerInfo.animObj.resetFrame = 0;
					playerInfo.animObj.currentFrame = 0;
					playerInfo.animObj.repeat = 1;
					playerInfo.p_Hp.pos = { 100, 50 };
					playerInfo.win = false;
					playerInfo.lose = false;


				}
				else if (playerInfo.nUniqueID % 2 == 1)
				{
					playerInfo.p_Pos = { 1100.0f,50.0f };
					playerInfo.p_respawnPos = { 1100.0f,50.0f };
					//Hp Initialize
					playerInfo.p_Hp.barPercentage = 200.0f;
					playerInfo.p_Hp.currentHp = 10.0f;
					playerInfo.p_Hp.maxHp = 10.0f;
					playerInfo.p_Hp.saveHp = 200.0f;
					playerInfo.p_Hp.receivedDamage = 0.0f;
					playerInfo.p_Hp.cooldown = 0.0f;
					playerInfo.animObj.maxFrame = 2;
					playerInfo.animObj.resetFrame = 0;
					playerInfo.animObj.currentFrame = 0;
					playerInfo.animObj.repeat = 1;
					playerInfo.facing = LEFT;
					playerInfo.p_Hp.pos = { 980, 50 };
					playerInfo.win = false;
					playerInfo.lose = false;
				}
				m_mapPlayerRoster.insert_or_assign(playerInfo.nUniqueID, playerInfo);

				Network::net::message<GameMsg> msgSendID;
				msgSendID.header.id = GameMsg::Client_AssignID;
				msgSendID << playerInfo.nUniqueID;
				MessageClient(client, msgSendID);

				Network::net::message<GameMsg> msgAvatarID;
				msgAvatarID.header.id = GameMsg::Client_AssignAvatar;
				msgAvatarID << playerInfo.nAvatarID;
				MessageClient(client, msgAvatarID);

				Network::net::message<GameMsg> msgAddPlayer;
				msgAddPlayer.header.id = GameMsg::Game_AddPlayer;
				msgAddPlayer << playerInfo;
				MessageAllClients(msgAddPlayer);

				for (const auto& user : m_mapPlayerRoster)
				{
					Network::net::message<GameMsg> msgAddOtherPlayers;
					msgAddOtherPlayers.header.id = GameMsg::Game_AddPlayer;
					msgAddOtherPlayers << user.second;
					MessageClient(client, msgAddOtherPlayers);
				}
				break;
			}

			case GameMsg::Client_UnregisterWithServer:
			{
				break;
			}

			case GameMsg::Game_UpdatePlayer:
			{
				//Simply bounce update to everyone except incoming client
				MessageAllClients(msg, client);
				break;
			}

			case GameMsg::Server_GetPing:
			{
				//std::cout << "[" << client->GetID() << "]: Server Ping\n";

				// Simply bounce message back to client
				client->Send(msg);
				
			}
		}
	}
};

int main()
{
	GameServer server(60000);
	server.Start();

	while (1)
	{
		server.Update(-1, true);
	}
	return 0;
}