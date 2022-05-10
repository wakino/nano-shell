//
//  nanoShell.c
//  Super Simple Shell Module
//
//  Copyright © 2018 Takatsura Miyawaki All rights reserved.
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