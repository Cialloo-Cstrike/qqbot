#ifndef SSQ_A2S_INFO_H
#define SSQ_A2S_INFO_H

#include "ssq/ssq.h"

#define A2S_INFO_FLAG_GAMEID   0x01
#define A2S_INFO_FLAG_KEYWORDS 0x20
#define A2S_INFO_FLAG_PORT     0x80
#define A2S_INFO_FLAG_STEAMID  0x10
#define A2S_INFO_FLAG_STV      0x40

#ifdef __cplusplus
extern "C"
{
#endif

enum a2s_server_type
{
    A2S_SERVER_TYPE_DEDICATED      = 'd',
    A2S_SERVER_TYPE_NON_DEDICATED  = 'l',
    A2S_SERVER_TYPE_STV_RELAY      = 'p'
};

enum a2s_environment
{
    A2S_ENVIRONMENT_LINUX   = 'l',
    A2S_ENVIRONMENT_WINDOWS = 'w',
    A2S_ENVIRONMENT_MAC     = 'm'
};

struct a2s_info
{
    uint8_t              protocol;    /** Protocol version used by the server */
    char                *name;        /** Name of the server */
    char                *map;         /** Map the server has currently loaded */
    char                *folder;      /** Name of the folder containing the game files */
    char                *game;        /** Full name of the game */
    uint16_t             id;          /** Steam Application ID of game */
    uint8_t              players;     /** Number of players on the server */
    uint8_t              max_players; /** Maximum number of players the server reports it can hold */
    uint8_t              bots;        /** Number of bots on the server */
    enum a2s_server_type server_type; /** The type of server */
    enum a2s_environment environment; /** The operating system of the server */
    bool                 visibility;  /** Whether the server requires a password */
    bool                 vac;         /** Whether the server uses VAC */
    char                *version;     /** Version of the game installed on the server */
    uint8_t              edf;         /** Extra Data Flag */
    uint16_t             port;        /** The server's game port number */
    uint64_t             steamid;     /** Server's SteamID */
    uint16_t             stv_port;    /** Spectator port number for SourceTV */
    char                *stv_name;    /** Name of the spectator server for SourceTV */
    char                *keywords;    /** Tags that describe the game according to the server */
    uint64_t             gameid;      /** The server's 64-bit GameID */
};

/**
 * Sends an A2S_INFO query.
 * @param querier the Source server querier to use
 * @returns the A2S_INFO response if successful, NULL otherwise
 */
struct a2s_info *ssq_info(struct ssq_querier *querier);

/**
 * Frees an A2S_INFO struct.
 * @param info the A2S_INFO struct to free
 */
void ssq_info_free(struct a2s_info *info);

#ifdef __cplusplus
}
#endif

#endif /* SSQ_A2S_INFO_H */
