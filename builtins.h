#ifndef BUILTINS_H
#define BUILTINS_H

#include <unistd.h>
#include <string.h>
#include <stdio.h>

int chad_cd(char** args);
int chad_help(char** args);
int chad_exit(char** args);
static int chad_num_builtins(void);
int builtin_execute(char** args);

static const char* builtin_string[] = {
	"cd",
	"help",
	"exit"
};

static const int (*builtin_func[])(char**) = {
	&chad_cd,
	&chad_help,
	&chad_exit
};



#endif
