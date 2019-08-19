#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<readline/readline.h>
#include<readline/history.h>


int chk_exit(char *s){
	while(s){
		if(isalpha(*s)){
			if(strncmp(s,"exit",4) == 0)
				return 1;
			return 0;
		}
		s++;
	}
}

int main(){
	char *command;
	while(1){
		command = readline(">> ");
		if(chk_exit(command))
			return 0;
		system(command);	
		free(command);
	}
}

