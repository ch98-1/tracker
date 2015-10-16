//Copyright (C) 2015  Corwin Hansen
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
	name[4096];
	unsigned int status;
}ps;

int main(int argc, char *argv[]){
	printf("Loading");
	char str[4096];
	char cmd[16];
	ps *pl;
	unsigned long int pls = 0;
	printf(".");
	if(argc > 1) strcpy(str, argv[1]);
	FILE *fp = fopen(str, "ab+");
	if(fp == NULL)goto(quit);
	rewind(fp);
	printf(".");
	while (EOF != fscanf(fp, "%4095s %4095s %15s", str, str, cmd)){
		int i;
		for (i = 0; i < pls; i++){
			if (!strcmp(str, pl[i].name)){
				if (!strcmp(cmd, "in") || !strcmp(cmd, "out")){
					pl[i].status = !strcmp(cmd, "in") ? 1 : 0;
				}
				goto(next);
			}
		}
		pls++;
		pl = realloc(pl, pls*sizeof(ps));
		strcpy(pl[pls - 1].name, name);
		if (!strcmp(cmd, "in") || !strcmp(cmd, "out")){
			pl[i].status = !strcmp(cmd, "in") ? 1 : 0;
		}
next:
	}
	printf(".\n");
	while(1){
		scanf("%4095s %15s", str, cmd);
		if(!strcmp(str, "quit"))goto(quit);
		if(!strcmp(cmd, "in")){
			for (i = 0; i < pls; i++){
				if (!strcmp(str, pl[i].name)){
						pl[i].status = 1;
						break;
				}
			}
			if (!strcmp(str, "all")){
				for (i = 0; i < pls; i++){
						pl[i].status = 1;
				}
			}
		}
		else if(!strcmp(cmd, "out")){
			for (i = 0; i < pls; i++){
				if (!strcmp(str, pl[i].name)){
					pl[i].status = 0;
					break;
				}
			}
			if (!strcmp(str, "all")){
				for (i = 0; i < pls; i++){
						pl[i].status = 0;
				}
			}
		}
		else if(!strcmp(cmd, "log")){
			if (!strcmp(str, "all")){

			}
		}
		else if(!strcmp(cmd, "logf")){
			if (!strcmp(str, "all")){

			}
		}
		else if(!strcmp(cmd, "note")){
			if (!strcmp(str, "all")){

			}
		}
		else if(!strcmp(cmd, "view")){
			if (!strcmp(str, "all")){

			}
		}
		else printf("\n");
	}
quit:
	fclose(fp);
}