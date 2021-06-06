#include <stdio.h>
#include "windows.h"
#pragma warning(disable:4996)

//Name given to the pipe
#define g_szPipeName "\\\\.\\Pipe\\MyNamedPipe"
//Pipe name format - \\.\pipe\pipename

#define BUFFER_SIZE 1024 //1k
#define ACK_MESG_RECV "Message received successfully"

int main(int argc, char* argv[])
{
	HANDLE hPipe;

	hPipe = CreateNamedPipe(
		(LPCWSTR)g_szPipeName,             // pipe name 
		PIPE_ACCESS_DUPLEX,       // read/write access 
		PIPE_TYPE_MESSAGE |       // message type pipe 
		PIPE_READMODE_MESSAGE |   // message-read mode 
		PIPE_WAIT,                // blocking mode 
		PIPE_UNLIMITED_INSTANCES, // max. instances  
		BUFFER_SIZE,              // output buffer size 
		BUFFER_SIZE,              // input buffer size 
		NMPWAIT_USE_DEFAULT_WAIT, // client time-out 
		NULL);                    // default security attribute 

	if (INVALID_HANDLE_VALUE == hPipe)
	{
		printf("\nError occurred while "
			"creating the pipe: %d", GetLastError());
		return 1;  //Error
	}
	else
	{
		printf("\nCreateNamedPipe() was successful.");
	}

	printf("\nWaiting for client connection...");

	//Wait for the client to connect
	BOOL bClientConnected = ConnectNamedPipe(hPipe, NULL);

	if (FALSE == bClientConnected)
	{
		//getchar();
		printf("\nError occurred while connecting"
			" to the client: %d", GetLastError());
		CloseHandle(hPipe);
		return 1;  //Error
	}
	else
	{
		printf("\nConnectNamedPipe() was successful.");
	}

	char szBuffer[BUFFER_SIZE];
	DWORD cbBytes;

	//We are connected to the client.
	//To communicate with the client 
	//we will use ReadFile()/WriteFile() 
	//on the pipe handle - hPipe

	//Read client message
	BOOL bResult = ReadFile(
		hPipe,                // handle to pipe 
		szBuffer,             // buffer to receive data 
		sizeof(szBuffer),     // size of buffer 
		&cbBytes,             // number of bytes read 
		NULL);                // not overlapped I/O 

	if ((!bResult) || (0 == cbBytes))
	{
		printf("\nError occurred while reading "
			"from the client: %d", GetLastError());
		CloseHandle(hPipe);
		return 1;  //Error
	}
	else
	{
		printf("\nReadFile() was successful.");
	}

	printf("\nClient sent the following message: %s", szBuffer);

	strcpy(szBuffer, ACK_MESG_RECV);

	//Reply to client
	bResult = WriteFile(
		hPipe,                // handle to pipe 
		szBuffer,             // buffer to write from 
		strlen(szBuffer) + 1,   // number of bytes to write, include the NULL 
		&cbBytes,             // number of bytes written 
		NULL);                // not overlapped I/O 

	if ((!bResult) || (strlen(szBuffer) + 1 != cbBytes))
	{
		printf("\nError occurred while writing"
			" to the client: %d", GetLastError());
		CloseHandle(hPipe);
		return 1;  //Error
	}
	else
	{
		printf("\nWriteFile() was successful.");
	}

	CloseHandle(hPipe);
	
	return 0; //Success
}
