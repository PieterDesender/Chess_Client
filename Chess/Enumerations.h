#pragma once
enum class Color
{
	BLACK,
	WHITE
};
enum class GameState
{
	INITIALISE,
	RUNNING,
	END,
	HELP,
	QUIT
};
enum class PeiceType
{
	PAWN,
	ROOK,
	BISHOP,
	KNIGHT,
	QUEEN,
	KING
};

enum Packet
{
	P_Ack,
	P_Move,
	P_Quit,
	P_Reject,
	P_PlayerInfo,
	P_QuitAck,
	P_Start
};