#pragma once
#include "Singleton.h"
#include "Enumerations.h"
class Client : public Singleton<Client>
{
public: //Public functions
	Client() {};
	~Client() {};
	bool Connect();

	bool Initialize(string IP, int PORT);
	bool CloseConnection();
	
	//Sending Funcs
	bool SendInt(int _int);
	bool SendPacketType(Packet _packettype);
	bool SendString(std::string & _string);

	//Getting Funcs
	bool GetInt(int & _int);
	bool GetPacketType(Packet & _packettype);
	bool GetString(std::string & _string);

private:
	SOCKET m_Connection;//This client's connection to the server
	SOCKADDR_IN m_Addr; //Address to be binded to our Connection socket
};