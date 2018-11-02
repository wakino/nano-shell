# About nano-shell
Some Real-time OS doen't have shell function.  
nano-shell is super simple shell for these environment.  
You can add shell function to your program very easily.  

# Function
- Parse user input into argc, argv[] style and call handler you registered
- You can use faverite　command prompt

# How to use
1) Implement your command handler
2) Call nanoShellRun() with handler

# Sample

```c
// Your command handler
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
		return 0; // Exit shell loop
	}
	else{
		puts("Unknown command.");
	}
	return 1; // Keep shell loop running
}

void main(void){
	puts("\n--- Nano Shell Sample ---\n");
	nanoShellRun("-> ", handler);	
}
```
