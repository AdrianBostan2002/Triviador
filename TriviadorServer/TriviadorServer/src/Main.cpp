#include "AddToAcountListHandler.h"
#include "LoginHandler.h"
#include "NumericalAnswerQuestionHandler.h"
#include "MultipleAnswerQuestionHandler.h"
#include "CreateLobbyHandler.h"
#include "CreateGameHandler.h"
#include "MultipleAnswerQuestion.h"
#include "QuestionManager.h"
#include "Game.h"
#include "Lobby.h"
#include <crow.h>

int main()
{
	AccountManager userList("resource/Accounts.sqlite");
	QuestionManager questionManager("resource/Questions.sqlite");
	questionManager.PopulateStorage();

	crow::SimpleApp app;

	std::unordered_map<uint32_t, Lobby> onGoingLobbies;
	//auto& createNewLobby = CROW_ROUTE(app, "/newLobby");
	//(CreateLobbyHandler(onGoingLobbies));

	CROW_ROUTE(app, "/newLobby")([&onGoingLobbies]()
		{
			Lobby lobby;
			lobby.AddPlayer();
			onGoingLobbies[lobby.GetLobbyID()] = lobby;
			crow::json::wvalue lobbyID
			{
				{"lobby id: ", lobby.GetLobbyID()}
			};
			return crow::json::wvalue(lobbyID);
		});

	CROW_ROUTE(app, "/addToLobby/<int>")([&onGoingLobbies](int lobbyID)
		{
			if (onGoingLobbies.contains(lobbyID))
			{
				if (onGoingLobbies[lobbyID].GetNumberOfPlayers() < 4)
				{
					onGoingLobbies[lobbyID].AddPlayer();
					return crow::response(200, "Successfully Added Player to Lobby");
				}
				return crow::response(401, "Full lobby");
			}
			return crow::response(400, "Lobby not found");
		});

	std::unordered_map<int32_t, Game> ongoingGames;
	//auto& createNewGame = CROW_ROUTE(app, "/newgame/<int>").methods(crow::HTTPMethod::PUT);
	//createNewGame(CreateGameHandler(ongoingGames));

	auto& addUserToAccountList = CROW_ROUTE(app, "/signup").methods(crow::HTTPMethod::PUT);
	addUserToAccountList(AddAccountHandler(userList));

	auto& loginToAccount = CROW_ROUTE(app, "/login").methods(crow::HTTPMethod::POST);
	loginToAccount(LoginHandler(userList));

	auto& getMultipleAnswerQuestion = CROW_ROUTE(app, "/MultipleAnswerQuestion");
	getMultipleAnswerQuestion(MultipleAnswerQuestionHandler(questionManager));

	auto& getNumericalAnswerQuestion = CROW_ROUTE(app, "/NumericalAnswerQuestion");
	getNumericalAnswerQuestion(NumericalAnswerQuestionHandler(questionManager));

	app.port(18080).multithreaded().run();
	return 0;
}
