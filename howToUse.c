#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nanoShell.h"

int handler(int argc, char* argv[])
{
	char* cmd = argv[0];
	if(strcmp(cmd, "say") == 0){
		if(argc >= 3){
			long i ;
			long count = strtol(argv[2], 0, 10);
			for(i = 0; i < count; i++){
				puts(argv[1]);
			}
		}
		else{
			puts("say [text] [count]\n");
		}
	}
	else if(strcmp(cmd, "help") == 0){
		puts("say [text] [count]");
		puts("exit");
	}
	else if(strcmp(cmd, "exit") == 0){
		return NANOSHELL_EXIT;
	}
	else{
		puts("Unknown command.");
	}
	return NANOSHELL_KEEP_RUNNING;
}

void main(void){
	puts("\n--- Nano Shell Sample ---\n");
	nanoShellRun("-> ", handler);
}

