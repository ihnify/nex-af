/*
Anti-Flood by Nexius v0.7.2
Publics:
OnDialogResponse (0)
OnEnterExitModShop (1)
OnPlayerClickMap (2)
OnPlayerClickPlayer (3)
OnPlayerClickTextDraw (4)
OnPlayerCommandText (5)
OnPlayerDeath (6)
OnPlayerEnterVehicle (7)
OnPlayerExitVehicle (8)
OnPlayerInteriorChange (9)
OnPlayerPickUpPickup (10)
OnPlayerRequestClass (11)
OnPlayerSelectedMenuRow (12)
OnPlayerStateChange (13)
OnVehicleMod (14)
OnVehiclePaintjob (15)
OnVehicleRespray (16)
OnPlayerSpawn (17)
OnVehicleDeath (18)
OnPlayerText (19)
OnPlayerEnterCheckpoint (20)
OnPlayerLeaveCheckpoint (21)
OnPlayerRequestSpawn (22)
OnPlayerExitedMenu (23)
OnPlayerDeath (for killer) (24)
OnIncomingConnection (25)
Other: Cross-public antiflood (26)
*/

#include <a_samp>

#define MIN_CONNECTED_TIME	1000    //Minimum stay player on the server

//Min time call public
//Time in Milliseconds
static const Mtc[27] = {
	250,	//OnDialogResponse
	800,	//OnEnterExitModShop
	150,	//OnPlayerClickMap
	500,	//OnPlayerClickPlayer
	180,	//OnPlayerClickTextDraw
	400,	//OnPlayerCommandText
	3000,	//OnPlayerDeath
	150,	//OnPlayerEnterVehicle
	300,	//OnPlayerExitVehicle
	500,	//OnPlayerInteriorChange
	400,	//OnPlayerPickUpPickup
	180,	//OnPlayerRequestClass
	250,	//OnPlayerSelectedMenuRow
	600,	//OnPlayerStateChange
	530,	//OnVehicleMod
	530,	//OnVehiclePaintjob
	530,	//OnVehicleRespray
	1000,	//OnPlayerSpawn
	600,	//OnVehicleDeath
	400,	//OnPlayerText
	580,	//OnPlayerEnterCheckpoint
	580,	//OnPlayerLeaveCheckpoint
	200,	//OnPlayerRequestSpawn
	350,	//OnPlayerExitedMenu
	320,	//OnPlayerDeath (for killer)
	300,	//OnIncomingConnection
	150/*,	//Cross-public
	580,	//OnPlayerEnterRaceCheckpoint
	580,	//OnPlayerLeaveRaceCheckpoint
	180*/	//OnPlayerClickPlayerTextDraw
},

//Max counts calls
Mfc[27] =
{
	4,		//OnDialogResponse
	2,		//OnEnterExitModShop
	5,		//OnPlayerClickMap
	5,		//OnPlayerClickPlayer
	5,		//OnPlayerClickTextDraw
	4,		//OnPlayerCommandText
	2,		//OnPlayerDeath
	5,		//OnPlayerEnterVehicle
	3,		//OnPlayerExitVehicle
	3,		//OnPlayerInteriorChange
	3,		//OnPlayerPickUpPickup
	5,		//OnPlayerRequestClass
	3,		//OnPlayerSelectedMenuRow
	3,		//OnPlayerStateChange
	3,		//OnVehicleMod
	3,		//OnVehiclePaintjob
	3,		//OnVehicleRespray
	2,		//OnPlayerSpawn
	2,		//OnVehicleDeath
	4,		//OnPlayerText
	3,		//OnPlayerEnterCheckpoint
	3,		//OnPlayerLeaveCheckpoint
	3,		//OnPlayerRequestSpawn
	2,		//OnPlayerExitedMenu
	3,		//OnPlayerDeath (for killer)
	2,		//OnIncomingConnection
	4/*,	//Cross-public
	2,		//OnPlayerEnterRaceCheckpoint
	2,		//OnPlayerLeaveRaceCheckpoint
	5*/		//OnPlayerClickPlayerTextDraw
};

new
	Call[27][MAX_PLAYERS],			//Time call public
	FloodCount[27][MAX_PLAYERS];	//Flood count

forward OnPlayerFlood(playerid, publicid, attempt, time);

public OnPlayerFlood(playerid, publicid, attempt, time)
{
    if(attempt > Mfc[publicid])
	{
	    if(publicid == 25) return Ban(playerid);
		return Kick(playerid);
	}
	return 1;
}

public OnPlayerConnect(playerid)
{
    for(new i = 24; i != -1; --i)
	{
	    Call[i][playerid] = 0;
		FloodCount[i][playerid] = 0;
	}
	new a = 1;
	#if defined af_OnPlayerConnect
		a = af_OnPlayerConnect(playerid);
	#endif
	return a;
}

#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect af_OnPlayerConnect
#if defined af_OnPlayerConnect
    forward af_OnPlayerConnect(playerid);
#endif

public OnPlayerDisconnect(playerid, reason)
{
    new a = 1;
    #if defined af_OnPlayerDisconnect
		a = af_OnPlayerDisconnect(playerid, reason);
	#endif
	if(NetStats_GetConnectedTime(playerid) > MIN_CONNECTED_TIME)
	{
	    FloodCount[25][playerid] = 0;
	    FloodCount[26][playerid] = 0;
	}
	Call[25][playerid] = GetTickCount();
	Call[26][playerid] = Call[25][playerid];
	return a;
}

#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect af_OnPlayerDisconnect
#if defined af_OnPlayerDisconnect
    forward af_OnPlayerDisconnect(playerid, reason);
#endif

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	new gtc = GetTickCount();
    Call[26][playerid] = gtc - Call[26][playerid];
    Call[0][playerid] = gtc - Call[0][playerid];
    if(Call[0][playerid] < Mtc[0])
    {
        FloodCount[0][playerid]++;
		OnPlayerFlood(playerid, 0, FloodCount[0][playerid], Call[0][playerid]);
    }
	else if(Call[26][playerid] < Mtc[26])
	{
		FloodCount[26][playerid]++;
		OnPlayerFlood(playerid, 26, FloodCount[26][playerid], Call[26][playerid]);
	}
    else
	{
	    FloodCount[0][playerid] = 0;
		FloodCount[26][playerid] = 0;
	}
	new a = 1;
	#if defined af_OnDialogResponse
		a = af_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
    #endif
    Call[0][playerid] = GetTickCount();
    Call[26][playerid] = Call[0][playerid];
	return a;
}

#if defined _ALS_OnDialogResponse
    #undef OnDialogResponse
#else
    #define _ALS_OnDialogResponse
#endif
#define OnDialogResponse af_OnDialogResponse
#if defined af_OnDialogResponse
    forward af_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

public OnEnterExitModShop(playerid, enterexit, interiorid)
{
    new gtc = GetTickCount();
    Call[26][playerid] = gtc - Call[26][playerid];
    Call[1][playerid] = gtc - Call[1][playerid];
    if(Call[1][playerid] < Mtc[1])
   	{
		FloodCount[1][playerid]++;
		OnPlayerFlood(playerid, 1, FloodCount[1][playerid], Call[1][playerid]);
	}
    else if(Call[26][playerid] < Mtc[26])
    {
		FloodCount[26][playerid]++;
		OnPlayerFlood(playerid, 26, FloodCount[26][playerid], Call[26][playerid]);
    }
    else
	{
	    FloodCount[1][playerid] = 0;
		FloodCount[26][playerid] = 0;
	}
	new a = 1;
	#if defined af_OnEnterExitModShop
		a = af_OnEnterExitModShop(playerid, enterexit, interiorid);
    #endif
    Call[1][playerid] = GetTickCount();
    Call[26][playerid] = Call[1][playerid];
    return a;
}

#if defined _ALS_OnEnterExitModShop
    #undef OnEnterExitModShop
#else
    #define _ALS_OnEnterExitModShop
#endif
#define OnEnterExitModShop af_OnEnterExitModShop
#if defined af_OnEnterExitModShop
    forward af_OnEnterExitModShop(playerid, enterexit, interiorid);
#endif

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
    new gtc = GetTickCount();
    Call[26][playerid] = gtc - Call[26][playerid];
    Call[2][playerid] = gtc - Call[2][playerid];
    if(Call[2][playerid] < Mtc[2])
	{
		FloodCount[2][playerid]++;
		OnPlayerFlood(playerid, 2, FloodCount[2][playerid], Call[2][playerid]);
	}
    else if(Call[26][playerid] < Mtc[26])
    {
		FloodCount[26][playerid]++;
		OnPlayerFlood(playerid, 26, FloodCount[26][playerid], Call[26][playerid]);
    }
    else
	{
	    FloodCount[2][playerid] = 0;
		FloodCount[26][playerid] = 0;
	}
	new a = 1;
	#if defined af_OnPlayerClickMap
		a = af_OnPlayerClickMap(playerid, fX, fY, fZ);
	#endif
    Call[2][playerid] = GetTickCount();
    Call[26][playerid] = Call[2][playerid];
	return a;
}

#if defined _ALS_OnPlayerClickMap
    #undef OnPlayerClickMap
#else
    #define _ALS_OnPlayerClickMap
#endif
#define OnPlayerClickMap af_OnPlayerClickMap
#if defined af_OnPlayerClickMap
    forward af_OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ);
#endif

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
    new gtc = GetTickCount();
    Call[26][playerid] = gtc - Call[26][playerid];
    Call[3][playerid] = gtc - Call[3][playerid];
    if(Call[3][playerid] < Mtc[3])
	{
		FloodCount[3][playerid]++;
		OnPlayerFlood(playerid, 3, FloodCount[3][playerid], Call[3][playerid]);
	}
    else if(Call[26][playerid] < Mtc[26])
    {
		FloodCount[26][playerid]++;
		OnPlayerFlood(playerid, 26, FloodCount[26][playerid], Call[26][playerid]);
    }
    else
	{
	    FloodCount[3][playerid] = 0;
		FloodCount[26][playerid] = 0;
	}
    new a = 1;
	#if defined af_OnPlayerClickPlayer
		a = af_OnPlayerClickPlayer(playerid, clickedplayerid, source);
	#endif
    Call[3][playerid] = GetTickCount();
    Call[26][playerid] = Call[3][playerid];
	return a;
}

#if defined _ALS_OnPlayerClickPlayer
    #undef OnPlayerClickPlayer
#else
    #define _ALS_OnPlayerClickPlayer
#endif
#define OnPlayerClickPlayer af_OnPlayerClickPlayer
#if defined af_OnPlayerClickPlayer
    forward af_OnPlayerClickPlayer(playerid, clickedplayerid, source);
#endif

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
    new gtc = GetTickCount();
    Call[26][playerid] = gtc - Call[26][playerid];
    Call[4][playerid] = gtc - Call[4][playerid];
    if(Call[4][playerid] < Mtc[4])
	{
		FloodCount[4][playerid]++;
		OnPlayerFlood(playerid, 4, FloodCount[4][playerid], Call[4][playerid]);
	}
    else if(Call[26][playerid] < Mtc[26])
    {
		FloodCount[26][playerid]++;
		OnPlayerFlood(playerid, 26, FloodCount[26][playerid], Call[26][playerid]);
    }
    else
	{
	    FloodCount[4][playerid] = 0;
		FloodCount[26][playerid] = 0;
	}
    new a = 1;
	#if defined af_OnPlayerClickTextDraw
		a = af_OnPlayerClickTextDraw(playerid, clickedid);
	#endif
    Call[4][playerid] = GetTickCount();
    Call[26][playerid] = Call[4][playerid];
	return a;
}

#if defined _ALS_OnPlayerClickTextDraw
	#undef OnPlayerClickTextDraw
#else
	#define _ALS_OnPlayerClickTextDraw
#endif
#define OnPlayerClickTextDraw af_OnPlayerClickTextDraw
#if defined af_OnPlayerClickTextDraw
	forward af_OnPlayerClickTextDraw(playerid, Text:clickedid);
#endif

public OnPlayerCommandText(playerid, cmdtext[])
{
    new gtc = GetTickCount();
    Call[26][playerid] = gtc - Call[26][playerid];
    Call[5][playerid] = gtc - Call[5][playerid];
    if(Call[5][playerid] < Mtc[5])
	{
		FloodCount[5][playerid]++;
		OnPlayerFlood(playerid, 5, FloodCount[5][playerid], Call[5][playerid]);
	}
    else if(Call[26][playerid] < Mtc[26])
    {
		FloodCount[26][playerid]++;
		OnPlayerFlood(playerid, 26, FloodCount[26][playerid], Call[26][playerid]);
    }
    else
	{
	    FloodCount[5][playerid] = 0;
		FloodCount[26][playerid] = 0;
	}
    new a = 1;
	#if defined af_OnPlayerCommandText
		a = af_OnPlayerCommandText(playerid, cmdtext);
	#endif
    Call[5][playerid] = GetTickCount();
    Call[26][playerid] = Call[5][playerid];
	return a;
}

#if defined _ALS_OnPlayerCommandText
	#undef OnPlayerCommandText
#else
	#define _ALS_OnPlayerCommandText
#endif
#define OnPlayerCommandText af_OnPlayerCommandText
#if defined af_OnPlayerCommandText
	forward af_OnPlayerCommandText(playerid, cmdtext[]);
#endif

public OnPlayerDeath(playerid, killerid, reason)
{
	new gtc = GetTickCount();
    Call[26][playerid] = gtc - Call[26][playerid];
    Call[6][playerid] = gtc - Call[6][playerid];
    if(Call[6][playerid] < Mtc[6])
	{
		FloodCount[6][playerid]++;
		OnPlayerFlood(playerid, 6, FloodCount[6][playerid], Call[6][playerid]);
	}
    else if(Call[26][playerid] < Mtc[26])
    {
		FloodCount[26][playerid]++;
		OnPlayerFlood(playerid, 26, FloodCount[26][playerid], Call[26][playerid]);
    }
    else
	{
	    FloodCount[6][playerid] = 0;
		FloodCount[26][playerid] = 0;
	}
	if(killerid != INVALID_PLAYER_ID)
	{
	    Call[26][killerid] = gtc - Call[26][killerid];
    	Call[24][killerid] = Call[6][playerid];

    	if(Call[24][killerid] < Mtc[24])
		{
			FloodCount[24][killerid]++;
			OnPlayerFlood(killerid, 24, FloodCount[24][killerid], Call[24][killerid]);
		}
	    else if(Call[26][killerid] < Mtc[26])
    	{
			FloodCount[26][killerid]++;
			OnPlayerFlood(killerid, 26, FloodCount[26][killerid], Call[26][killerid]);
    	}
    	else
		{
	    	FloodCount[24][killerid] = 0;
			FloodCount[26][killerid] = 0;
		}
	}
    new a = 1;
	#if defined af_OnPlayerDeath
		a = af_OnPlayerDeath(playerid, killerid, reason);
	#endif
    if(killerid != INVALID_PLAYER_ID)
	{
		Call[24][killerid] = GetTickCount();
		Call[26][killerid] = Call[24][killerid];
	}
    Call[6][playerid] = GetTickCount();
    Call[26][playerid] = Call[6][playerid];
	return a;
}

#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath af_OnPlayerDeath
#if defined af_OnPlayerDeath
	forward af_OnPlayerDeath(playerid, killerid, reason);
#endif

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
    new gtc = GetTickCount();
    Call[26][playerid] = gtc - Call[26][playerid];
    Call[7][playerid] = gtc - Call[7][playerid];
    if(Call[7][playerid] < Mtc[7])
	{
		FloodCount[7][playerid]++;
		OnPlayerFlood(playerid, 7, FloodCount[7][playerid], Call[7][playerid]);
	}
	else if(Call[26][playerid] < Mtc[26])
    {
		FloodCount[26][playerid]++;
		OnPlayerFlood(playerid, 26, FloodCount[26][playerid], Call[26][playerid]);
    }
    else
	{
	    FloodCount[7][playerid] = 0;
		FloodCount[26][playerid] = 0;
	}
    new a = 1;
	#if defined af_OnPlayerEnterVehicle
		a = af_OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
	#endif
    Call[7][playerid] = GetTickCount();
    Call[26][playerid] = Call[7][playerid];
	return a;
}

#if defined _ALS_OnPlayerEnterVehicle
	#undef OnPlayerEnterVehicle
#else
	#define _ALS_OnPlayerEnterVehicle
#endif
#define OnPlayerEnterVehicle af_OnPlayerEnterVehicle
#if defined af_OnPlayerEnterVehicle
	forward af_OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
#endif

public OnPlayerExitVehicle(playerid, vehicleid)
{
    new gtc = GetTickCount();
    Call[26][playerid] = gtc - Call[26][playerid];
    Call[8][playerid] = gtc - Call[8][playerid];
    if(Call[8][playerid] < Mtc[8])
	{
		FloodCount[8][playerid]++;
		OnPlayerFlood(playerid, 8, FloodCount[8][playerid], Call[8][playerid]);
	}
    else if(Call[26][playerid] < Mtc[26])
    {
		FloodCount[26][playerid]++;
		OnPlayerFlood(playerid, 26, FloodCount[26][playerid], Call[26][playerid]);
    }
    else
	{
	    FloodCount[8][playerid] = 0;
		FloodCount[26][playerid] = 0;
	}
    new a = 1;
	#if defined af_OnPlayerExitVehicle
		a = af_OnPlayerExitVehicle(playerid, vehicleid);
	#endif
    Call[8][playerid] = GetTickCount();
    Call[26][playerid] = Call[8][playerid];
	return a;
}

#if defined _ALS_OnPlayerExitVehicle
	#undef OnPlayerExitVehicle
#else
	#define _ALS_OnPlayerExitVehicle
#endif
#define OnPlayerExitVehicle af_OnPlayerExitVehicle
#if defined af_OnPlayerExitVehicle
	forward af_OnPlayerExitVehicle(playerid, vehicleid);
#endif

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
    new gtc = GetTickCount();
    Call[26][playerid] = gtc - Call[26][playerid];
    Call[9][playerid] = gtc - Call[9][playerid];
    if(Call[9][playerid] < Mtc[9])
	{
		FloodCount[9][playerid]++;
		OnPlayerFlood(playerid, 9, FloodCount[9][playerid], Call[9][playerid]);
	}
    else if(Call[26][playerid] < Mtc[26])
    {
		FloodCount[26][playerid]++;
		OnPlayerFlood(playerid, 26, FloodCount[26][playerid], Call[26][playerid]);
    }
    else
	{
	    FloodCount[9][playerid] = 0;
		FloodCount[26][playerid] = 0;
	}
    new a = 1;
	#if defined af_OnPlayerInteriorChange
		a = af_OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid);
	#endif
    Call[9][playerid] = GetTickCount();
    Call[26][playerid] = Call[9][playerid];
	return a;
}

#if defined _ALS_OnPlayerInteriorChange
	#undef OnPlayerInteriorChange
#else
	#define _ALS_OnPlayerInteriorChange
#endif
#define OnPlayerInteriorChange af_OnPlayerInteriorChange
#if defined af_OnPlayerInteriorChange
	forward af_OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid);
#endif

public OnPlayerPickUpPickup(playerid, pickupid)
{
    new gtc = GetTickCount();
    Call[26][playerid] = gtc - Call[26][playerid];
    Call[10][playerid] = gtc - Call[10][playerid];
    if(Call[10][playerid] < Mtc[10])
	{
		FloodCount[10][playerid]++;
		OnPlayerFlood(playerid, 10, FloodCount[10][playerid], Call[10][playerid]);
	}
    else if(Call[26][playerid] < Mtc[26])
    {
		FloodCount[26][playerid]++;
		OnPlayerFlood(playerid, 26, FloodCount[26][playerid], Call[26][playerid]);
    }
    else
	{
	    FloodCount[10][playerid] = 0;
		FloodCount[26][playerid] = 0;
	}
    new a = 1;
	#if defined af_OnPlayerPickUpPickup
		a = af_OnPlayerPickUpPickup(playerid, pickupid);
	#endif
    Call[10][playerid] = GetTickCount();
    Call[26][playerid] = Call[10][playerid];
	return a;
}

#if defined _ALS_OnPlayerPickUpPickup
	#undef OnPlayerPickUpPickup
#else
	#define _ALS_OnPlayerPickUpPickup
#endif
#define OnPlayerPickUpPickup af_OnPlayerPickUpPickup
#if defined af_OnPlayerPickUpPickup
	forward af_OnPlayerPickUpPickup(playerid, pickupid);
#endif

public OnPlayerRequestClass(playerid, classid)
{
    new gtc = GetTickCount();
    Call[26][playerid] = gtc - Call[26][playerid];
    Call[11][playerid] = gtc - Call[11][playerid];
    if(Call[11][playerid] < Mtc[11])
	{
		FloodCount[11][playerid]++;
		OnPlayerFlood(playerid, 11, FloodCount[11][playerid], Call[11][playerid]);
	}
	else if(Call[26][playerid] < Mtc[26])
    {
		FloodCount[26][playerid]++;
		OnPlayerFlood(playerid, 26, FloodCount[26][playerid], Call[26][playerid]);
    }
    else
	{
	    FloodCount[11][playerid] = 0;
		FloodCount[26][playerid] = 0;
	}
    new a = 1;
	#if defined af_OnPlayerRequestClass
		a = af_OnPlayerRequestClass(playerid, classid);
	#endif
    Call[11][playerid] = GetTickCount();
    Call[26][playerid] = Call[11][playerid];
	return a;
}

#if defined _ALS_OnPlayerRequestClass
	#undef OnPlayerRequestClass
#else
	#define _ALS_OnPlayerRequestClass
#endif
#define OnPlayerRequestClass af_OnPlayerRequestClass
#if defined af_OnPlayerRequestClass
	forward af_OnPlayerRequestClass(playerid, classid);
#endif

public OnPlayerSelectedMenuRow(playerid, row)
{
    new gtc = GetTickCount();
    Call[26][playerid] = gtc - Call[26][playerid];
    Call[12][playerid] = gtc - Call[12][playerid];
    if(Call[12][playerid] < Mtc[12])
	{
		FloodCount[12][playerid]++;
		OnPlayerFlood(playerid, 12, FloodCount[12][playerid], Call[12][playerid]);
	}
    else if(Call[26][playerid] < Mtc[26])
    {
		FloodCount[26][playerid]++;
		OnPlayerFlood(playerid, 26, FloodCount[26][playerid], Call[26][playerid]);
    }
    else
	{
	    FloodCount[12][playerid] = 0;
		FloodCount[26][playerid] = 0;
	}
    new a = 1;
	#if defined af_OnPlayerSelectedMenuRow
		a = af_OnPlayerSelectedMenuRow(playerid, row);
	#endif
    Call[12][playerid] = GetTickCount();
    Call[26][playerid] = Call[12][playerid];
	return a;
}

#if defined _ALS_OnPlayerSelectedMenuRow
	#undef OnPlayerSelectedMenuRow
#else
	#define _ALS_OnPlayerSelectedMenuRow
#endif
#define OnPlayerSelectedMenuRow af_OnPlayerSelectedMenuRow
#if defined af_OnPlayerSelectedMenuRow
	forward af_OnPlayerSelectedMenuRow(playerid, row);
#endif

public OnPlayerStateChange(playerid, newstate, oldstate)
{
    new gtc = GetTickCount();
    Call[26][playerid] = gtc - Call[26][playerid];
    Call[13][playerid] = gtc - Call[13][playerid];
    if(Call[13][playerid] < Mtc[13])
	{
		FloodCount[13][playerid]++;
		OnPlayerFlood(playerid, 13, FloodCount[13][playerid], Call[13][playerid]);
	}
	else if(Call[26][playerid] < Mtc[26])
	{
		FloodCount[26][playerid]++;
		OnPlayerFlood(playerid, 26, FloodCount[26][playerid], Call[26][playerid]);
    }
    else
	{
	    FloodCount[13][playerid] = 0;
		FloodCount[26][playerid] = 0;
	}
    new a = 1;
	#if defined af_OnPlayerStateChange
		a = af_OnPlayerStateChange(playerid, newstate, oldstate);
	#endif
    Call[13][playerid] = GetTickCount();
    Call[26][playerid] = Call[13][playerid];
	return a;
}

#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif
#define OnPlayerStateChange af_OnPlayerStateChange
#if defined af_OnPlayerStateChange
	forward af_OnPlayerStateChange(playerid, newstate, oldstate);
#endif

public OnVehicleMod(playerid, vehicleid, componentid)
{
    new gtc = GetTickCount();
    Call[26][playerid] = gtc - Call[26][playerid];
    Call[14][playerid] = gtc - Call[14][playerid];
    if(Call[14][playerid] < Mtc[14])
	{
		FloodCount[14][playerid]++;
		OnPlayerFlood(playerid, 14, FloodCount[14][playerid], Call[14][playerid]);
	}
    else if(Call[26][playerid] < Mtc[26])
    {
		FloodCount[26][playerid]++;
		OnPlayerFlood(playerid, 26, FloodCount[26][playerid], Call[26][playerid]);
    }
    else
	{
	    FloodCount[14][playerid] = 0;
		FloodCount[26][playerid] = 0;
	}
    new a = 1;
	#if defined af_OnVehicleMod
		a = af_OnVehicleMod(playerid, vehicleid, componentid);
	#endif
    Call[14][playerid] = GetTickCount();
    Call[26][playerid] = Call[14][playerid];
	return a;
}

#if defined _ALS_OnVehicleMod
	#undef OnVehicleMod
#else
	#define _ALS_OnVehicleMod
#endif
#define OnVehicleMod af_OnVehicleMod
#if defined af_OnVehicleMod
	forward af_OnVehicleMod(playerid, vehicleid, componentid);
#endif

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
    new gtc = GetTickCount();
    Call[26][playerid] = gtc - Call[26][playerid];
    Call[15][playerid] = gtc - Call[15][playerid];
    if(Call[15][playerid] < Mtc[15])
	{
		FloodCount[15][playerid]++;
		OnPlayerFlood(playerid, 15, FloodCount[15][playerid], Call[15][playerid]);
	}
    else if(Call[26][playerid] < Mtc[26])
    {
		FloodCount[26][playerid]++;
		OnPlayerFlood(playerid, 26, FloodCount[26][playerid], Call[26][playerid]);
    }
    else
	{
	    FloodCount[15][playerid] = 0;
		FloodCount[26][playerid] = 0;
	}
    new a = 1;
	#if defined af_OnVehiclePaintjob
		a = af_OnVehiclePaintjob(playerid, vehicleid, paintjobid);
	#endif
    Call[15][playerid] = GetTickCount();
    Call[26][playerid] = Call[15][playerid];
	return a;
}

#if defined _ALS_OnVehiclePaintjob
	#undef OnVehiclePaintjob
#else
	#define _ALS_OnVehiclePaintjob
#endif
#define OnVehiclePaintjob af_OnVehiclePaintjob
#if defined af_OnVehiclePaintjob
	forward af_OnVehiclePaintjob(playerid, vehicleid, paintjobid);
#endif

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
    new gtc = GetTickCount();
    Call[26][playerid] = gtc - Call[26][playerid];
    Call[16][playerid] = gtc - Call[16][playerid];
    if(Call[16][playerid] < Mtc[16])
	{
		FloodCount[16][playerid]++;
		OnPlayerFlood(playerid, 16, FloodCount[16][playerid], Call[16][playerid]);
	}
	else if(Call[26][playerid] < Mtc[26])
    {
		FloodCount[26][playerid]++;
		OnPlayerFlood(playerid, 26, FloodCount[26][playerid], Call[26][playerid]);
    }
    else
	{
	    FloodCount[16][playerid] = 0;
		FloodCount[26][playerid] = 0;
	}
    new a = 1;
	#if defined af_OnVehicleRespray
		a = af_OnVehicleRespray(playerid, vehicleid, color1, color2);
	#endif
    Call[16][playerid] = GetTickCount();
    Call[26][playerid] = Call[16][playerid];
	return a;
}

#if defined _ALS_OnVehicleRespray
	#undef OnVehicleRespray
#else
	#define _ALS_OnVehicleRespray
#endif
#define OnVehicleRespray af_OnVehicleRespray
#if defined af_OnVehicleRespray
	forward af_OnVehicleRespray(playerid, vehicleid, color1, color2);
#endif

public OnPlayerSpawn(playerid)
{
    new gtc = GetTickCount();
    Call[26][playerid] = gtc - Call[26][playerid];
    Call[17][playerid] = gtc - Call[17][playerid];
    if(Call[17][playerid] < Mtc[17])
	{
		FloodCount[17][playerid]++;
		OnPlayerFlood(playerid, 17, FloodCount[17][playerid], Call[17][playerid]);
	}
    else if(Call[26][playerid] < Mtc[26])
    {
		FloodCount[26][playerid]++;
		OnPlayerFlood(playerid, 26, FloodCount[26][playerid], Call[26][playerid]);
    }
    else
	{
	    FloodCount[17][playerid] = 0;
		FloodCount[26][playerid] = 0;
	}
    new a = 1;
	#if defined af_OnPlayerSpawn
		a = af_OnPlayerSpawn(playerid);
	#endif
    Call[17][playerid] = GetTickCount();
    Call[26][playerid] = Call[17][playerid];
	return a;
}

#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn af_OnPlayerSpawn
#if defined af_OnPlayerSpawn
	forward af_OnPlayerSpawn(playerid);
#endif

public OnVehicleDeath(vehicleid, killerid)
{
    new gtc = GetTickCount();
    Call[26][killerid] = gtc - Call[26][killerid];
    Call[18][killerid] = gtc - Call[18][killerid];
    if(Call[18][killerid] < Mtc[18])
	{
		FloodCount[18][killerid]++;
		OnPlayerFlood(killerid, 18, FloodCount[18][killerid], Call[18][killerid]);
	}
	else if(Call[26][killerid] < Mtc[26])
    {
		FloodCount[26][killerid]++;
		OnPlayerFlood(killerid, 26, FloodCount[26][killerid], Call[26][killerid]);
    }
    else
	{
	    FloodCount[18][killerid] = 0;
		FloodCount[26][killerid] = 0;
	}
	new a = 1;
	#if defined af_OnVehicleDeath
		a = af_OnVehicleDeath(vehicleid, killerid);
	#endif
    Call[18][killerid] = GetTickCount();
    Call[26][killerid] = Call[18][killerid];
	return a;
}

#if defined _ALS_OnVehicleDeath
	#undef OnVehicleDeath
#else
	#define _ALS_OnVehicleDeath
#endif
#define OnVehicleDeath af_OnVehicleDeath
#if defined af_OnVehicleDeath
	forward af_OnVehicleDeath(vehicleid, killerid);
#endif

public OnPlayerText(playerid, text[])
{
    new gtc = GetTickCount();
    Call[26][playerid] = gtc - Call[26][playerid];
    Call[19][playerid] = gtc - Call[19][playerid];
    if(Call[19][playerid] < Mtc[19])
	{
		FloodCount[19][playerid]++;
		OnPlayerFlood(playerid, 19, FloodCount[19][playerid], Call[19][playerid]);
	}
    else if(Call[26][playerid] < Mtc[26])
    {
		FloodCount[26][playerid]++;
		OnPlayerFlood(playerid, 26, FloodCount[26][playerid], Call[26][playerid]);
    }
    else
	{
	    FloodCount[19][playerid] = 0;
		FloodCount[26][playerid] = 0;
	}
    new a = 1;
	#if defined af_OnPlayerText
		a = af_OnPlayerText(playerid, text);
	#endif
    Call[19][playerid] = GetTickCount();
    Call[26][playerid] = Call[19][playerid];
	return a;
}

#if defined _ALS_OnPlayerText
	#undef OnPlayerText
#else
	#define _ALS_OnPlayerText
#endif
#define OnPlayerText af_OnPlayerText
#if defined af_OnPlayerText
	forward af_OnPlayerText(playerid, text[]);
#endif

public OnPlayerEnterCheckpoint(playerid)
{
    new gtc = GetTickCount();
    Call[26][playerid] = gtc - Call[26][playerid];
    Call[20][playerid] = gtc - Call[20][playerid];
    if(Call[20][playerid] < Mtc[20])
	{
		FloodCount[20][playerid]++;
		OnPlayerFlood(playerid, 20, FloodCount[20][playerid], Call[20][playerid]);
	}
    else if(Call[26][playerid] < Mtc[26])
    {
		FloodCount[26][playerid]++;
		OnPlayerFlood(playerid, 26, FloodCount[26][playerid], Call[26][playerid]);
    }
    else
	{
	    FloodCount[20][playerid] = 0;
		FloodCount[26][playerid] = 0;
	}
    new a = 1;
	#if defined af_OnPlayerEnterCheckpoint
		a = af_OnPlayerEnterCheckpoint(playerid);
	#endif
    Call[20][playerid] = GetTickCount();
    Call[26][playerid] = Call[20][playerid];
	return a;
}

#if defined _ALS_OnPlayerEnterCheckpoint
	#undef OnPlayerEnterCheckpoint
#else
	#define _ALS_OnPlayerEnterCheckpoint
#endif
#define OnPlayerEnterCheckpoint af_OnPlayerEnterCheckpoint
#if defined af_OnPlayerEnterCheckpoint
	forward af_OnPlayerEnterCheckpoint(playerid);
#endif

public OnPlayerLeaveCheckpoint(playerid)
{
    new gtc = GetTickCount();
    Call[26][playerid] = gtc - Call[26][playerid];
    Call[21][playerid] = gtc - Call[21][playerid];
    if(Call[21][playerid] < Mtc[21])
	{
		FloodCount[21][playerid]++;
		OnPlayerFlood(playerid, 21, FloodCount[21][playerid], Call[21][playerid]);
	}
	else if(Call[26][playerid] < Mtc[26])
    {
		FloodCount[26][playerid]++;
		OnPlayerFlood(playerid, 26, FloodCount[26][playerid], Call[26][playerid]);
    }
    else
	{
	    FloodCount[21][playerid] = 0;
		FloodCount[26][playerid] = 0;
	}
    new a = 1;
	#if defined af_OnPlayerLeaveCheckpoint
		a = af_OnPlayerLeaveCheckpoint(playerid);
	#endif
    Call[21][playerid] = GetTickCount();
    Call[26][playerid] = Call[21][playerid];
	return a;
}

#if defined _ALS_OnPlayerLeaveCheckpoint
	#undef OnPlayerLeaveCheckpoint
#else
	#define _ALS_OnPlayerLeaveCheckpoint
#endif
#define OnPlayerLeaveCheckpoint af_OnPlayerLeaveCheckpoint
#if defined af_OnPlayerLeaveCheckpoint
	forward af_OnPlayerLeaveCheckpoint(playerid);
#endif

public OnPlayerRequestSpawn(playerid)
{
    new gtc = GetTickCount();
    Call[26][playerid] = gtc - Call[26][playerid];
    Call[22][playerid] = gtc - Call[22][playerid];
    if(Call[22][playerid] < Mtc[22])
	{
		FloodCount[22][playerid]++;
		OnPlayerFlood(playerid, 22, FloodCount[22][playerid], Call[22][playerid]);
	}
    else if(Call[26][playerid] < Mtc[26])
    {
		FloodCount[26][playerid]++;
		OnPlayerFlood(playerid, 26, FloodCount[26][playerid], Call[26][playerid]);
    }
    else
	{
	    FloodCount[22][playerid] = 0;
		FloodCount[26][playerid] = 0;
	}
    new a = 1;
	#if defined af_OnPlayerRequestSpawn
		a = af_OnPlayerRequestSpawn(playerid);
	#endif
    Call[22][playerid] = GetTickCount();
    Call[26][playerid] = Call[22][playerid];
	return a;
}

#if defined _ALS_OnPlayerRequestSpawn
	#undef OnPlayerRequestSpawn
#else
	#define _ALS_OnPlayerRequestSpawn
#endif
#define OnPlayerRequestSpawn af_OnPlayerRequestSpawn
#if defined af_OnPlayerRequestSpawn
	forward af_OnPlayerRequestSpawn(playerid);
#endif

public OnPlayerExitedMenu(playerid)
{
    new gtc = GetTickCount();
    Call[26][playerid] = gtc - Call[26][playerid];
    Call[23][playerid] = gtc - Call[23][playerid];
    if(Call[23][playerid] < Mtc[23])
	{
		FloodCount[23][playerid]++;
		OnPlayerFlood(playerid, 23, FloodCount[23][playerid], Call[23][playerid]);
	}
    else if(Call[26][playerid] < Mtc[26])
    {
		FloodCount[26][playerid]++;
		OnPlayerFlood(playerid, 26, FloodCount[26][playerid], Call[26][playerid]);
    }
    else
	{
	    FloodCount[23][playerid] = 0;
		FloodCount[26][playerid] = 0;
	}
    new a = 1;
	#if defined af_OnPlayerExitedMenu
		a = af_OnPlayerExitedMenu(playerid);
	#endif
    Call[23][playerid] = GetTickCount();
    Call[26][playerid] = Call[23][playerid];
	return a;
}

#if defined _ALS_OnPlayerExitedMenu
	#undef OnPlayerExitedMenu
#else
	#define _ALS_OnPlayerExitedMenu
#endif
#define OnPlayerExitedMenu af_OnPlayerExitedMenu
#if defined af_OnPlayerExitedMenu
	forward af_OnPlayerExitedMenu(playerid);
#endif

public OnIncomingConnection(playerid, ip_address[], port)
{
    new gtc = GetTickCount();
    Call[26][playerid] = gtc - Call[26][playerid];
    Call[25][playerid] = gtc - Call[25][playerid];
    if(Call[25][playerid] < Mtc[25])
	{
		FloodCount[25][playerid]++;
		OnPlayerFlood(playerid, 25, FloodCount[25][playerid], Call[25][playerid]);
	}
    else if(Call[26][playerid] < Mtc[26])
    {
		FloodCount[26][playerid]++;
		OnPlayerFlood(playerid, 26, FloodCount[26][playerid], Call[26][playerid]);
    }
    else
	{
	    FloodCount[25][playerid] = 0;
		FloodCount[26][playerid] = 0;
	}
    new a = 1;
	#if defined af_OnIncomingConnection
		a = af_OnIncomingConnection(playerid, ip_address, port);
	#endif
    Call[25][playerid] = GetTickCount();
    Call[26][playerid] = Call[25][playerid];
    return a;
}

#if defined _ALS_OnIncomingConnection
	#undef OnIncomingConnection
#else
	#define _ALS_OnIncomingConnection
#endif
#define OnIncomingConnection af_OnIncomingConnection
#if defined af_OnIncomingConnection
	forward af_OnIncomingConnection(playerid, ip_address[], port);
#endif

/*public OnPlayerEnterRaceCheckpoint(playerid)
{
    new gtc = GetTickCount();
    Call[26][playerid] = gtc - Call[26][playerid];
    Call[27][playerid] = gtc - Call[27][playerid];
    if(Call[27][playerid] < Mtc[27])
	{
		FloodCount[27][playerid]++;
		OnPlayerFlood(playerid, 27, FloodCount[27][playerid], Call[27][playerid]);
	}
    else if(Call[26][playerid] < Mtc[26])
    {
		FloodCount[26][playerid]++;
		OnPlayerFlood(playerid, 26, FloodCount[26][playerid], Call[26][playerid]);
    }
    else
	{
	    FloodCount[27][playerid] = 0;
		FloodCount[26][playerid] = 0;
	}
    new a = 1;
	#if defined af_OnPlayerEnterRaceCheckpoint
		a = af_OnPlayerEnterRaceCheckpoint(playerid);
	#endif
    Call[27][playerid] = GetTickCount();
    Call[26][playerid] = Call[27][playerid];
	return a;
}

#if defined _ALS_OnPlayerEnterRaceCheckpoint
	#undef OnPlayerEnterRaceCheckpoint
#else
	#define _ALS_OnPlayerEnterRaceCheckpoint
#endif
#define OnPlayerEnterRaceCheckpoint af_OnPlayerEnterRaceCheckpoint
#if defined af_OnPlayerEnterRaceCheckpoint
	forward af_OnPlayerEnterRaceCheckpoint(playerid);
#endif*/

/*public OnPlayerLeaveRaceCheckpoint(playerid)
{
    new gtc = GetTickCount();
    Call[26][playerid] = gtc - Call[26][playerid];
    Call[28][playerid] = gtc - Call[28][playerid];
    if(Call[28][playerid] < Mtc[28])
	{
		FloodCount[28][playerid]++;
		OnPlayerFlood(playerid, 28, FloodCount[28][playerid], Call[28][playerid]);
	}
    else if(Call[26][playerid] < Mtc[26])
    {
		FloodCount[26][playerid]++;
		OnPlayerFlood(playerid, 26, FloodCount[26][playerid], Call[26][playerid]);
    }
    else
	{
	    FloodCount[28][playerid] = 0;
		FloodCount[26][playerid] = 0;
	}
    new a = 1;
	#if defined af_OnPlayerLeaveRaceCheckpoint
		a = af_OnPlayerLeaveRaceCheckpoint(playerid);
	#endif
    Call[28][playerid] = GetTickCount();
    Call[26][playerid] = Call[28][playerid];
	return a;
}

#if defined _ALS_OnPlayerLeaveRaceCheckpoint
	#undef OnPlayerLeaveRaceCheckpoint
#else
	#define _ALS_OnPlayerLeaveRaceCheckpoint
#endif
#define OnPlayerLeaveRaceCheckpoint af_OnPlayerLeaveRaceCheckpoint
#if defined af_OnPlayerLeaveRaceCheckpoint
	forward af_OnPlayerLeaveRaceCheckpoint(playerid);
#endif*/

/*public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
    new gtc = GetTickCount();
    Call[26][playerid] = gtc - Call[26][playerid];
    Call[29][playerid] = gtc - Call[29][playerid];
    if(Call[29][playerid] < Mtc[29])
	{
		FloodCount[29][playerid]++;
		OnPlayerFlood(playerid, 29, FloodCount[29][playerid], Call[29][playerid]);
	}
    else if(Call[26][playerid] < Mtc[26])
    {
		FloodCount[26][playerid]++;
		OnPlayerFlood(playerid, 26, FloodCount[26][playerid], Call[26][playerid]);
    }
    else
	{
	    FloodCount[29][playerid] = 0;
		FloodCount[26][playerid] = 0;
	}
    new a = 1;
	#if defined af_OnPlayerClickPlayerTextDraw
		a = af_OnPlayerClickPlayerTextDraw(playerid, playertextid);
	#endif
    Call[29][playerid] = GetTickCount();
    Call[26][playerid] = Call[29][playerid];
	return a;
}

#if defined _ALS_OnPlayerClickPlayerTextDraw
	#undef OnPlayerClickPlayerTextDraw
#else
	#define _ALS_OnPlayerClickPlayerTextDraw
#endif
#define OnPlayerClickPlayerTextDraw af_OnPlayerClickPlayerTextDraw
#if defined af_OnPlayerClickPlayerTextDraw
	forward af_OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid);
#endif*/
