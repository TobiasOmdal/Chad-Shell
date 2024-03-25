#include <stdio.h>
#include <stdlib.h>

static char* read_shell(void) {
	return "";
}

static char** parse_line(char* line) {
	return (char**)0;
}

static int exec_cmd(char** args) {
	return 0;
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

		//free(line);
		//free(args);	
	} while(status);	
}


int main(int argc, char** argv) {

	shell_loop(); 

	return EXIT_SUCCESS; 
}
