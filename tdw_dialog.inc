/*
 * TDW Improved Dialogs
 *
 * Copyright (c) 2017 Double V
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgement in the product documentation would be
 * appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#if defined _TDW_DIALOG_INC_
	#endinput
#endif
#define _TDW_DIALOG_INC_

#if defined _INC_y_hooks
	#define TDW_DIALOG_SUPPORT_Y_HOOKS
#endif

#define u@$ 0]);
#define __:%0$ u@(u[_:%0 u@$

#define dialog%1(%2) __:a@g:f@g:g@g:$%1(%2)()

#define a@g a@m:a@o:a@n
#define a@m:%8$%0[%3,%4]%1(%2) a@g:r@%3:%8$%0[%4]%1(%2)
#define a@o:%8$%0[%3]%1(%2)        r@%3:%8$%0%1(%2)
#define a@n:%8$%0[]%1(%2)               %8$%0%1(%2)

#define r@%1\32; r@%1
#if defined TDW_DIALOG_SUPPORT_Y_HOOKS
	#define r@hook g@h  // support y_hooks
#else
	#define r@hook g@n
#endif
#define r@nohook g@n
#define r@template g@t

// #define f@g:%8$%0<%3>%1(%2)() g@v:%8$%0%1(%2)(%3)

#if defined TDW_DIALOG_SUPPORT_Y_HOOKS && defined TDW_DIALOG_DEFAULT_HOOK
	#define g@g g@h
#else
	#define g@g g@n
#endif
// #define g@v:%8$%1(%2)(%3) %8$public const d@%1=(%3);forward %1(%2);public %1(%2)
#if defined TDW_DIALOG_SKIP_ARGS
	#define g@n:%8$%1(%2)(%3) %8$\
 		forward D_%1(playerid,response,listitem,inputtext[]);\
 		public D_%1(playerid,response,listitem,inputtext[])\
 		{(_:ar@:(D@%1(%2)));}\
 		stock D@%1(%2)
	#define g@h:%8$%1(%2)(%3) %8$\
 		hook D_%1(playerid,response,listitem,inputtext[])\
 		{(_:ar@:(D@%1(%2)));}\
 		stock D@%1(%2)
 	#define ar@:(%1(%2[%4]%3)) ar@:(%1(%2%3))
#else
	#define g@n:%8$%1(%2)(%3) %8$forward D_%1(%2);public D_%1(%2)
	#define g@h:%8$%1(%2)(%3) %8$hook D_%1(%2)
#endif
#define g@t:%8$%1(%2)(%3) %8$forward T_%1(%2);public T_%1(%2)

#define d@%1\32; d@%1
#define D_%1\32; D_%1
#define D@%1\32; D@%1
#define T_%1\32; T_%1
#define @yH_D_%1\32; @yH_D_%1

// alternative syntax
#define Dialog:%1(%2) dialog %1(%2)
#define DialogResponse Dialog

#define dtempl dialog [template]
#define Dialog_Open OpenDialog
#define Dialog_Close CloseDialog
#define Dialog_Show ShowDialog
#define dfunc: #

#if !defined _INC_SAMP_Community_fixes && !defined FIX_const && !defined SAMP_CONST_CORRECT
	native TDW_DIALOG_ShowPlayerDialog(playerid, dialogid, style,
		const caption[], const info[], const button1[],
		const button2[]) = ShowPlayerDialog;

	#if defined _ALS_ShowPlayerDialog
		#undef ShowPlayerDialog
	#else
		#define _ALS_ShowPlayerDialog
	#endif
	#define ShowPlayerDialog TDW_DIALOG_ShowPlayerDialog
#endif


#if !defined TDW_DIALOG_ID
	#define TDW_DIALOG_ID (32767)
#endif

const
	TDW_DIALOG_MAX_FUNC_NAME = 32;

static stock
	TDW_gsDialogName[MAX_PLAYERS][TDW_DIALOG_MAX_FUNC_NAME char],
	bool:TDW_gsDialogOpened[MAX_PLAYERS char];

stock OpenDialog(playerid, const func[], style,	const caption[], const info[],
	const button1[], const button2[])
{
	TDW_gsDialogName[playerid] = !"D_";
	strcat(TDW_gsDialogName[playerid], func);

	TDW_gsDialogOpened{playerid} = true;

	return ShowPlayerDialog(playerid, TDW_DIALOG_ID, style, caption, info,
		button1, button2);
}

stock CloseDialog(playerid)
{
	static const
		space[] = !" ";

	TDW_gsDialogName[playerid]{0} = '\0';
	TDW_gsDialogOpened{playerid} = false;

	return ShowPlayerDialog(playerid, -1, DIALOG_STYLE_MSGBOX, space, space,
		space, space);
}

stock IsPlayerInDialog(playerid)
{
	return TDW_gsDialogOpened{playerid};
}

stock ShowDialog(playerid, const func[])
{
	new buffer[TDW_DIALOG_MAX_FUNC_NAME char] = !"T_";
	strcat(buffer, func);

	return CallLocalFunction(buffer, !"d", playerid);
}


#if defined TDW_DIALOG_SUPPORT_Y_HOOKS
hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
#else
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
#endif
{
	static ret;
	#pragma unused ret

	if (dialogid == TDW_DIALOG_ID) {
		if (_:TDW_gsDialogOpened{playerid} == 0)
			return 0;
		TDW_gsDialogOpened{playerid} = false;

		if (inputtext[0] == '\0') {
			return CallLocalFunction(TDW_gsDialogName[playerid], !"ddds",
				playerid, response, listitem, !"\1");
		} else {
			new len = strlen(inputtext);
			do {
				if (inputtext[len] == '%')
					inputtext[len] = '#';
				else if (len > len - 2) {
					if (
						inputtext[len] == '~' && 
						inputtext[len - 1] == 'k' && 
						inputtext[len - 2] == '~'
					) {
						inputtext[len] = '#';
						inputtext[len - 1] = '#';
						inputtext[len - 2] = '#';
					}
				}
			} while (--len != 0);

			return CallLocalFunction(TDW_gsDialogName[playerid], !"ddds",
				playerid, response, listitem, inputtext);
		}
	}

#if !defined TDW_DIALOG_SUPPORT_Y_HOOKS && defined TDW_DLG@OnDialogResponse
	TDW_DLG@OnDialogResponse(playerid, dialogid, response, listitem,
		inputtext);
	// this workaround is used to get the return value of
	// TDW_DLG@OnDialogResponse.
	#emit stor.pri ret
	return ret;
#else
	return 0;
#endif
}
#if !defined TDW_DIALOG_SUPPORT_Y_HOOKS
	#if defined _ALS_OnDialogResponse
		#undef OnDialogResponse
	#else
		#define _ALS_OnDialogResponse
	#endif
	#define OnDialogResponse TDW_DLG@OnDialogResponse
	#if defined TDW_DLG@OnDialogResponse
	forward TDW_DLG@OnDialogResponse(playerid, dialogid, response, listitem,
		inputtext[]);
	#endif
#endif
