#include "AddToLobbyHandler.h"

AddToLobbyHandler::AddToLobbyHandler(std::unordered_map<uint32_t, Lobby>& onGoingLobbies, AccountManager& userList) :
	m_onGoingLobbies(onGoingLobbies),
	m_userList(userList)
{}

crow::response AddToLobbyHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto lobbyID = bodyArgs.find("id");
	auto userName = bodyArgs.find("username");
	if (lobbyID != end && userName != end)
	{
		std::string username = userName->second;
		if (m_userList.SearchUser(username))
		{
			auto id = std::stoi(lobbyID->second);
			if (m_onGoingLobbies.contains(id))
			{
				int numberOfPlayersFromLobby = m_onGoingLobbies.at(id).GetNumberOfPlayers();
				if (numberOfPlayersFromLobby < 4)
				{
					m_onGoingLobbies.at(id).AddPlayer(Player(username, Player::Color::NaN));
					return crow::response(200, "Successfully Added Player to Lobby");
				}
				return crow::response(401, "Full lobby");
			}
			return crow::response(404, "No lobby which contains inserted id");
		}
		return crow::response(404, "User list doesn't contain inserted username");
	}
	return crow::response(400, "Lobby ID or/and username isn't/aren't sent properly");
}
