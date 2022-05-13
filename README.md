# About nano-shell
Some Real-time OS doen't have shell function.
nano-shell is super simple shell for these environment.
You can add shell function to your program very easily.

# Function
- Parse user input into argc, argv[] style and call handler you registered
- You can use faverite command prompt
- easy to show help for commands

# How to implement
1) Implement your command handler
2) Call nanoShellRun() with handler

* "help" and "exit" are reserved for build-in command

# Sample

```c

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

int handler(int argc, char* argv[])
{
	static COMMAND_INFO commands[] = {
		{"say", "[text] [count]", "print text X times", sayHello},
		{NULL, NULL, NULL, NULL}	// end mark
	};

	return nanoShellDispatch(commands, argc, argv);
}

void main(void){
	puts("\n--- Nano Shell Sample ---\n");
	nanoShellRun("-> ", handler);
}
```

# How to use sample
```
-> say Hello 3
Hello
Hello
Hello
-> help
------ H E L P ------
 - print text X times:
      say [text] [count]
-> exit
```

