#include <a_samp>

//Min time call public
//Time in Milliseconds
static const ac_Mtfc[][] =
{
	{150, 5},	//0 OnDialogResponse
	{800, 2},	//1 OnEnterExitModShop
	{250, 5},	//2 OnPlayerClickMap
	{450, 5},	//3 OnPlayerClickPlayer
	{50, 8},	//4 OnPlayerClickTextDraw
	{400, 5},	//5 OnPlayerCommandText
	{50, 8},	//6 OnPlayerEnterVehicle
	{50, 11},	//7 OnPlayerExitVehicle
	{150, 8},	//8 OnPlayerPickUpPickup
	{150, 8},	//9 OnPlayerRequestClass
	{150, 5},	//10 OnPlayerSelectedMenuRow
	{600, 5},	//11 OnPlayerStateChange
	{450, 2},	//12 OnVehicleMod
	{450, 2},	//13 OnVehiclePaintjob
	{450, 2},	//14 OnVehicleRespray
	{300, 1},	//15 OnVehicleDeath
	{450, 3},	//16 OnPlayerText
	{150, 8},	//17 OnPlayerEnterCheckpoint
	{150, 8},	//18 OnPlayerLeaveCheckpoint
	{150, 5},	//19 OnPlayerRequestSpawn
	{150, 5},	//20 OnPlayerExitedMenu
	{150, 8},	//21 OnPlayerEnterRaceCheckpoint
	{150, 8},	//22 OnPlayerLeaveRaceCheckpoint
	{50, 8},	//23 OnPlayerClickPlayerTextDraw
	{150, 5},	//24 OnVehicleDamageStatusUpdate
	{150, 8},	//25 OnVehicleSirenStateChange
	{150, 5},	//26 OnPlayerSelectObject
	{50, 8}		//27 Cross-public
};

enum acInfo{
	acACAllow,
	acCall[sizeof ac_Mtfc],			//Time call public
	acFloodCount[sizeof ac_Mtfc], //Flood count
}	
static 
	ACInfo[MAX_PLAYERS][acInfo];


static 
    ac_vType[] =
{
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0,
	0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 3, 2, 5, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0,
	1, 5, 5, 5, 0, 0, 0, 0, 5, 2, 0, 5, 3, 3, 0, 0, 1, 0, 0, 0,
	0, 4, 0, 0, 3, 0, 0, 2, 2, 0, 0, 0, 0, 3, 0, 0, 0, 2, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 1, 1, 1, 0, 0, 0, 0, 0, 1,
	1, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
	0, 5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 1, 1, 0, 3, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
static ac_IsABoat(modelid) return (430 <= modelid <= 595 && ac_vType[modelid - 400] == 3);


#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnPlayerConnect(playerid)
#else
	public OnPlayerConnect(playerid)
#endif
{
	ACInfo[playerid][acACAllow] = 1; // Enable cheat for player
	#if !defined _inc_y_hooks && !defined _INC_y_hooks\
		&& defined ac_OnPlayerConnect
		return ac_OnPlayerConnect(playerid);
	#else
		return 0;
	#endif
}

#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnPlayerConnect
		#undef OnPlayerConnect
	#else
		#define _ALS_OnPlayerConnect
	#endif
	#define OnPlayerConnect ac_OnPlayerConnect
	#if defined ac_OnPlayerConnect
		forward ac_OnPlayerConnect(playerid);
	#endif
#endif

#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
#else
	public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
#endif
{
	new ac_i = GetTickCount();
	if(ACInfo[playerid][acACAllow])
	{
		if(ac_i < ACInfo[playerid][acCall][0] + ac_Mtfc[0][0]) ac_FloodDetect(playerid, 0);
		else if(ac_i < ACInfo[playerid][acCall][27] + ac_Mtfc[27][0]) ac_FloodDetect(playerid, 27);
		else ACInfo[playerid][acFloodCount][0] = ACInfo[playerid][acFloodCount][27] = 0;
	}
	ACInfo[playerid][acCall][27] = ACInfo[playerid][acCall][0] = ac_i;
	#if !defined _inc_y_hooks && !defined _INC_y_hooks\
		&& defined ac_OnDialogResponse
		return ac_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 0;
	#endif
}

#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnDialogResponse
		#undef OnDialogResponse
	#else
		#define _ALS_OnDialogResponse
	#endif
	#define OnDialogResponse ac_OnDialogResponse
	#if defined ac_OnDialogResponse
		forward ac_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
	#endif
#endif

public OnEnterExitModShop(playerid, enterexit, interiorid)
{
    new ac_i = GetTickCount();
	if(ACInfo[playerid][acACAllow])
	{
		if(ac_i < ACInfo[playerid][acCall][1] + ac_Mtfc[1][0]) ac_FloodDetect(playerid, 1);
		else if(ac_i < ACInfo[playerid][acCall][27] + ac_Mtfc[27][0]) ac_FloodDetect(playerid, 27);
		else ACInfo[playerid][acFloodCount][1] = ACInfo[playerid][acFloodCount][27] = 0;
	}
	ACInfo[playerid][acCall][27] = ACInfo[playerid][acCall][1] = ac_i;
    #if !defined _inc_y_hooks && !defined _INC_y_hooks\
		&& defined ac_OnEnterExitModShop
		return ac_OnEnterExitModShop(playerid, enterexit, interiorid);
	#else
		return 1;
	#endif
}

#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnEnterExitModShop
		#undef OnEnterExitModShop
	#else
		#define _ALS_OnEnterExitModShop
	#endif
	#define OnEnterExitModShop ac_OnEnterExitModShop
	#if defined ac_OnEnterExitModShop
		forward ac_OnEnterExitModShop(playerid, enterexit, interiorid);
	#endif
#endif


#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
#else
	public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
#endif
{
	new ac_gtc = GetTickCount();
	if(ACInfo[playerid][acACAllow])
	{
		if(ac_gtc < ACInfo[playerid][acCall][2] + ac_Mtfc[2][0]) ac_FloodDetect(playerid, 2);
		else if(ac_gtc < ACInfo[playerid][acCall][27] + ac_Mtfc[27][0]) ac_FloodDetect(playerid, 27);
		else ACInfo[playerid][acFloodCount][2] = ACInfo[playerid][acFloodCount][27] = 0;
	}
	ACInfo[playerid][acCall][27] = ACInfo[playerid][acCall][2] = ac_gtc;
	#if !defined _inc_y_hooks && !defined _INC_y_hooks\
		&& defined ac_OnPlayerClickMap
		return ac_OnPlayerClickMap(playerid, fX, fY, fZ);
	#else
		return 0;
	#endif
}

#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnPlayerClickMap
		#undef OnPlayerClickMap
	#else
		#define _ALS_OnPlayerClickMap
	#endif
	#define OnPlayerClickMap ac_OnPlayerClickMap
	#if defined ac_OnPlayerClickMap
		forward ac_OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ);
	#endif
#endif


#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnPlayerClickPlayer(playerid, clickedplayerid, source)
#else
	public OnPlayerClickPlayer(playerid, clickedplayerid, source)
#endif
{
	new ac_gtc = GetTickCount();
	if(ACInfo[playerid][acACAllow])
	{
		if(ac_gtc < ACInfo[playerid][acCall][3] + ac_Mtfc[3][0])
		{
			ac_FloodDetect(playerid, 3);
			return 1;
		}
		if(ac_gtc < ACInfo[playerid][acCall][27] + ac_Mtfc[27][0]) ac_FloodDetect(playerid, 27);
		else ACInfo[playerid][acFloodCount][3] = ACInfo[playerid][acFloodCount][27] = 0;
	}
	ACInfo[playerid][acCall][27] = ACInfo[playerid][acCall][3] = ac_gtc;
	#if !defined _inc_y_hooks && !defined _INC_y_hooks\
		&& defined ac_OnPlayerClickPlayer
		return ac_OnPlayerClickPlayer(playerid, clickedplayerid, source);
	#else
		return 0;
	#endif
}

#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnPlayerClickPlayer
		#undef OnPlayerClickPlayer
	#else
		#define _ALS_OnPlayerClickPlayer
	#endif
	#define OnPlayerClickPlayer ac_OnPlayerClickPlayer
	#if defined ac_OnPlayerClickPlayer
		forward ac_OnPlayerClickPlayer(playerid, clickedplayerid, source);
	#endif
#endif

#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnPlayerClickTextDraw(playerid, Text:clickedid)
#else
	public OnPlayerClickTextDraw(playerid, Text:clickedid)
#endif
{
	new ac_gtc = GetTickCount();
	if(ACInfo[playerid][acACAllow])
	{
		if(ac_gtc < ACInfo[playerid][acCall][4] + ac_Mtfc[4][0])
		{
			ac_FloodDetect(playerid, 4);
			return 1;
		}
		if(ac_gtc < ACInfo[playerid][acCall][27] + ac_Mtfc[27][0]) ac_FloodDetect(playerid, 27);
		else ACInfo[playerid][acFloodCount][4] = ACInfo[playerid][acFloodCount][27] = 0;
	}
	ACInfo[playerid][acCall][27] = ACInfo[playerid][acCall][4] = ac_gtc;
	#if !defined _inc_y_hooks && !defined _INC_y_hooks\
		&& defined ac_OnPlayerClickTextDraw
		return ac_OnPlayerClickTextDraw(playerid, clickedid);
	#else
		return 0;
	#endif
}

#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnPlayerClickTextDraw
		#undef OnPlayerClickTextDraw
	#else
		#define _ALS_OnPlayerClickTextDraw
	#endif
	#define OnPlayerClickTextDraw ac_OnPlayerClickTextDraw
	#if defined ac_OnPlayerClickTextDraw
		forward ac_OnPlayerClickTextDraw(playerid, Text:clickedid);
	#endif
#endif

#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnPlayerCommandText(playerid, cmdtext[])
#else
	public OnPlayerCommandText(playerid, cmdtext[])
#endif
{
	if(!IsPlayerNPC(playerid))
	{
		new ac_gtc = GetTickCount();
		if(ACInfo[playerid][acACAllow])
		{
			if(ac_gtc < ACInfo[playerid][acCall][5] + ac_Mtfc[5][0])
			{
				ac_FloodDetect(playerid, 5);
				return 1;
			}
			if(ac_gtc < ACInfo[playerid][acCall][27] + ac_Mtfc[27][0]) ac_FloodDetect(playerid, 27);
			else ACInfo[playerid][acFloodCount][5] = ACInfo[playerid][acFloodCount][27] = 0;
		}
		ACInfo[playerid][acCall][27] = ACInfo[playerid][acCall][5] = ac_gtc;
	}
	#if !defined _inc_y_hooks && !defined _INC_y_hooks\
		&& defined ac_OnPlayerCommandText
		return ac_OnPlayerCommandText(playerid, cmdtext);
	#else
		return 0;
	#endif
}

#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnPlayerCommandText
		#undef OnPlayerCommandText
	#else
		#define _ALS_OnPlayerCommandText
	#endif
	#define OnPlayerCommandText ac_OnPlayerCommandText
	#if defined ac_OnPlayerCommandText
		forward ac_OnPlayerCommandText(playerid, cmdtext[]);
	#endif
#endif


#if defined _inc_y_hooks || defined _INC_y_hooks
    hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
#else
	public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
#endif
{
	if(!(0 <= playerid < MAX_PLAYERS)) return 0;
	new ac_gtc = GetTickCount();
	if(ACInfo[playerid][acACAllow])
	{
		if(ac_gtc < ACInfo[playerid][acCall][6] + ac_Mtfc[6][0]) ac_FloodDetect(playerid, 6);
		if(ac_gtc < ACInfo[playerid][acCall][27] + ac_Mtfc[27][0]) ac_FloodDetect(playerid, 27);
		else ACInfo[playerid][acFloodCount][6] = ACInfo[playerid][acFloodCount][27] = 0;
	}
	ACInfo[playerid][acCall][27] = ACInfo[playerid][acCall][6] = ac_gtc;
	#if !defined _inc_y_hooks && !defined _INC_y_hooks\
		&& defined ac_OnPlayerEnterVehicle
		return ac_OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
	#else
		return 1;
	#endif
}

#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnPlayerEnterVehicle
		#undef OnPlayerEnterVehicle
	#else
		#define _ALS_OnPlayerEnterVehicle
	#endif
	#define OnPlayerEnterVehicle ac_OnPlayerEnterVehicle
	#if defined ac_OnPlayerEnterVehicle
		forward ac_OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
	#endif
#endif

#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnPlayerExitVehicle(playerid, vehicleid)
#else
	public OnPlayerExitVehicle(playerid, vehicleid)
#endif
{
	if(!(0 <= playerid < MAX_PLAYERS)) return 0;
	new ac_gtc = GetTickCount();
	if(ACInfo[playerid][acACAllow])
	{
		if(ac_gtc < ACInfo[playerid][acCall][7] + ac_Mtfc[7][0]) ac_FloodDetect(playerid, 7);
		if(ac_gtc < ACInfo[playerid][acCall][27] + ac_Mtfc[27][0]) ac_FloodDetect(playerid, 27);
		else ACInfo[playerid][acFloodCount][7] = ACInfo[playerid][acFloodCount][27] = 0;
	}
	ACInfo[playerid][acCall][27] = ACInfo[playerid][acCall][7] = ac_gtc;
	#if !defined _inc_y_hooks && !defined _INC_y_hooks\
		&& defined ac_OnPlayerExitVehicle
		return ac_OnPlayerExitVehicle(playerid, vehicleid);
	#else
		return 1;
	#endif
}

#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnPlayerExitVehicle
		#undef OnPlayerExitVehicle
	#else
		#define _ALS_OnPlayerExitVehicle
	#endif
	#define OnPlayerExitVehicle ac_OnPlayerExitVehicle
	#if defined ac_OnPlayerExitVehicle
		forward ac_OnPlayerExitVehicle(playerid, vehicleid);
	#endif
#endif

#if defined OnPlayerPickUpDynamicPickup\
	&& defined Streamer_GetDistanceToItem\
	&& defined Streamer_GetIntData
	#if defined _inc_y_hooks || defined _INC_y_hooks
		#if defined STREAMER_ENABLE_TAGS
			hook OnPlayerPickUpDynPickup(playerid, STREAMER_TAG_PICKUP:pickupid)
		#else
			hook OnPlayerPickUpDynPickup(playerid, pickupid)
		#endif
	#else
		#if defined STREAMER_ENABLE_TAGS
			public OnPlayerPickUpDynamicPickup(playerid, STREAMER_TAG_PICKUP:pickupid)
		#else
			public OnPlayerPickUpDynamicPickup(playerid, pickupid)
		#endif
	#endif
	{
		if(!(0 <= playerid < MAX_PLAYERS)) return 0;
		new ac_i = GetTickCount();
		if(ACInfo[playerid][acACAllow])
		{
			if(ac_i < ACInfo[playerid][acCall][8] + ac_Mtfc[8][0]) ac_FloodDetect(playerid, 8);
			else if(ac_i < ACInfo[playerid][acCall][27] + ac_Mtfc[27][0]) ac_FloodDetect(playerid, 27);
			else ACInfo[playerid][acFloodCount][8] = ACInfo[playerid][acFloodCount][27] = 0;
		}
		ACInfo[playerid][acCall][27] = ACInfo[playerid][acCall][8] = ac_i;
		#if !defined _inc_y_hooks && !defined _INC_y_hooks\
			&& defined ac_OnPlayerPickUpDynamicPickup
			return ac_OnPlayerPickUpDynamicPickup(playerid, pickupid);
		#else
			return 1;
		#endif
	}

	#if !defined _inc_y_hooks && !defined _INC_y_hooks
		#if defined _ALS_OnPlayerPickUpDynamicPicku\
			|| defined _ALS_OnPlayerPickUpDynPickup\
			|| defined _ALS_OnPlayerPickUpDynamicPick || defined _ALS_OnPlayerPickUpDynamicPUp
			#undef OnPlayerPickUpDynamicPickup
		#else
			#define _ALS_OnPlayerPickUpDynPickup
		#endif
		#define OnPlayerPickUpDynamicPickup ac_OnPlayerPickUpDynamicPickup
		#if defined ac_OnPlayerPickUpDynamicPickup
			#if defined STREAMER_ENABLE_TAGS
				forward ac_OnPlayerPickUpDynamicPickup(playerid, STREAMER_TAG_PICKUP:pickupid);
			#else
				forward ac_OnPlayerPickUpDynamicPickup(playerid, pickupid);
			#endif
		#endif
	#endif
#endif


#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnPlayerPickUpPickup(playerid, pickupid)
#else
	public OnPlayerPickUpPickup(playerid, pickupid)
#endif
{
	if(!(0 <= playerid < MAX_PLAYERS) || !(0 <= pickupid < MAX_PICKUPS)) return 0;
	#if defined Streamer_GetItemStreamerID\
		&& defined IsValidDynamicPickup
		#if defined STREAMER_ENABLE_TAGS
			new STREAMER_TAG_PICKUP:streamerid = STREAMER_TAG_PICKUP:Streamer_GetItemStreamerID(playerid, STREAMER_TYPE_PICKUP, pickupid);
		#else
			new streamerid = Streamer_GetItemStreamerID(playerid, STREAMER_TYPE_PICKUP, pickupid);
		#endif
		if(!IsValidDynamicPickup(streamerid))
		{
	#endif
		new ac_i = GetTickCount();
		if(ACInfo[playerid][acACAllow])
		{
			if(ac_i < ACInfo[playerid][acCall][8] + ac_Mtfc[8][0]) ac_FloodDetect(playerid, 8);
			else if(ac_i < ACInfo[playerid][acCall][27] + ac_Mtfc[27][0]) ac_FloodDetect(playerid, 27);
			else ACInfo[playerid][acFloodCount][8] = ACInfo[playerid][acFloodCount][27] = 0;
		}
		ACInfo[playerid][acCall][27] = ACInfo[playerid][acCall][8] = ac_i;
	#if defined Streamer_GetItemStreamerID\
		&& defined IsValidDynamicPickup
		}
	#endif
	#if !defined _inc_y_hooks && !defined _INC_y_hooks\
		&& defined ac_OnPlayerPickUpPickup
		return ac_OnPlayerPickUpPickup(playerid, pickupid);
	#else
		return 1;
	#endif
}

#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnPlayerPickUpPickup
		#undef OnPlayerPickUpPickup
	#else
		#define _ALS_OnPlayerPickUpPickup
	#endif
	#define OnPlayerPickUpPickup ac_OnPlayerPickUpPickup
	#if defined ac_OnPlayerPickUpPickup
		forward ac_OnPlayerPickUpPickup(playerid, pickupid);
	#endif
#endif

#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnPlayerRequestClass(playerid, classid)
#else
	public OnPlayerRequestClass(playerid, classid)
#endif
{
	if(!IsPlayerNPC(playerid))
	{
		new ac_gtc = GetTickCount();
		if(ACInfo[playerid][acACAllow])
		{
			if(ac_gtc < ACInfo[playerid][acCall][9] + ac_Mtfc[9][0]) ac_FloodDetect(playerid, 9);
			else if(ac_gtc < ACInfo[playerid][acCall][27] + ac_Mtfc[27][0]) ac_FloodDetect(playerid, 27);
			else ACInfo[playerid][acFloodCount][9] = ACInfo[playerid][acFloodCount][27] = 0;
		}
		ACInfo[playerid][acCall][27] = ACInfo[playerid][acCall][9] = ac_gtc;
	}
	#if !defined _inc_y_hooks && !defined _INC_y_hooks\
		&& defined ac_OnPlayerRequestClass
		return ac_OnPlayerRequestClass(playerid, classid);
	#else
		return 1;
	#endif
}

#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnPlayerRequestClass
		#undef OnPlayerRequestClass
	#else
		#define _ALS_OnPlayerRequestClass
	#endif
	#define OnPlayerRequestClass ac_OnPlayerRequestClass
	#if defined ac_OnPlayerRequestClass
		forward ac_OnPlayerRequestClass(playerid, classid);
	#endif
#endif

#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnPlayerSelectedMenuRow(playerid, row)
#else
	public OnPlayerSelectedMenuRow(playerid, row)
#endif
{
	if(!(0 <= playerid < MAX_PLAYERS)) return 0;
	new ac_gtc = GetTickCount();
	if(ACInfo[playerid][acACAllow])
	{
		if(ac_gtc < ACInfo[playerid][acCall][10] + ac_Mtfc[10][0]) ac_FloodDetect(playerid, 10);
		else if(ac_gtc < ACInfo[playerid][acCall][27] + ac_Mtfc[27][0]) ac_FloodDetect(playerid, 27);
		else ACInfo[playerid][acFloodCount][10] = ACInfo[playerid][acFloodCount][27] = 0;
	}
	ACInfo[playerid][acCall][27] = ACInfo[playerid][acCall][10] = ac_gtc;
	#if !defined _inc_y_hooks && !defined _INC_y_hooks\
		&& defined ac_OnPlayerSelectedMenuRow
		return ac_OnPlayerSelectedMenuRow(playerid, row);
	#else
		return 1;
	#endif
}

#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnPlayerSelectedMenuRow
		#undef OnPlayerSelectedMenuRow
	#else
		#define _ALS_OnPlayerSelectedMenuRow
	#endif
	#define OnPlayerSelectedMenuRow ac_OnPlayerSelectedMenuRow
	#if defined ac_OnPlayerSelectedMenuRow
		forward ac_OnPlayerSelectedMenuRow(playerid, row);
	#endif
#endif

#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnPlayerStateChange(playerid, newstate, oldstate)
#else
	public OnPlayerStateChange(playerid, newstate, oldstate)
#endif
{
	if(!IsPlayerNPC(playerid))
	{
		new ac_i = GetTickCount();
		if(ACInfo[playerid][acACAllow])
		{
			if(ac_i < ACInfo[playerid][acCall][11] + ac_Mtfc[11][0])
			{
				if(newstate != PLAYER_STATE_ONFOOT || oldstate != PLAYER_STATE_SPAWNED)
				{
					new ac_model;
					if(oldstate == PLAYER_STATE_DRIVER) ac_model = GetVehicleModel(playerid);
					else if(newstate == PLAYER_STATE_DRIVER) ac_model = GetVehicleModel(GetPlayerVehicleID(playerid));
					if(!ac_IsABoat(ac_model)) ac_FloodDetect(playerid, 11);
				}
			}
			else if(ac_i < ACInfo[playerid][acCall][27] + ac_Mtfc[27][0]) ac_FloodDetect(playerid, 27);
			else ACInfo[playerid][acFloodCount][11] = ACInfo[playerid][acFloodCount][27] = 0;
		}
		ACInfo[playerid][acCall][27] = ACInfo[playerid][acCall][11] = ac_i;
	}
	#if !defined _inc_y_hooks && !defined _INC_y_hooks\
		&& defined ac_OnPlayerStateChange
		return ac_OnPlayerStateChange(playerid, newstate, oldstate);
	#else
		return 1;
	#endif
}

#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnPlayerStateChange
		#undef OnPlayerStateChange
	#else
		#define _ALS_OnPlayerStateChange
	#endif
	#define OnPlayerStateChange ac_OnPlayerStateChange
	#if defined ac_OnPlayerStateChange
		forward ac_OnPlayerStateChange(playerid, newstate, oldstate);
	#endif
#endif

#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnVehicleMod(playerid, vehicleid, componentid)
#else
	public OnVehicleMod(playerid, vehicleid, componentid)
#endif
{
	new ac_i = GetTickCount();
	if(ACInfo[playerid][acACAllow])
	{
		if(ac_i < ACInfo[playerid][acCall][12] + ac_Mtfc[12][0]) return ac_FloodDetect(playerid, 12);
		if(ac_i < ACInfo[playerid][acCall][27] + ac_Mtfc[27][0]) ac_FloodDetect(playerid, 27);
		else ACInfo[playerid][acFloodCount][12] = ACInfo[playerid][acFloodCount][27] = 0;
	}
	ACInfo[playerid][acCall][27] = ACInfo[playerid][acCall][12] = ac_i;
	#if !defined _inc_y_hooks && !defined _INC_y_hooks\
		&& defined ac_OnVehicleMod
		return ac_OnVehicleMod(playerid, vehicleid, componentid);
	#else
		return 1;
	#endif
}

#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnVehicleMod
		#undef OnVehicleMod
	#else
		#define _ALS_OnVehicleMod
	#endif
	#define OnVehicleMod ac_OnVehicleMod
	#if defined ac_OnVehicleMod
		forward ac_OnVehicleMod(playerid, vehicleid, componentid);
	#endif
#endif

#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnVehiclePaintjob(playerid, vehicleid, paintjobid)
#else
	public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
#endif
{
	new ac_gtc = GetTickCount();
	if(ACInfo[playerid][acACAllow])
	{
		if(ac_gtc < ACInfo[playerid][acCall][13] + ac_Mtfc[13][0]) ac_FloodDetect(playerid, 13);
		else if(ac_gtc < ACInfo[playerid][acCall][27] + ac_Mtfc[27][0]) ac_FloodDetect(playerid, 27);
		else ACInfo[playerid][acFloodCount][13] = ACInfo[playerid][acFloodCount][27] = 0;
	}
	ACInfo[playerid][acCall][27] = ACInfo[playerid][acCall][13] = ac_gtc;
	#if !defined _inc_y_hooks && !defined _INC_y_hooks\
		&& defined ac_OnVehiclePaintjob
		return ac_OnVehiclePaintjob(playerid, vehicleid, paintjobid);
	#else
		return 1;
	#endif
}

#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnVehiclePaintjob
		#undef OnVehiclePaintjob
	#else
		#define _ALS_OnVehiclePaintjob
	#endif
	#define OnVehiclePaintjob ac_OnVehiclePaintjob
	#if defined ac_OnVehiclePaintjob
		forward ac_OnVehiclePaintjob(playerid, vehicleid, paintjobid);
	#endif
#endif

#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnVehicleRespray(playerid, vehicleid, color1, color2)
#else
	public OnVehicleRespray(playerid, vehicleid, color1, color2)
#endif
{
	new ac_gtc = GetTickCount();
	if(ACInfo[playerid][acACAllow])
	{
		if(ac_gtc < ACInfo[playerid][acCall][14] + ac_Mtfc[14][0]) return ac_FloodDetect(playerid, 14);
		if(ac_gtc < ACInfo[playerid][acCall][27] + ac_Mtfc[27][0]) ac_FloodDetect(playerid, 27);
		else ACInfo[playerid][acFloodCount][14] = ACInfo[playerid][acFloodCount][27] = 0;
	}
	ACInfo[playerid][acCall][27] = ACInfo[playerid][acCall][14] = ac_gtc;
	#if !defined _inc_y_hooks && !defined _INC_y_hooks\
		&& defined ac_OnVehicleRespray
		return ac_OnVehicleRespray(playerid, vehicleid, color1, color2);
	#else
		return 1;
	#endif
}

#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnVehicleRespray
		#undef OnVehicleRespray
	#else
		#define _ALS_OnVehicleRespray
	#endif
	#define OnVehicleRespray ac_OnVehicleRespray
	#if defined ac_OnVehicleRespray
		forward ac_OnVehicleRespray(playerid, vehicleid, color1, color2);
	#endif
#endif

#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnVehicleDeath(vehicleid, killerid)
#else
	public OnVehicleDeath(vehicleid, killerid)
#endif
{
	if(IsPlayerConnected(killerid) && !IsPlayerNPC(killerid))
	{
		new ac_gtc = GetTickCount();
		if(ACInfo[killerid][acACAllow])
		{
			if(ac_gtc < ACInfo[killerid][acCall][15] + ac_Mtfc[15][0]) ac_FloodDetect(killerid, 15);
			else if(ac_gtc < ACInfo[killerid][acCall][27] + ac_Mtfc[27][0]) ac_FloodDetect(killerid, 27);
			else ACInfo[killerid][acFloodCount][15] = ACInfo[killerid][acFloodCount][27] = 0;
		}
		ACInfo[killerid][acCall][27] = ACInfo[killerid][acCall][15] = ac_gtc;
	}
	#if !defined _inc_y_hooks && !defined _INC_y_hooks\
		&& defined ac_OnVehicleDeath
		return ac_OnVehicleDeath(vehicleid, killerid);
	#else
		return 1;
	#endif
}

#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnVehicleDeath
		#undef OnVehicleDeath
	#else
		#define _ALS_OnVehicleDeath
	#endif
	#define OnVehicleDeath ac_OnVehicleDeath
	#if defined ac_OnVehicleDeath
		forward ac_OnVehicleDeath(vehicleid, killerid);
	#endif
#endif

#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnPlayerText(playerid, text[])
#else
	public OnPlayerText(playerid, text[])
#endif
{
	if(!IsPlayerNPC(playerid))
	{
		new ac_gtc = GetTickCount();
		if(ACInfo[playerid][acACAllow])
		{
			if(ac_gtc < ACInfo[playerid][acCall][16] + ac_Mtfc[16][0]) return ac_FloodDetect(playerid, 16);
			if(ac_gtc < ACInfo[playerid][acCall][27] + ac_Mtfc[27][0]) ac_FloodDetect(playerid, 27);
			else ACInfo[playerid][acFloodCount][16] = ACInfo[playerid][acFloodCount][27] = 0;
		}
		ACInfo[playerid][acCall][27] = ACInfo[playerid][acCall][16] = ac_gtc;
	}
	#if !defined _inc_y_hooks && !defined _INC_y_hooks\
		&& defined ac_OnPlayerText
		return ac_OnPlayerText(playerid, text);
	#else
		return 1;
	#endif
}

#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnPlayerText
		#undef OnPlayerText
	#else
		#define _ALS_OnPlayerText
	#endif
	#define OnPlayerText ac_OnPlayerText
	#if defined ac_OnPlayerText
		forward ac_OnPlayerText(playerid, text[]);
	#endif
#endif

#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnPlayerEnterCheckpoint(playerid)
#else
	public OnPlayerEnterCheckpoint(playerid)
#endif
{
	if(!IsPlayerNPC(playerid))
	{
		new ac_gtc = GetTickCount();
		if(ACInfo[playerid][acACAllow])
		{
			if(ac_gtc < ACInfo[playerid][acCall][17] + ac_Mtfc[17][0]) ac_FloodDetect(playerid, 17);
			else if(ac_gtc < ACInfo[playerid][acCall][27] + ac_Mtfc[27][0]) ac_FloodDetect(playerid, 27);
			else ACInfo[playerid][acFloodCount][17] = ACInfo[playerid][acFloodCount][27] = 0;
		}
		ACInfo[playerid][acCall][27] = ACInfo[playerid][acCall][17] = ac_gtc;
	}
	#if !defined _inc_y_hooks && !defined _INC_y_hooks\
		&& defined ac_OnPlayerEnterCheckpoint
		return ac_OnPlayerEnterCheckpoint(playerid);
	#else
		return 1;
	#endif
}

#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnPlayerEnterCheckpoint
		#undef OnPlayerEnterCheckpoint
	#else
		#define _ALS_OnPlayerEnterCheckpoint
	#endif
	#define OnPlayerEnterCheckpoint ac_OnPlayerEnterCheckpoint
	#if defined ac_OnPlayerEnterCheckpoint
		forward ac_OnPlayerEnterCheckpoint(playerid);
	#endif
#endif

#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnPlayerLeaveCheckpoint(playerid)
#else
	public OnPlayerLeaveCheckpoint(playerid)
#endif
{
	if(!IsPlayerNPC(playerid))
	{
		new ac_gtc = GetTickCount();
		if(ACInfo[playerid][acACAllow])
		{
			if(ac_gtc < ACInfo[playerid][acCall][18] + ac_Mtfc[18][0]) ac_FloodDetect(playerid, 18);
			else if(ac_gtc < ACInfo[playerid][acCall][27] + ac_Mtfc[27][0]) ac_FloodDetect(playerid, 27);
			else ACInfo[playerid][acFloodCount][18] = ACInfo[playerid][acFloodCount][27] = 0;
		}
		ACInfo[playerid][acCall][27] = ACInfo[playerid][acCall][18] = ac_gtc;
	}
	#if !defined _inc_y_hooks && !defined _INC_y_hooks\
		&& defined ac_OnPlayerLeaveCheckpoint
		return ac_OnPlayerLeaveCheckpoint(playerid);
	#else
		return 1;
	#endif
}

#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnPlayerLeaveCheckpoint
		#undef OnPlayerLeaveCheckpoint
	#else
		#define _ALS_OnPlayerLeaveCheckpoint
	#endif
	#define OnPlayerLeaveCheckpoint ac_OnPlayerLeaveCheckpoint
	#if defined ac_OnPlayerLeaveCheckpoint
		forward ac_OnPlayerLeaveCheckpoint(playerid);
	#endif
#endif

#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnPlayerRequestSpawn(playerid)
#else
	public OnPlayerRequestSpawn(playerid)
#endif
{
	new ac_i;
	if(!IsPlayerNPC(playerid))
	{
		ac_i = GetTickCount();
		if(ACInfo[playerid][acACAllow])
		{
			if(ac_i < ACInfo[playerid][acCall][19] + ac_Mtfc[19][0]) return ac_FloodDetect(playerid, 19);
			if(ac_i < ACInfo[playerid][acCall][27] + ac_Mtfc[27][0]) ac_FloodDetect(playerid, 27);
			else ACInfo[playerid][acFloodCount][19] = ACInfo[playerid][acFloodCount][27] = 0;
		}
		ACInfo[playerid][acCall][27] = ACInfo[playerid][acCall][19] = ac_i;
	}
	ac_i = 1;
	#if !defined _inc_y_hooks && !defined _INC_y_hooks\
		&& defined ac_OnPlayerRequestSpawn
		ac_i = ac_OnPlayerRequestSpawn(playerid);
	#endif
	return ac_i;
}

#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnPlayerRequestSpawn
		#undef OnPlayerRequestSpawn
	#else
		#define _ALS_OnPlayerRequestSpawn
	#endif
	#define OnPlayerRequestSpawn ac_OnPlayerRequestSpawn
	#if defined ac_OnPlayerRequestSpawn
		forward ac_OnPlayerRequestSpawn(playerid);
	#endif
#endif

#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnPlayerExitedMenu(playerid)
#else
	public OnPlayerExitedMenu(playerid)
#endif
{
	if(!(0 <= playerid < MAX_PLAYERS)) return 0;
	new ac_gtc = GetTickCount();
	if(ACInfo[playerid][acACAllow])
	{
		if(ac_gtc < ACInfo[playerid][acCall][20] + ac_Mtfc[20][0]) ac_FloodDetect(playerid, 20);
		else if(ac_gtc < ACInfo[playerid][acCall][27] + ac_Mtfc[27][0]) ac_FloodDetect(playerid, 27);
		else ACInfo[playerid][acFloodCount][20] = ACInfo[playerid][acFloodCount][27] = 0;
	}
	ACInfo[playerid][acCall][27] = ACInfo[playerid][acCall][20] = ac_gtc;
	#if !defined _inc_y_hooks && !defined _INC_y_hooks\
		&& defined ac_OnPlayerExitedMenu
		return ac_OnPlayerExitedMenu(playerid);
	#else
		return 1;
	#endif
}
#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnPlayerExitedMenu
		#undef OnPlayerExitedMenu
	#else
		#define _ALS_OnPlayerExitedMenu
	#endif
	#define OnPlayerExitedMenu ac_OnPlayerExitedMenu
	#if defined ac_OnPlayerExitedMenu
		forward ac_OnPlayerExitedMenu(playerid);
	#endif
#endif

#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnPlayerExitedMenu
		#undef OnPlayerExitedMenu
	#else
		#define _ALS_OnPlayerExitedMenu
	#endif
	#define OnPlayerExitedMenu ac_OnPlayerExitedMenu
	#if defined ac_OnPlayerExitedMenu
		forward ac_OnPlayerExitedMenu(playerid);
	#endif
#endif

#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnPlayerEnterRaceCP(playerid)
#else
	public OnPlayerEnterRaceCheckpoint(playerid)
#endif
{
	if(!IsPlayerNPC(playerid))
	{
		new ac_gtc = GetTickCount();
		if(ACInfo[playerid][acACAllow])
		{
			if(ac_gtc < ACInfo[playerid][acCall][21] + ac_Mtfc[21][0]) ac_FloodDetect(playerid, 21);
			else if(ac_gtc < ACInfo[playerid][acCall][27] + ac_Mtfc[27][0]) ac_FloodDetect(playerid, 27);
			else ACInfo[playerid][acFloodCount][21] = ACInfo[playerid][acFloodCount][27] = 0;
		}
		ACInfo[playerid][acCall][27] = ACInfo[playerid][acCall][21] = ac_gtc;
	}
	#if !defined _inc_y_hooks && !defined _INC_y_hooks\
		&& defined ac_OnPlayerEnterRaceCheckpoint
		return ac_OnPlayerEnterRaceCheckpoint(playerid);
	#else
		return 1;
	#endif
}

#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnPlayerEnterRaceCheckpoin\
		|| defined _ALS_OnPlayerEnterRaceCP
		#undef OnPlayerEnterRaceCheckpoint
	#else
		#define _ALS_OnPlayerEnterRaceCP
	#endif
	#define OnPlayerEnterRaceCheckpoint ac_OnPlayerEnterRaceCheckpoint
	#if defined ac_OnPlayerEnterRaceCheckpoint
		forward ac_OnPlayerEnterRaceCheckpoint(playerid);
	#endif
#endif

#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnPlayerLeaveRaceCP(playerid)
#else
	public OnPlayerLeaveRaceCheckpoint(playerid)
#endif
{
	if(!IsPlayerNPC(playerid))
	{
		new ac_gtc = GetTickCount();
		if(ACInfo[playerid][acACAllow])
		{
			if(ac_gtc < ACInfo[playerid][acCall][22] + ac_Mtfc[22][0]) ac_FloodDetect(playerid, 22);
			else if(ac_gtc < ACInfo[playerid][acCall][27] + ac_Mtfc[27][0]) ac_FloodDetect(playerid, 27);
			else ACInfo[playerid][acFloodCount][22] = ACInfo[playerid][acFloodCount][27] = 0;
		}
		ACInfo[playerid][acCall][27] = ACInfo[playerid][acCall][22] = ac_gtc;
	}
	#if !defined _inc_y_hooks && !defined _INC_y_hooks\
		&& defined ac_OnPlayerLeaveRaceCheckpoint
		return ac_OnPlayerLeaveRaceCheckpoint(playerid);
	#else
		return 1;
	#endif
}

#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnPlayerLeaveRaceCheckpoin\
		|| defined _ALS_OnPlayerLeaveRaceCP
		#undef OnPlayerLeaveRaceCheckpoint
	#else
		#define _ALS_OnPlayerLeaveRaceCP
	#endif
	#define OnPlayerLeaveRaceCheckpoint ac_OnPlayerLeaveRaceCheckpoint
	#if defined ac_OnPlayerLeaveRaceCheckpoint
		forward ac_OnPlayerLeaveRaceCheckpoint(playerid);
	#endif
#endif

#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnPlayerClickPlayerTD(playerid, PlayerText:playertextid)
#else
	public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
#endif
{
	new ac_gtc = GetTickCount();
	if(ACInfo[playerid][acACAllow])
	{
		if(ac_gtc < ACInfo[playerid][acCall][23] + ac_Mtfc[23][0])
		{
			ac_FloodDetect(playerid, 23);
			return 1;
		}
		if(ac_gtc < ACInfo[playerid][acCall][27] + ac_Mtfc[27][0]) ac_FloodDetect(playerid, 27);
		else ACInfo[playerid][acFloodCount][23] = ACInfo[playerid][acFloodCount][27] = 0;
	}
	ACInfo[playerid][acCall][27] = ACInfo[playerid][acCall][23] = ac_gtc;
	#if !defined _inc_y_hooks && !defined _INC_y_hooks\
		&& defined ac_OnPlayerClickPlayerTextDraw
		return ac_OnPlayerClickPlayerTextDraw(playerid, playertextid);
	#else
		return 0;
	#endif
}

#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnPlayerClickPlayerTextDra\
		|| defined _ALS_OnPlayerClickPlayerTD
		#undef OnPlayerClickPlayerTextDraw
	#else
		#define _ALS_OnPlayerClickPlayerTD
	#endif
	#define OnPlayerClickPlayerTextDraw ac_OnPlayerClickPlayerTextDraw
	#if defined ac_OnPlayerClickPlayerTextDraw
		forward ac_OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid);
	#endif
#endif

#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnVehDamageStatusUpd(vehicleid, playerid)
#else
	public OnVehicleDamageStatusUpdate(vehicleid, playerid)
#endif
{
	new ac_gtc = GetTickCount();
	if(ACInfo[playerid][acACAllow])
	{
		if(ac_gtc < ACInfo[playerid][acCall][24] + ac_Mtfc[24][0]) ac_FloodDetect(playerid, 24);
		else if(ac_gtc < ACInfo[playerid][acCall][27] + ac_Mtfc[27][0]) ac_FloodDetect(playerid, 27);
		else ACInfo[playerid][acFloodCount][24] = ACInfo[playerid][acFloodCount][27] = 0;
	}
	ACInfo[playerid][acCall][27] = ACInfo[playerid][acCall][24] = ac_gtc;
	#if !defined _inc_y_hooks && !defined _INC_y_hooks\
		&& defined ac_OnVehicleDamageStatusUpdate
		return ac_OnVehicleDamageStatusUpdate(vehicleid, playerid);
	#else
		return ac_gtc;
	#endif
}

#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnVehicleDamageStatusUpdat\
		|| defined _ALS_OnVehicleDamageStatusUpd
		#undef OnVehicleDamageStatusUpdate
	#else
		#define _ALS_OnVehicleDamageStatusUpd
	#endif
	#define OnVehicleDamageStatusUpdate ac_OnVehicleDamageStatusUpdate
	#if defined ac_OnVehicleDamageStatusUpdate
		forward ac_OnVehicleDamageStatusUpdate(vehicleid, playerid);
	#endif
#endif

#if defined OnVehicleSirenStateChange
	#if defined _inc_y_hooks || defined _INC_y_hooks
		hook OnVehicleSirenChange(playerid, vehicleid, newstate)
	#else
		public OnVehicleSirenStateChange(playerid, vehicleid, newstate)
	#endif
	{
		if(!IsPlayerNPC(playerid))
		{
			new ac_gtc = GetTickCount();
			if(ACInfo[playerid][acACAllow])
			{
				if(ac_gtc < ACInfo[playerid][acCall][25] + ac_Mtfc[25][0]) ac_FloodDetect(playerid, 25);
				else if(ac_gtc < ACInfo[playerid][acCall][27] + ac_Mtfc[27][0]) ac_FloodDetect(playerid, 27);
				else ACInfo[playerid][acFloodCount][25] = ACInfo[playerid][acFloodCount][27] = 0;
			}
			ACInfo[playerid][acCall][27] = ACInfo[playerid][acCall][25] = ac_gtc;
		}
		#if !defined _inc_y_hooks && !defined _INC_y_hooks\
			&& defined ac_OnVehicleSirenStateChange
			return ac_OnVehicleSirenStateChange(playerid, vehicleid, newstate);
		#else
			return 0;
		#endif
	}

	#if !defined _inc_y_hooks && !defined _INC_y_hooks
		#if defined _ALS_OnVehicleSirenStateChange
			#undef OnVehicleSirenStateChange
		#else
			#define _ALS_OnVehicleSirenStateChange
		#endif
		#define OnVehicleSirenStateChange ac_OnVehicleSirenStateChange
		#if defined ac_OnVehicleSirenStateChange
			forward ac_OnVehicleSirenStateChange(playerid, vehicleid, newstate);
		#endif
	#endif
#endif

#if defined OnPlayerSelectDynamicObject
	#if defined _inc_y_hooks || defined _INC_y_hooks
		#if defined STREAMER_ENABLE_TAGS
			hook OnPlayerSelectDynObject(playerid, STREAMER_TAG_OBJECT:objectid, modelid, Float:x, Float:y, Float:z)
		#else
			hook OnPlayerSelectDynObject(playerid, objectid, modelid, Float:x, Float:y, Float:z)
		#endif
	#else
		#if defined STREAMER_ENABLE_TAGS
			public OnPlayerSelectDynamicObject(playerid, STREAMER_TAG_OBJECT:objectid, modelid, Float:x, Float:y, Float:z)
		#else
			public OnPlayerSelectDynamicObject(playerid, objectid, modelid, Float:x, Float:y, Float:z)
		#endif
	#endif
	{
		new ac_gtc = GetTickCount();
		if(ACInfo[playerid][acACAllow])
		{
			if(ac_gtc < ACInfo[playerid][acCall][26] + ac_Mtfc[26][0]) ac_FloodDetect(playerid, 26);
			else if(ac_gtc < ACInfo[playerid][acCall][27] + ac_Mtfc[27][0]) ac_FloodDetect(playerid, 27);
			else ACInfo[playerid][acFloodCount][26] = ACInfo[playerid][acFloodCount][27] = 0;
		}
		ACInfo[playerid][acCall][27] = ACInfo[playerid][acCall][26] = ac_gtc;
		#if !defined _inc_y_hooks && !defined _INC_y_hooks\
			&& defined ac_OnPlayerSelectDynamicObject
			return ac_OnPlayerSelectDynamicObject(playerid, objectid, modelid, x, y, z);
		#else
			return 1;
		#endif
	}

	#if !defined _inc_y_hooks && !defined _INC_y_hooks
		#if defined _ALS_OnPlayerSelectDynamicObjec\
			|| defined _ALS_OnPlayerSelectDynObject || defined _ALS_OnPlayerSelectDynamicObj
			#undef OnPlayerSelectDynamicObject
		#else
			#define _ALS_OnPlayerSelectDynObject
		#endif
		#define OnPlayerSelectDynamicObject ac_OnPlayerSelectDynamicObject
		#if defined ac_OnPlayerSelectDynamicObject
			#if defined STREAMER_ENABLE_TAGS
				forward ac_OnPlayerSelectDynamicObject(playerid, STREAMER_TAG_OBJECT:objectid, modelid, Float:x, Float:y, Float:z);
			#else
				forward ac_OnPlayerSelectDynamicObject(playerid, objectid, modelid, Float:x, Float:y, Float:z);
			#endif
		#endif
	#endif
#endif

#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnPlayerSelectObject(playerid, type, objectid, modelid, Float:fX, Float:fY, Float:fZ)
#else
	public OnPlayerSelectObject(playerid, type, objectid, modelid, Float:fX, Float:fY, Float:fZ)
#endif
{
	new ac_gtc = GetTickCount();
	if(ACInfo[playerid][acACAllow])
	{
		if(ac_gtc < ACInfo[playerid][acCall][26] + ac_Mtfc[26][0])
		{
			ac_FloodDetect(playerid, 26);
			return 1;
		}
		if(ac_gtc < ACInfo[playerid][acCall][27] + ac_Mtfc[27][0]) ac_FloodDetect(playerid, 27);
		else ACInfo[playerid][acFloodCount][26] = ACInfo[playerid][acFloodCount][27] = 0;
	}
	ACInfo[playerid][acCall][27] = ACInfo[playerid][acCall][26] = ac_gtc;
	#if !defined _inc_y_hooks && !defined _INC_y_hooks\
		&& defined ac_OnPlayerSelectObject
		return ac_OnPlayerSelectObject(playerid, type, objectid, modelid, fX, fY, fZ);
	#else
		return 0;
	#endif
}

#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnPlayerSelectObject
		#undef OnPlayerSelectObject
	#else
		#define _ALS_OnPlayerSelectObject
	#endif
	#define OnPlayerSelectObject ac_OnPlayerSelectObject
	#if defined ac_OnPlayerSelectObject
		forward ac_OnPlayerSelectObject(playerid, type, objectid, modelid, Float:fX, Float:fY, Float:fZ);
	#endif
#endif

static ac_FloodDetect(playerid, publicid)
{
	if(++ACInfo[playerid][acFloodCount][publicid] > ac_Mtfc[publicid][1])
	{
		printf("playerid: %d, %d, %d", playerid, ac_Mtfc[publicid][1], publicid);
        Kick(playerid);
    }
	ACInfo[playerid][acCall][publicid] = ACInfo[playerid][acCall][27] = GetTickCount();
	return 0;
}