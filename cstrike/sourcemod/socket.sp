#include <sourcemod>
#include <socket>

Handle g_hSocket = null;

public void OnPluginStart()
{
    g_hSocket = SocketCreate(SOCKET_TCP, OnSocketError);
    SocketConnect(g_hSocket, OnSocketConnected, OnSocketReceived, OnSocketDisconnected, "127.0.0.1", 51000);
    RegServerCmd("socketsend", Scmd_SocketSend);
}

public Action Scmd_SocketSend(int args)
{
    char buffer[256];
    GetCmdArgString(buffer, sizeof(buffer));
    SocketSend(g_hSocket, buffer);
}

public void OnSocketError(Handle socket, const int errorType, const int errorNum, any arg)
{
}

public void OnSocketConnected(Handle socket, any arg)
{
}

public void OnSocketReceived(Handle socket, const char[] receiveData, const int dataSize, any arg)
{
}

public void OnSocketDisconnected(Handle socket, any arg)
{    
}