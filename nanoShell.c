//
//  nanoShell.c
//  Super Simple Shell Module
//
//  Copyright © 2018 Takatsura Miyawaki All rights reserved.
//

/** WTFPL
DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
Version 2, December 2004
Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>
Everyone is permitted to copy and distribute verbatim or modified
copies of this license document, and changing it is allowed as long
as the name is changed.
DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
0. You just DO WHAT THE FUCK YOU WANT TO.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nanoShell.h"

#define TRUE			1
#define FALSE			0

// prototype
static int parseCommand(char* buf, char* argv[]);


//	Run shell loop
void nanoShellRun(const char* prompt, SHELL_COMMAND handler)
{
	int index = 0;
	char buf[MAX_COMMAND_LEN];
	int tooLong = FALSE;

	printf("%s", prompt);

	for(;;){
		int c = getchar();
		if(c != '\r'){
			if(c == '\n'){
				int argc = 0;
				char* argv[MAX_ARG];
				memset(argv, 0, sizeof(argv));
				buf[index] = '\0';
				index = 0;
				argc = parseCommand(buf, argv);
				if(argc > 0){
					if(handler(argc, argv) == 0){
						break;
					}
				}
				printf("%s", prompt);
			}
			else if(index >= (MAX_COMMAND_LEN-1)){
				if(tooLong == FALSE){
					puts("too long command.\n");
					tooLong = TRUE;
				}
			}
			else{
				buf[index] = (char) c;
				index++;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
// private function


static int parseCommand(char* buf, char* argv[])
{
	int index = 0;
	int len = strlen(buf);

	if(len > 0){
		int i = 0;
		int hasData = FALSE;

		for(i = 0; i < len; i++){
			if(buf[i] == ' '){
				buf[i] = '\0';
				hasData = FALSE;
			}
			else if(!hasData){
				argv[index] = &buf[i];
				index++;
				hasData = TRUE;
			}
		}
	}
	return index;
}