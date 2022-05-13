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
#include <stdint.h>
#include <stdbool.h>

#include "nanoShell.h"

// Function prototype
int handler(int argc, char* argv[]);
bool match(const char* txt1, const char* txt2);
uint32_t parseNum(const char* numText);
void dumpBin(uint8_t* data, uint32_t dataLen);

// Implementation
void main(void){
	puts("\n--- Nano Shell Sample ---\n");
	nanoShellRun("-> ", handler);
}

COMMAND_RESULT sayHello(int argc, char* argv[]){
	if(argc >= 3){
		long i ;
		long count = parseNum(argv[2]);
		for(i = 0; i < count; i++){
			puts(argv[1]);
		}
		return CMD_RESULT_DONE;
	}
	else{
		return CMD_RESULT_INVALID_PARAM;
	}
}

COMMAND_RESULT bye(int argc, char* argv[]){
	puts("bye...");
	return CMD_RESULT_DO_EXIT;
}

int handler(int argc, char* argv[])
{
	static COMMAND_INFO commands[] = {
		{"say", "[text] [count]", "print text X times", sayHello},
		{"bye", "", "exit program", bye},
		{NULL, NULL, NULL, NULL}	// end of command mark
	};

	return nanoShellDispatch(commands, argc, argv);
}

bool match(const char* txt1, const char* txt2)
{
	return (strcmp(txt1, txt2) == 0);
}

uint32_t parseNum(const char* numText)
{
	if(numText == 0){
		return 0;
	}
	int radix = 10;
	if(strncmp(numText, "0x", 2) == 0){
		radix = 16;
	}
	return (uint32_t) strtoul(numText, 0, radix);
}

void dumpBin(uint8_t* data, uint32_t dataLen)
{
	uint32_t i;

	for(i = 0; i < dataLen; i++){

		if((i % 16) == 0){
			printf("\n[%04X] ", i);
		}
		else if((i % 4) == 0){
			printf("  ");
		}
		printf("%02X ", data[i]);
	}
	printf("\n");
}
