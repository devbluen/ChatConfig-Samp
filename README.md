# 📄 Chat Config [SA:MP]
This is an include for general chat configuration within the server. You will be able to manage the chat for one or more players at the same time, all synchronized with its native functions.

# ♻️ How to install?
Place "#include configChat" **after all** your includes, it needs **to be the last one of all**.

# ⚙️ Natives
```pawn
native TogglePlayerChat(playerid, bool:status);
native ToggleServerChat(bool:status);
native IsPlayerToggleChat(playerid);
native IsServerToggleChat();
native ClearPlayerChat(playerid, lines);
native ClearServerChat(lines);
```
# ⚙️ Extras
```pawn
native SendServerMessage(color, const message[]);
native SendPlayerMessage(playerid, color, const message[]);
```
#
Enjoy :)
