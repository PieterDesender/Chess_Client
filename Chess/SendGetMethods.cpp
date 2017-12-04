#include "stdafx.h"
#include "Client.h"
bool Client::SendInt(int value)
{
	int RetnCheck = send(m_Connection, (char*)&value, sizeof(int), NULL); //send int: _int
	if (RetnCheck == SOCKET_ERROR) //If int failed to send due to connection issue
		return false; //Return false: Connection issue
	return true; //Return true: int successfully sent
}

bool Client::GetInt(int & value)
{
	int RetnCheck = recv(m_Connection, (char*)&value, sizeof(int), NULL); //receive integer
	if (RetnCheck == SOCKET_ERROR) //If there is a connection issue
		return false; //return false since we did not get the integer
	return true;//Return true if we were successful in retrieving the int
}

bool Client::SendPacketType(Packet type)
{
	int RetnCheck = send(m_Connection, (char*)&type, sizeof(Packet), NULL); //Send packet: _packettype
	if (RetnCheck == SOCKET_ERROR) //If packettype failed to send due to connection issue
		return false; //Return false: Connection issue
	return true; //Return true: int successfully sent
}

bool Client::GetPacketType(Packet & type)
{
	int RetnCheck = recv(m_Connection, (char*)&type, sizeof(Packet), NULL); //receive packet type (same as integer)
	if (RetnCheck == SOCKET_ERROR) //If there is a connection issue
		return false; //return false since we did not properly get the packet type
	return true;//Return true if we were successful in retrieving the packet type
}

bool Client::SendString(std::string & value)
{
	int bufferlength = value.size(); //Find string buffer length
	if (!SendInt(bufferlength)) //Send length of string buffer, If sending buffer length fails...
		return false; //Return false: Failed to send string buffer length
	int RetnCheck = send(m_Connection, value.c_str(), bufferlength, NULL); //Send string buffer
	if (RetnCheck == SOCKET_ERROR) //If failed to send string buffer
		return false; //Return false: Failed to send string buffer
	return true; //Return true: string successfully sent
}

bool Client::GetString(std::string & value)
{
	int bufferlength; //Holds length of the message
	if (!GetInt(bufferlength)) //Get length of buffer and store it in variable: bufferlength
		return false; //If get int fails, return false
	char * buffer = new char[bufferlength + 1]; //Allocate buffer
	buffer[bufferlength] = '\0'; //Set last character of buffer to be a null terminator so we aren't printing memory that we shouldn't be looking at
	int RetnCheck = recv(m_Connection, buffer, bufferlength, NULL); //receive message and store the message in buffer array, set RetnCheck to be the value recv returns to see if there is an issue with the connection
	value = buffer; //set string to received buffer message
	delete[] buffer; //Deallocate buffer memory (cleanup to prevent memory leak)
	if (RetnCheck == SOCKET_ERROR) //If connection is lost while getting message
		return false; //If there is an issue with connection, return false
	return true;//Return true if we were successful in retrieving the string
}
