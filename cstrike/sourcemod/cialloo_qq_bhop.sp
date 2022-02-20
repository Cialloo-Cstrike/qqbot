#include <sourcemod>
#include <socket>
#include <shavit/core>

#define NULLMSG 0
#define BHOPWR 4
#define BHOPFINISH 5

Handle gH_Socket = null;

public Plugin myinfo =
{
    name = "cialloo_qq_bhop",
    author = "Cialloo",
    description = "Send a wr message to qq group",
    version = "1.0.0",
    url = "www.cialloo.com"
};

public void OnPluginStart()
{
    CreateConVar("cialloo_qq_bhopwr", "1", "1: enable qq msg; 0: disable");
    CreateConVar("cialloo_qq_bhopfinish", "0");
    CreateConVar("cialloo_qq_hostname", "127.0.0.1");
    CreateConVar("cialloo_qq_port", "51000");
    CreateConVar("cialloo_qq_maintain", "200.0", "send a null message to relay server");
    CreateConVar("cialloo_bhop_serverip", "127.0.0.1:27015");
    
    AutoExecConfig(true, "cialloo_qq_bhop");
}

public void OnConfigsExecuted()
{
    if(gH_Socket == null)
    {
        CreateSocket();
    }

    ConVar cv_timer = FindConVar("cialloo_qq_maintain");
    CreateTimer(GetConVarFloat(cv_timer), Timer_Maintain, INVALID_HANDLE, TIMER_FLAG_NO_MAPCHANGE);
}

public void Shavit_OnWorldRecord(int client, int style, float time, int jumps, int strafes, float sync, int track, float oldwr, float oldtime, float perfs, float avgvel, float maxvel, int timestamp)
{
    if(gH_Socket == null)
    {
        return;
    }

    ConVar cv_wr = FindConVar("cialloo_qq_bhopwr");
    ConVar cv_hostname = FindConVar("hostname");
    ConVar cv_ip = FindConVar("cialloo_bhop_serverip");
    char hostname[64], mapname[64], ip[36], stylename[36];

    GetConVarString(cv_hostname, hostname, sizeof(hostname));
    GetConVarString(cv_ip, ip, sizeof(ip));
    GetCurrentMap(mapname, sizeof(mapname));
    Shavit_GetStyleStrings(style, sStyleName, stylename, sizeof(stylename));

    if(GetConVarBool(cv_wr))
    {
        char message[1024];

        FormatEx(message, sizeof(message),
        "%d\n\
        # New Bhop Record! #\n\
        server: %s\n\
        ip: %s\n\
        player: %N\n\
        map: %s\n\
        time: %.3f\n\
        style: %s\n\
        jumps: %d\n\
        strafes: %d\n\
        sync: %f\%", 
        BHOPWR, 
        hostname, 
        ip, 
        client, 
        mapname, 
        time, 
        stylename,
        jumps, 
        strafes, 
        sync);

        SocketSend(gH_Socket, message);
    }
}

public void Shavit_OnFinish_Post(int client, int style, float time, int jumps, int strafes, float sync, int rank, int overwrite, int track, float oldtime, float perfs, float avgvel, float maxvel, int timestamp)
{
    if(gH_Socket == null)
    {
        return;
    }

    ConVar cv_finish = FindConVar("cialloo_qq_bhopfinish");
    ConVar cv_hostname = FindConVar("hostname");
    ConVar cv_ip = FindConVar("cialloo_bhop_serverip");
    char hostname[64], mapname[64], ip[36], stylename[36];

    GetConVarString(cv_hostname, hostname, sizeof(hostname));
    GetConVarString(cv_ip, ip, sizeof(ip));
    GetCurrentMap(mapname, sizeof(mapname));
    Shavit_GetStyleStrings(style, sStyleName, stylename, sizeof(stylename));

    if(GetConVarBool(cv_finish))
    {
        char message[1024];

        FormatEx(message, sizeof(message),
        "%d\n\
        # Bhop Finish. #\n\
        server: %s\n\
        ip: %s\n\
        player: %N\n\
        map: %s\n\
        time: %.3f\n\
        style: %s\n\
        jumps: %d\n\
        strafes: %d\n\
        sync: %f\%", 
        BHOPFINISH, 
        hostname, 
        ip, 
        client, 
        mapname, 
        time, 
        stylename,
        jumps, 
        strafes, 
        sync);

        SocketSend(gH_Socket, message);
    }    
}

public void OnSocketReceived(Handle socket, const char[] receiveData, const int dataSize, any arg)
{

}

public void OnSocketConnected(Handle socket, any arg)
{
    PrintToServer("[Cialloo]Socket has connected.");
}

public void OnSocketDisconnected(Handle socket, any arg)
{
    CloseSocket();
}

public void OnSocketError(Handle socket, const int errorType, const int errorNum, any arg)
{
    CloseSocket();
}

public Action Timer_Maintain(Handle timer)
{
    if(gH_Socket == null)
    {
        CreateSocket();
    }

    SocketSend(gH_Socket, "0");
}

stock void CreateSocket()
{
    ConVar cv_hostname = FindConVar("cialloo_qq_hostname");
    ConVar cv_port = FindConVar("cialloo_qq_port");

    char ip[64];
    GetConVarString(cv_hostname, ip, sizeof(ip));
    int port = GetConVarInt(cv_port);
        
    gH_Socket = SocketCreate(SOCKET_TCP, OnSocketError);
    SocketConnect(gH_Socket, OnSocketConnected, OnSocketReceived, OnSocketDisconnected, ip, port);
}

stock void CloseSocket()
{
    if(gH_Socket != null)
    {
        CloseHandle(gH_Socket);
        gH_Socket = null;

        PrintToServer("[Cialloo]Socket has been closed.");
    }
}