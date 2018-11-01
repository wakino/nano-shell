#ifndef _NANO_SHELL_H_INCLUDED_
#define _NANO_SHELL_H_INCLUDED_

#define MAX_COMMAND_LEN	256
#define MAX_ARG			32

// command handler
// (if you want to exit shell loop, return 0)
typedef int (* SHELL_COMMAND)(int argc, char* argv[]);

void nanoShellRun(const char* prompt, SHELL_COMMAND handler);

#endif