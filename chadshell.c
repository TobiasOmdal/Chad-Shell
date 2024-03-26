#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "builtins.h"

#define TOK_BUFFERSIZE 64
#define TOK_DELIMITERS " \n\t\r\a"
#define BUFFERSIZE 512

static char* read_shell(void) {
	int buffersize = BUFFERSIZE; 
	int position = 0; 
	char* buffer = malloc(sizeof(char) * buffersize);
	int c; 


	if (!buffer) {
		fprintf(stderr, "Could not allocate input buffer\n"); 
		exit(EXIT_FAILURE);
	}

	while(1) {
		c = getchar(); 

		if (c == EOF || c == '\n') {
			buffer[position] = '\0';
			return buffer;
		} else {
			buffer[position] = c;
		}

		position++;

		if (position >= buffersize) {
			buffersize += BUFFERSIZE;
			buffer = realloc(buffer, buffersize);

			if (!buffer) {
				fprintf(stderr, "Could not reallocate buffer\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

static char** parse_line(char* line) {
	int buffersize = TOK_BUFFERSIZE;
	int position = 0; 
	char** tokens = malloc(buffersize * sizeof(char));
	char* token;

	if (!tokens) {
		fprintf(stderr,"Could not allocate tokens\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, TOK_DELIMITERS); 
	while (token != NULL) {
		tokens[position++] = token;

		if (position >= buffersize) {
			buffersize += TOK_BUFFERSIZE;
			tokens = realloc(tokens, buffersize * sizeof(char*));
			if (!tokens) {
				fprintf(stderr, "Could not allocate token\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, TOK_DELIMITERS);
	}
	tokens[position] = NULL;
	return tokens;

}

static int exec_cmd(char** args) {
	pid_t pid; 
	pid_t wpid;
	int status;

	int builtin_status = builtin_execute(args);
	if (builtin_status != -1) {
		if (builtin_status == 0) {
			return 0;
		}
		return 1;
	}
	pid = fork();
	if (pid == 0) {
		if (execvp(args[0], args) == -1) {
			perror("shell");
		}
		exit(EXIT_FAILURE);
	} else if (pid < 0) {
		perror("shell");
	} else {
		do {
			wpid = waitpid(pid, &status, WUNTRACED); 
		} while(!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return 1;
}

static void shell_loop(void) {
	char* line; 
	char** args; 
	int status;

	do {
		printf("> ");
		
		line = read_shell(); 
		args = parse_line(line);
		status = exec_cmd(args);

		free(line);
		free(args);	
	} while(status);	
}


int main(int argc, char** argv) {

	shell_loop(); 

	return EXIT_SUCCESS; 
}
