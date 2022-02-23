#include <sourcemod>
#include <socket>
#include <influx/core>

#define NULLMSG 0
#define SURFWR 2
#define SURFFINISH 3

Handle gH_Socket = null;

public Plugin myinfo =
{
    name = "cialloo_qq_surf",
    author = "Cialloo",
    description = "Send a wr message to qq group",
    version = "1.0.0",
    url = "www.cialloo.com"
};

public void OnPluginStart()
{
    CreateConVar("cialloo_qq_surfwr", "1", "1: enable qq msg; 0: disable");
    CreateConVar("cialloo_qq_surffinish", "0");
    CreateConVar("cialloo_qq_hostname", "127.0.0.1");
    CreateConVar("cialloo_qq_port", "51000");
    CreateConVar("cialloo_qq_maintain", "200.0", "send a null message to relay server");
    CreateConVar("cialloo_surf_serverip", "127.0.0.1:27015");
    
    AutoExecConfig(true, "cialloo_qq_surf");
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

public void Influx_OnTimerFinishPost( int client, int runid, int mode, int style, float time, float prev_pb, float prev_best, int flags )
{
    if(gH_Socket == null)
    {
        return;
    }

    ConVar cv_wr = FindConVar("cialloo_qq_surfwr");
    ConVar cv_finish = FindConVar("cialloo_qq_surffinish");
    ConVar cv_hostname = FindConVar("hostname");
    ConVar cv_ip = FindConVar("cialloo_surf_serverip");
    char hostname[64], mapname[64], ip[36], runname[36], stylename[36];

    GetConVarString(cv_hostname, hostname, sizeof(hostname));
    GetConVarString(cv_ip, ip, sizeof(ip));
    GetCurrentMap(mapname, sizeof(mapname));
    Influx_GetRunName(runid, runname, sizeof(runname));
    Influx_GetStyleName(style, stylename, sizeof(stylename));

    if(GetConVarBool(cv_wr) && (time < prev_best || prev_best < 3.0))
    {
        char message[1024];

        FormatEx(message, sizeof(message),
        "%d\n\
        # New Surf Record! #\n\
        %s\n\
        %s\n\
        玩家: %N\n\
        地图: %s\n\
        时间: %.3f\n\
        模式: %s\n\
        线路: %s", 
        SURFWR, 
        hostname, 
        ip, 
        client, 
        mapname, 
        time, 
        stylename, 
        runname);

        SocketSend(gH_Socket, message);
    }

    if(GetConVarBool(cv_finish))
    {
        char message[1024];

        FormatEx(message, sizeof(message),
        "%d\n\
        # Finished map. #\n\
        %s\n\
        %s\n\
        玩家: %N\n\
        地图: %s\n\
        时间: %.3f\n\
        模式: %s\n\
        线路: %s", 
        SURFFINISH, 
        hostname, 
        ip, 
        client, 
        mapname, 
        time, 
        stylename, 
        runname);

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