#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<readline/readline.h>
#include<readline/history.h>
#include"syscalltable.h"

char **system_call_completion(const char*,int,int);
char *system_call_generation(const char*,int);

extern const char *syscalltable[];


int chk_exit(char *s){
	while(s){
		if(isalpha(*s)){
			if(strncmp(s,"exit",4) == 0){
				write_history(".sysh_history");
				return 1;
			}
			return 0;
		}
		s++;
	}
}

char **system_call_completion(const char *text,int start,int end){
	rl_attempted_completion_over = 1;
	return rl_completion_matches(text,system_call_generation);
}

char *system_call_generation(const char *text,int state){
	static int list_index,len;
	const char *name;
	if(!state){
		list_index = 0;
		len = strlen(text);
	}
	while((name = syscalltable[list_index++])){
		if(strncmp(name,text,len) == 0){
			return strdup(name);
		}
	}
	return NULL;
}
void init(){
	using_history();
	read_history(".sysh_history");
	rl_attempted_completion_function = system_call_completion;
}
int main(){
	char *command;
	init();
	while(1){
		command = readline(">> ");
		if(chk_exit(command))
			return 0;
		add_history(command);
		system(command);	
		free(command);
	}
}

