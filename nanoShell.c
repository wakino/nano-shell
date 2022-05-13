//
//  nanoShell.c
//  Super Simple Shell Module
//
//  Copyright © 2018-2022 Takatsura Miyawaki All rights reserved.
//

/** MIT License

Copyright (c) 2022 Takatsura Miyawaki

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "nanoShell.h"

static int parseCommand(char* buf, char* argv[]);

void nanoShellRun(const char* prompt, SHELL_COMMAND handler)
{
	int index = 0;
	char buf[NANOSHELL_MAX_COMMAND_LEN];
	bool tooLong = false;

	printf("%s", prompt);

	for(;;){
		int c = getchar();
		if(c != '\r'){
			if(c == '\n'){
				int argc = 0;
				char* argv[NANOSHELL_MAX_ARG];
				memset(argv, 0, sizeof(argv));
				buf[index] = '\0';
				index = 0;
				argc = parseCommand(buf, argv);
				if(argc > 0){
					if(handler(argc, argv) == DISPATCH_RESULT_EXIT){
						break;
					}
				}
				printf("%s", prompt);
			}
			else if(index >= (NANOSHELL_MAX_COMMAND_LEN-1)){
				if(tooLong == false){
					puts("*** too long command.\n");
					tooLong = true;
				}
			}
			else{
				buf[index] = (char) c;
				index++;
			}
		}
	}
}

DISPATCH_RESULT nanoShellDispatch(COMMAND_INFO* commands,  int argc, char* argv[]){
	bool handled = false;
	COMMAND_RESULT result;
	int i;
	for(i = 0; commands[i].command != NULL ;i++){
		if(strcmp(commands[i].command, argv[0]) == 0){
			result = commands[i].handler(argc, argv);
			handled = true;
			break;
		}
	}

	if(!handled){
		if(strcmp("help", argv[0]) == 0){
			printf("------ H E L P ------\n");
			for(int j = 0; commands[j].command != NULL ;j++){
				printf(" - %s:\n", commands[j].functionDescription);
				printf("      %s %s\n", commands[j].command, commands[j].paramDescription);
			}
			handled = true;
		}
		else if(strcmp("exit", argv[0]) == 0){
			result = CMD_RESULT_DO_EXIT;
			handled = true;
		}
	}

	if(handled){
		if(result == CMD_RESULT_INVALID_PARAM){
			printf("*** invalid parameter:\n");
			printf("    %s %s\n", commands[i].command, commands[i].paramDescription);
		}
		else if(result == CMD_RESULT_DO_EXIT){
			return DISPATCH_RESULT_EXIT;
		}
	}
	else{
		printf("*** invalid command:%s\n", argv[0]);
	}
	return DISPATCH_RESULT_KEEP_RUNNING;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// private function

static int parseCommand(char* buf, char* argv[])
{
	int index = 0;
	int len = strlen(buf);

	if(len > 0){
		int i = 0;
		bool hasData = false;

		for(i = 0; i < len; i++){
			if(buf[i] == ' '){
				buf[i] = '\0';
				hasData = false;
			}
			else if(!hasData){
				argv[index] = &buf[i];
				index++;
				hasData = true;
			}
		}
	}
	return index;
}