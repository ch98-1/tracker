//Copyright (C) 2015  Corwin Hansen
#include <stdio.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]){
	char str[4096];
	if(argc > 1) strcpy(str, argv[1]);
	FILE *fp = fopen(str, "ab+");
	if(fp == NULL)goto(quit);
	while(1){
		scanf("%4095s", str)
		if(!strcmp(str, "quit"))goto(quit);
		char *name = strtok(str, " ");
		char *cmd = strtok(str, NULL);
		if(!strcmp(cmd, "in")){
			if (!strcmp(name, "all")){

			}
		}
		else if(!strcmp(cmd, "out")){
			if (!strcmp(name, "all")){

			}
		}
		else if(!strcmp(cmd, "log")){
			if (!strcmp(name, "all")){

			}
		}
		else if(!strcmp(cmd, "logf")){
			if (!strcmp(name, "all")){

			}
		}
		else if(!strcmp(cmd, "note")){
			if (!strcmp(name, "all")){

			}
		}
		else if(!strcmp(cmd, "view")){
			if (!strcmp(name, "all")){

			}
		}
		else printf("\n");
	}
quit:
	fclose(fp);
}

