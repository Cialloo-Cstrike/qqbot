#ifndef QQBOT_H
#define QQBOT_H

#include <cstdio>
#include "engine/iserverplugin.h"
#include "igameevents.h"
#include "tier2/tier2.h"
#include "convar.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <eiface.h>
#include <iserver.h>
#include "msgtype.hpp"
#include <cdll_int.h>

void CreateClientSocket();
void* SendMapInfo(void* args);

class QQBot: public IServerPluginCallbacks, public IGameEventListener2
{
public:
	QQBot(){}
	~QQBot(){}

	// IServerPluginCallbacks methods
	virtual bool			Load(	CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory );
	virtual void			Unload( void );
	virtual void			Pause( void ){}
	virtual void			UnPause( void ){}
	virtual const char     *GetPluginDescription( void ){return "qqbot-plugin-version-1.0.1\n";}     
	virtual void			LevelInit( char const *pMapName );
	virtual void			ServerActivate( edict_t *pEdictList, int edictCount, int clientMax ){}
	virtual void			GameFrame( bool simulating ){}
	virtual void			LevelShutdown( void ){}
	virtual void			ClientActive( edict_t *pEntity );
	virtual void			ClientDisconnect( edict_t *pEntity ){}
	virtual void			ClientPutInServer( edict_t *pEntity, char const *playername ){}
	virtual void			SetCommandClient( int index ){}
	virtual void			ClientSettingsChanged( edict_t *pEdict ){}
	virtual PLUGIN_RESULT	ClientConnect( bool *bAllowConnect, edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen ){return PLUGIN_CONTINUE;}
	virtual PLUGIN_RESULT	ClientCommand( edict_t *pEntity, const CCommand &args ){return PLUGIN_CONTINUE;}
	virtual PLUGIN_RESULT	NetworkIDValidated( const char *pszUserName, const char *pszNetworkID ){return PLUGIN_CONTINUE;}
	virtual void			OnQueryCvarValueFinished( QueryCvarCookie_t iCookie, edict_t *pPlayerEntity, EQueryCvarValueStatus eStatus, const char *pCvarName, const char *pCvarValue ){}
	virtual void			OnEdictAllocated( edict_t *edict ){}
	virtual void			OnEdictFreed( const edict_t *edict  ){}	

	// IGameEventListener2 method.
	virtual void FireGameEvent( IGameEvent *event ){}
};

QQBot g_ServerPlugin;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(QQBot, IServerPluginCallbacks, INTERFACEVERSION_ISERVERPLUGINCALLBACKS, g_ServerPlugin );


#endif