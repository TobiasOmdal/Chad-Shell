#include "builtins.h"



static int chad_num_builtins(void) {
	return sizeof(builtin_string) / sizeof(char*);
}

int chad_cd(char** args) {
	if (args[1] == NULL) {
		fprintf(stderr, "Could not change directory using \"cd\"");
	} else if (chdir(args[1]) != 0) {
		perror("chad");
	}
	return 1;
}

int chad_help(char** args) {
	printf("Tobias Omdal's Chad Shell\n");
	printf("Supports rudimentary UNIX shell commands\n");
	printf("To use, type program names followed by white space seperated arguments");
	printf("Apart from normal commands, the following builtins are also available: \n");

	for (size_t i = 0; i < chad_num_builtins(); ++i) {
		printf("  %s\n", builtin_string[i]);
	}

	printf("The [man] command will provide information on other programs\n");
	return 1;
}

int chad_exit(char** exit) {
	return 0;
}

int builtin_execute(char** args) {
	if (args[0] == NULL) {
		return -1;
	}

	for (size_t i = 0; i < chad_num_builtins(); ++i) {
		if (strcmp(args[0], builtin_string[i]) == 0) {
			return (*builtin_func[i])(args);
		}	
	}
	return -1;
}
