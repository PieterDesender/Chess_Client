#include "stdafx.h"
#include "ChessGame.h"
#include "Enumerations.h"
#include "Board.h"
#include "Player.h"
#include "MoveParser.h"
#include "Client.h"

ChessGame::ChessGame() :
	m_IPAddres("127.0.0.1"),
	m_Port(1111)
{
}

ChessGame::~ChessGame()
{
	GameEnd();
}

/************************************************** GAME LOOP **********************************************************/
void ChessGame::GameLoop()
{
	while (m_GameState != GameState::QUIT)
	{
		switch (m_GameState)
		{
		case GameState::INITIALISE:
			m_GameState = GameState::END;
			if (GameInitialise())
				m_GameState = GameState::RUNNING;
			break;
		case GameState::HELP:
			GameHelp();
			break;
		case GameState::RUNNING:
			GameRunning();
			break;
		case GameState::END:
			GameEnd();
			m_GameState = GameState::QUIT;
			break;
		}
	}
}
/************************************************** GAME RUNS **********************************************************/
/*INITIALISE*/
/************/
bool ChessGame::GameInitialise()
{
	cout << "\nGame initialize ...";

	if (!Client::GetInstance()->Initialize(m_IPAddres, m_Port)) {
		cout << "\nChessGame::GameInitialise() > Error intitializing winsock";
		return false;
	}
	cout << "\nWinsock initialize done.";

	if (!Client::GetInstance()->Connect()) {
		cout << "\nChessGame::GameInitialise() > Error connecting winsock";
		return false;
	}
	cout << "\nWinsock connect done.";

	Packet packet;

	if (!Client::GetInstance()->GetPacketType(packet)) {
		cout << "\nChessGame::GameInitialise(): 63 > Could not get packet from client.";
		return false;
	}
	cout << "\nPacket received:" << packet;
	if (packet != Packet::P_Ack) {
		if (packet == Packet::P_Reject)
			cout << "\nThe Server has rejected your connection, to many players.\nPlease try again later.";

		return false;
	}
	cout << " Ack received.";

	if (!Client::GetInstance()->GetPacketType(packet)) {
		cout << "\nChessGame::GameInitialise(): 75 > Could not get packet from client.";
		return false;
	}
	cout << "\nPacket received:" << packet;
	if (packet != Packet::P_PlayerInfo) {
		cout << "\nChessGame::GameInitialise(): 81 > Could not receive.";
		return false;
	}
	cout << " player info received.";

	int playerId;
	if (!Client::GetInstance()->GetInt(playerId)) {
		cout << "\nChessGame::GameInitialise(): 87 > could not receive player id.";
		return false;
	}
	cout << "\nPlayer info ID:" << playerId;

	int playerColorInt;
	if (!Client::GetInstance()->GetInt(playerColorInt)) {
		cout << "\nChessGame::GameInitialise(): 93 > could not receive player color.";
		return false;
	}
	cout << "\nPlayer info color:" << playerColorInt;

	if (!Client::GetInstance()->GetPacketType(packet)) {
		cout << "\nChessGame::GameInitialise(): 98 > Could not get packet from client.";
		return false;
	}

	cout << "\nPacket received:" << packet;
	if (packet != Packet::P_Start) {
		cout << "\nChessGame::GameInitialise(): 103 > start not received.";
		return false;
	}
	cout << " start received.";

	Color playerColor = (Color)playerColorInt;
	Color otherPlayerColor = Color::BLACK;

	if (playerColor == Color::BLACK)
		otherPlayerColor = Color::WHITE;

	m_pPlayer = new Player(playerColor);
	m_pOtherPlayer = new Player(otherPlayerColor);

	m_pBoard = new Board(m_pPlayer->GetPlayerColor());
	m_pBoard->PopulateBoard();

	cout << "\nDone";

	return true;
}
/*RUNNING*/
/*********/
void ChessGame::GameRunning()
{
	//Paint the board
	if (m_GameState == GameState::RUNNING)Paint();

	if (m_pPlayer->GetPlayerColor() == Color::WHITE) {
		PlayerMove();
		if (m_GameState == GameState::RUNNING) {
			Paint();
			OtherplayerMove();
		}
	}
	else {
		if (m_GameState == GameState::RUNNING) {
			OtherplayerMove();
			Paint();
		}
		PlayerMove();
	}
}
/*HELP*/
/******/
void ChessGame::GameHelp()
{
	//clear console
	system("cls");
	OutputHelpScreen();
	cout << "Press enter to continue.\n";
	cin.get();
	cin.get();
	m_GameState = GameState::RUNNING;
}
/*GAME END*/
/**********/
void ChessGame::GameEnd()
{
	delete m_pOtherPlayer;
	m_pOtherPlayer = nullptr;
	delete m_pPlayer;
	m_pPlayer = nullptr;
	delete m_pBoard;
	m_pBoard = nullptr;
	MoveParser::GetInstance()->destroy();
	Client::GetInstance()->CloseConnection();
	Client::GetInstance()->destroy();
}
/************************************************** EXTRA GAME FUNCTIONS **********************************************************/
void ChessGame::PlayerMove()
{
	//Player input
	bool validMove = false;
	while (!validMove && m_GameState == GameState::RUNNING) {
		Move parsedMove;
		bool usefullPlayerInput = false;
		while (!usefullPlayerInput) {
			//get the input of the player
			m_PlayerInput = WaitForPlayerInput();

			//HandleInput
			usefullPlayerInput = CheckQuit();
			if (!usefullPlayerInput)usefullPlayerInput = CheckHelp();
			if (!usefullPlayerInput) {
				parsedMove = MoveParser::GetInstance()->ParseMove(m_PlayerInput, m_pPlayer->GetPlayerColor());
				usefullPlayerInput = parsedMove.validParsed;
			}

			if (!usefullPlayerInput)cout << "Use a valid input command. Press h for help.\n";
		}
		//Handle peice move
		if (m_GameState == GameState::RUNNING) {
			if (m_pPlayer->IsMovePossibleAndMove(parsedMove, m_pBoard)) {
				validMove = true;
				Client::GetInstance()->SendPacketType(Packet::P_Move);
				Client::GetInstance()->SendString(parsedMove.unparsedString);
			}
			else {
				cout << "Not a valid move try again.\n";
			}
		}
	}
}
void ChessGame::OtherplayerMove()
{
	Packet packet;
	Client::GetInstance()->GetPacketType(packet);
	string unparsedMove, chat;
	Move move;

	switch (packet)
	{
	case P_Move:
		Client::GetInstance()->GetString(unparsedMove);
		move = MoveParser::GetInstance()->ParseMove(unparsedMove, m_pOtherPlayer->GetPlayerColor());
		m_pOtherPlayer->MovePiece(move, m_pBoard);
		break;
	case P_QuitAck:
		cout << "\nThe other player has quit the game I guess you win.";
		m_GameState = GameState::END;
		break;
	default:
		break;
	}
}
string ChessGame::WaitForPlayerInput()
{
	cout << "\nUser Input: ";
	string input;
	cin >> input;
	transform(input.begin(), input.end(), input.begin(), ::toupper);
	return input;
}
void ChessGame::Paint()
{
	//clear console
	system("cls");
	//paint board
	m_pBoard->Paint(m_pPlayer->GetPlayerColor());
}
bool ChessGame::CheckQuit()
{
	if (m_PlayerInput == "Quit" | m_PlayerInput == "Q" | m_PlayerInput == "q" | m_PlayerInput == "quit") {
		Client::GetInstance()->SendPacketType(Packet::P_Quit);
		m_GameState = GameState::END;
		cout << "\nGAME QUIT";
		return true;
	}
	return false;
}
bool ChessGame::CheckHelp()
{
	if (m_PlayerInput == "Help" | m_PlayerInput == "H" | m_PlayerInput == "h" | m_PlayerInput == "help") {
		m_GameState = GameState::HELP;
		cout << "\nGAME HELP";
		return true;
	}
	return false;
}
void ChessGame::OutputHelpScreen()
{
	cout << "Welcome to the help section\n";
	cout << "Move format:\n";
	cout << "\t'name of play peice''->''column''row'\n";
	cout << "\tExample: Knight 1 to A2 => K1->A2\n";
	cout << "\n\n\nCreated By Pieter Desender\n";
}