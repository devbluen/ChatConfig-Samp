/*

			Definer:
				DEFAULT_CHAT_CONNECT_PLAYER  							// Default chat status after player connects (true or false) to activate or deactivate

			Stocks:
				native IsPlayerToggleChat(playerid);  							// Verify if the player has toggled chat
				native IsServerToggleChat(); 						 			// Verify if the server has toggled chat
				native ToggleServerChat(bool:status);  							// Activate or deactivate chat for everyone
				native TogglePlayerChat(playerid, bool:status);  				// Activate or deactivate chat for a player
				native SendServerMessage(color, const message[]);  				// Send a message to everyone regardless of their ToggleChat status
				native SendPlayerMessage(playerid, color, const message[]);  	// Send a message to a player regardless of their ToggleChat status
				native ClearPlayerChat(playerid, lines);  						// Clear the chat for a specific player (playerid) by a number of lines
				native ClearServerChat(lines);  								// Clear the chat for the server by a number of lines

*/

#if defined _inc_chatc
	#undef _inc_chatc
#endif
#if defined _chatc_included
	#endinput
#endif
#define _chatc_included


			// Definers
#define			DEFAULT_CHAT_CONNECT_PLAYER			(true)

			// Includes
#include <YSI_Coding\y_hooks>
#include <YSI_Data\y_iterate>

new Iterator:yChat<MAX_PLAYERS>, bool:yChatStatus = true;

hook OnGameModeInit() {
	Iter_Init(yChat);
	return true;
}

hook OnPlayerDisconnect(playerid, reason) {
	TogglePlayerChat(playerid, false);		// Don't never remove it :)
	return true;
}

hook OnPlayerConnect(playerid) {
	TogglePlayerChat(playerid, DEFAULT_CHAT_CONNECT_PLAYER);
	return true;
}



/*

					.oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
					d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
					Y88bo.           888      888      888 888           888  d8'    Y88bo.      
					`"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
						`"Y88b      888      888      888 888           888`88b.         `"Y88b 
					oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
					8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock bool:IsPlayerToggleChat(playerid)
	return (!Iter_Contains(yChat, playerid) ? (false) : (true));

stock bool:IsServerToggleChat()
	return yChatStatus;

stock bool:ToggleServerChat(bool:status) {

	if(yChatStatus == status)
		return true;

	yChatStatus = status;
	return true;
}

stock bool:TogglePlayerChat(playerid, bool:status) {

	if(!IsPlayerConnected(playerid)) return false;				// Verify connections

	switch(status)
	{
		case false: Iter_Remove(yChat, playerid);
		case true: Iter_Add(yChat, playerid);
	}
	return true;
}

stock SendServerMessage(color, const message[])
	return (SendClientMessageToAll(color, message));

stock SendPlayerMessage(playerid, color, const message[])
	return (SendClientMessage(playerid, color, message));

stock ySendClientMessage(playerid, color, const message[]) {

	if(playerid < 0 || playerid >= MAX_PLAYERS) return false; 	// Prevent Bugs
	if(!IsPlayerConnected(playerid)) return false;				// Verify connections
	if(!Iter_Contains(yChat, playerid)) return false;			// Allowed
	if(yChatStatus == false) return false;						// Allowed global

	return SendClientMessage(playerid, color, message);			// Message :)
}

stock ySendClientMessageToAll(color, const message[]) {

	if(yChatStatus == false)
		return false;

	foreach(new i: yChat) 
		SendClientMessage(i, color, message);
	
	return true;
}

stock ClearPlayerChat(playerid, lines = 30) {

	for(new i = 0; i < lines; i++)
		SendClientMessage(playerid, -1, " ");

	return true;
}

stock ClearServerChat(lines = 30) {

	for(new i = 0; i < lines; i++)
		SendClientMessageToAll(-1, " ");

	return true;
}



/*

					oooooooooo.   oooooooooooo oooooooooooo ooooo ooooo      ooo oooooooooooo ooooooooo.    .oooooo..o 
					`888'   `Y8b  `888'     `8 `888'     `8 `888' `888b.     `8' `888'     `8 `888   `Y88. d8P'    `Y8 
					888      888  888          888          888   8 `88b.    8   888          888   .d88' Y88bo.      
					888      888  888oooo8     888oooo8     888   8   `88b.  8   888oooo8     888ooo88P'   `"Y8888o.  
					888      888  888    "     888    "     888   8     `88b.8   888    "     888`88b.         `"Y88b 
					888     d88'  888       o  888          888   8       `888   888       o  888  `88b.  oo     .d8P 
					o888bood8P'   o888ooooood8 o888o        o888o o8o        `8  o888ooooood8 o888o  o888o 8""88888P'  

*/


#if defined _ALS_SendClientMessage
	#undef SendClientMessage
#else
	#define _ALS_SendClientMessage
#endif
#define SendClientMessage ySendClientMessage

#if defined _ALS_SendClientMessageToAll
	#undef SendClientMessageToAll
#else
	#define _ALS_SendClientMessageToAll
#endif
#define SendClientMessageToAll ySendClientMessageToAll
