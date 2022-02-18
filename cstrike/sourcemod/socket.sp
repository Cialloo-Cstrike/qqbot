#include <sourcemod>
#include <socket>

#define QQMSG 0

Handle g_hSocket = null;

public void OnPluginStart()
{
    RegConsoleCmd("sm_qq", Cmd_QQ, "Send a server message to qq group.");

    CreateConVar("cialloo_socket_hostname", "127.0.0.1");
    CreateConVar("cialloo_socket_port", "51000");
    CreateConVar("cialloo_socket_qqgroup", "123456789", "qq group number.");

    AutoExecConfig(true, "cialloo_socket");
}

public void OnPluginEnd()
{
    if(g_hSocket != null)
    {
        CloseHandle(g_hSocket);
        g_hSocket = null;
    }
}

public void OnConfigsExecuted()
{
    if(g_hSocket == null)
    {
        ConVar cv_hostname = FindConVar("cialloo_socket_hostname");
        ConVar cv_port = FindConVar("cialloo_socket_port");

        char hostname[36];
        int port = GetConVarInt(cv_port);
        GetConVarString(cv_hostname, hostname, sizeof(hostname));
        
        g_hSocket = SocketCreate(SOCKET_TCP, OnSocketError);
        SocketConnect(g_hSocket, OnSocketConnected, OnSocketReceived, OnSocketDisconnected, hostname, port);
    }
}

public Action Cmd_QQ(int client, int args)
{
    char hostname[128],buffer[256], msg[512];
    ConVar cv_hostname = FindConVar("hostname");
    ConVar cv_group = FindConVar("cialloo_socket_qqgroup");

    GetCmdArgString(buffer, sizeof(buffer));
    GetConVarString(cv_hostname, hostname, sizeof(hostname));
    int group = GetConVarInt(cv_group);
    
    FormatEx(msg, sizeof(msg), "%d\n%d\n%s\n%N\n%s", QQMSG, group, hostname, client, buffer);
    SocketSend(g_hSocket, msg);

    return Plugin_Handled;
}

public void OnSocketConnected(Handle socket, any arg)
{
    PrintToServer("Successfully connect to the relay server");
}

public void OnSocketReceived(Handle socket, const char[] receiveData, const int dataSize, any arg)
{
}

public void OnSocketDisconnected(Handle socket, any arg)
{
    if(g_hSocket != null)    
    {
        CloseHandle(g_hSocket);
        g_hSocket = null;
    }
}

public void OnSocketError(Handle socket, const int errorType, const int errorNum, any arg)
{
    if(g_hSocket != null)    
    {
        CloseHandle(g_hSocket);
        g_hSocket = null;
    }
}