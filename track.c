#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
	char name[4096];
	unsigned int status;
}ps;

int main(int argc, char *argv[]){
	printf("Loading");
	char str[4096];
	char cmd[16]; 
	int i;
	struct tm rtiv;
	struct tm *rtime = NULL;
	time_t system_time;
	ps *pl = NULL;
	unsigned long int pls = 0;
	printf(".");
	if(argc > 1) strcpy(str, argv[1]);
	FILE *fp = fopen(str, "ab+");
	if(fp == NULL)goto quit;
	setvbuf(fp, NULL, _IOLBF, 4096);
	rewind(fp);
	printf(".");
	while (EOF != fscanf(fp, "%i %i %i %i %i %i %i %i %i %s %s\n", &rtiv.tm_sec, &rtiv.tm_min, &rtiv.tm_hour, &rtiv.tm_mday, &rtiv.tm_mon, &rtiv.tm_year, &rtiv.tm_wday, &rtiv.tm_yday, &rtiv.tm_isdst, str, cmd)){
		for (i = 0; i < pls; i++){
			if (!strcmp(str, pl[i].name)){
				pl[i].status = !strcmp(cmd, "in") ? 1 : 0;
				goto next;
			}
		}
		pls++;
		pl = realloc(pl, pls*sizeof(ps));
		strcpy(pl[pls - 1].name, str);
		pl[pls - 1].status = !strcmp(cmd, "in") ? 1 : 0;
		next:
		continue;
	}
	printf(".\n");
	while(1){
		scanf("%4095s %15s", str, cmd);
		if(!strcmp(cmd, "quit"))goto quit;
		if(!strcmp(cmd, "in")){
			if (strcmp(str, "all")){
			for (i = 0; i < pls; i++){
				if (!strcmp(str, pl[i].name)){
						pl[i].status = 1;
						goto skip1;
				}
			}
			pls++;
			pl = realloc(pl, pls*sizeof(ps));
			strcpy(pl[pls - 1].name, str);
			pl[pls - 1].status = 1;
			skip1:
			time(&system_time);
			rtime = localtime(&system_time);
			fprintf(fp, "%i %i %i %i %i %i %i %i %i %s %s\n", rtime->tm_sec, rtime->tm_min, rtime->tm_hour, rtime->tm_mday, rtime->tm_mon, rtime->tm_year, rtime->tm_wday, rtime->tm_yday, rtime->tm_isdst, str, cmd);
			}
			else{
				for (i = 0; i < pls; i++){
					pl[i].status = 1;
					time(&system_time);
					rtime = localtime(&system_time);
					fprintf(fp, "%i %i %i %i %i %i %i %i %i %s %s\n", rtime->tm_sec, rtime->tm_min, rtime->tm_hour, rtime->tm_mday, rtime->tm_mon, rtime->tm_year, rtime->tm_wday, rtime->tm_yday, rtime->tm_isdst, pl[1].name, cmd);
				}
			}
		}
		else if(!strcmp(cmd, "out")){
			if (strcmp(str, "all")){
			for (i = 0; i < pls; i++){
				if (!strcmp(str, pl[i].name)){
					pl[i].status = 0;
					goto skip2;
				}
			}
			pls++;
			pl = realloc(pl, pls*sizeof(ps));
			strcpy(pl[pls - 1].name, str);
			pl[pls - 1].status = 0;
			skip2:
				time(&system_time);
				rtime = localtime(&system_time);
				fprintf(fp, "%i %i %i %i %i %i %i %i %i %s %s\n", rtime->tm_sec, rtime->tm_min, rtime->tm_hour, rtime->tm_mday, rtime->tm_mon, rtime->tm_year, rtime->tm_wday, rtime->tm_yday, rtime->tm_isdst, str, cmd);
			}
			else{
				for (i = 0; i < pls; i++){
					pl[i].status = 0;
					time(&system_time);
					rtime = localtime(&system_time);
					fprintf(fp, "%i %i %i %i %i %i %i %i %i %s %s\n", rtime->tm_sec, rtime->tm_min, rtime->tm_hour, rtime->tm_mday, rtime->tm_mon, rtime->tm_year, rtime->tm_wday, rtime->tm_yday, rtime->tm_isdst, pl[1].name, cmd);
				}
			}
		}
		else if(!strcmp(cmd, "log")){
			time(&system_time);
			printf("%s\n", ctime(&system_time));
			if (!strcmp(str, "all")){
				printf("type:");
				int ds, de, l;
				scanf("%i-%i %i", &de, &ds, &l);
				rewind(fp);
				if (l > 0){
					for (i = 0; i < pls; i++){
						printf("%s is %s\n", pl[i].name, pl[i].status ? "in" : "out");
					}
				}
				char name[4096];
				strcpy(name, str);
				if (l > 1){
					while (EOF != fscanf(fp, "%i %i %i %i %i %i %i %i %i %s %s\n", &rtiv.tm_sec, &rtiv.tm_min, &rtiv.tm_hour, &rtiv.tm_mday, &rtiv.tm_mon, &rtiv.tm_year, &rtiv.tm_wday, &rtiv.tm_yday, &rtiv.tm_isdst, str, cmd)){
						int d = (int)(difftime(time(NULL), mktime(&rtiv)) / 86400);
						if(d <= ds && d >= de){
							printf("%s %s got %s\n", asctime(&rtiv), str, cmd);
						}
					}
				}
			}
			else{
				printf("type:");
				int ds, de, l;
				scanf("%i-%i %i", &de, &ds, &l);
				rewind(fp);
				for (i = 0; i < pls; i++){
					if (!strcmp(str, pl[i].name) && l > 0){
						printf("%s is %s\n", str, pl[i].status ? "in" : "out");
					}
				}
				char name[4096];
				strcpy(name, str);
				while (EOF != fscanf(fp, "%i %i %i %i %i %i %i %i %i %s %s\n", &rtiv.tm_sec, &rtiv.tm_min, &rtiv.tm_hour, &rtiv.tm_mday, &rtiv.tm_mon, &rtiv.tm_year, &rtiv.tm_wday, &rtiv.tm_yday, &rtiv.tm_isdst, str, cmd)){
					for (i = 0; i < pls; i++){
						if (!strcmp(str, name) && l > 1){
							int d = (int)(difftime(time(NULL), mktime(&rtiv)) / 86400);
							if(d <= ds && d >= de){
								printf("%s %s got %s\n", asctime(&rtiv), name, cmd);
							}
						}
					}
				}
			}
		}
		else if(!strcmp(cmd, "logf")){
			printf("file:");
			char fln[4096];
			scanf("%4095s", fln);
			FILE *lfp = fopen( fln, "ab");
			time(&system_time);
			fprintf(lfp, "%s\n", ctime(&system_time));
			if (!strcmp(str, "all")){
				printf("type:");
				int ds, de, l;
				scanf("%i-%i %i", &de, &ds, &l);
				rewind(fp);
				if (l > 0){
					for (i = 0; i < pls; i++){
						fprintf(lfp, "%s is %s\n", pl[i].name, pl[i].status ? "in" : "out");
					}
				}
				char name[4096];
				strcpy(name, str);
				if (l > 1){
					while (EOF != fscanf(fp, "%i %i %i %i %i %i %i %i %i %s %s\n", &rtiv.tm_sec, &rtiv.tm_min, &rtiv.tm_hour, &rtiv.tm_mday, &rtiv.tm_mon, &rtiv.tm_year, &rtiv.tm_wday, &rtiv.tm_yday, &rtiv.tm_isdst, str, cmd)){
						int d = (int)(difftime(time(NULL), mktime(&rtiv)) / 86400);
						if(d <= ds && d >= de){
							fprintf(lfp, "%s %s got %s\n", asctime(&rtiv), str, cmd);
						}
					}
				}
			}
			else{
				printf("type:");
				int ds, de, l;
				scanf("%i-%i %i", &de, &ds, &l);
				rewind(fp);
				for (i = 0; i < pls; i++){
					if (!strcmp(str, pl[i].name) && l > 0){
						fprintf(lfp, "%s is %s\n", str, pl[i].status ? "in" : "out");
					}
				}
				char name[4096];
				strcpy(name, str);
				while (EOF != fscanf(fp, "%i %i %i %i %i %i %i %i %i %s %s\n", &rtiv.tm_sec, &rtiv.tm_min, &rtiv.tm_hour, &rtiv.tm_mday, &rtiv.tm_mon, &rtiv.tm_year, &rtiv.tm_wday, &rtiv.tm_yday, &rtiv.tm_isdst, str, cmd)){
					for (i = 0; i < pls; i++){
						if (!strcmp(str, name) && l > 1){
							int d = (int)(difftime(time(NULL), mktime(&rtiv)) / 86400);
							if(d <= ds && d >= de){
								fprintf(lfp, "%s %s got %s\n", asctime(&rtiv), name, cmd);
							}
						}
					}
				}
			}
		}
		else printf("\n");
	}
quit:
	fflush(fp);
	fclose(fp);
	exit(0);
}