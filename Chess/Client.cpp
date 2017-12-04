#include "stdafx.h"
#include "Client.h"

bool Client::Connect()
{
	m_Connection = socket(AF_INET, SOCK_STREAM, NULL); //Set Connection socket
	if (connect(m_Connection, (SOCKADDR*)&m_Addr, sizeof(m_Addr)) != 0) //If we are unable to connect...
	{
		return false;
	}
	return true;
}

bool Client::Initialize(string IP, int PORT)
{
	//Winsock Startup
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0)
	{
		return false;
	}
	inet_pton(AF_INET, IP.c_str(), &m_Addr.sin_addr);
	m_Addr.sin_port = htons(PORT); //Port to connect on
	m_Addr.sin_family = AF_INET; //IPv4 Socket
	return true;
}

bool Client::CloseConnection()
{
	if (closesocket(m_Connection) == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAENOTSOCK) //If socket error is that operation is not performed on a socket (This happens when the socket has already been closed)
			return true; //return true since connection has already been closed

		std::string ErrorMessage = "Failed to close the socket. Winsock Error: " + std::to_string(WSAGetLastError()) + ".";
		MessageBoxA(NULL, ErrorMessage.c_str(), "Error", MB_OK | MB_ICONERROR);
		return false;
	}
	return true;
}