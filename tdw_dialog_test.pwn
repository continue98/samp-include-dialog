#include <a_samp>
#include <dialog\tdw_dialog>

dialog register(playerid, response, listitem, inputtext[])
{
	if (!response)
		return;
	SendClientMessage(playerid, -1, "Registered");
}

public OnPlayerConnect(playerid)
{
	OpenDialog(playerid, "register", DIALOG_STYLE_MSGBOX,
		"Register",
		"Hello!",
		"Register", "Cancel"
	);

	return 1;
}
