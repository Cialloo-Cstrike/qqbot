#ifndef MSGTYPE_H
#define MSGTYPE_H



enum MessageType_QQ
{
    NOMSG,
    CHANGEMAP,
    SERVERMSG,
    QQMSG,
    PLAYERCONNECT,
    SERVERNAME
    /*
    0 = null (just for maintain the connection)
    1 = changelevel (game server send the map info to relay server)
    2 = in game server player message
    3 = in qq group player message
    4 = player connect to game server*/
};


#endif