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

#ifndef _NANO_SHELL_H_INCLUDED_
#define _NANO_SHELL_H_INCLUDED_

#define NANOSHELL_MAX_COMMAND_LEN	256
#define NANOSHELL_MAX_ARG			32

typedef enum {
	DISPATCH_RESULT_EXIT,
	DISPATCH_RESULT_KEEP_RUNNING
} DISPATCH_RESULT;

typedef enum {
	CMD_RESULT_DONE,
	CMD_RESULT_INVALID_PARAM,
	CMD_RESULT_DO_EXIT
} COMMAND_RESULT;

typedef struct {
	char* command;
	char* paramDescription;
	char* functionDescription;
	COMMAND_RESULT (*handler)(int argc, char* argv[]);
} COMMAND_INFO;

// command handler
// (if you want to exit shell loop, return 0)
typedef int (* SHELL_COMMAND)(int argc, char* argv[]);


void nanoShellRun(const char* prompt, SHELL_COMMAND handler);
DISPATCH_RESULT nanoShellDispatch(COMMAND_INFO* commands,  int argc, char* argv[]);

#endif