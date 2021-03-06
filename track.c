#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


typedef struct{//ID
	char id[4096];
}ID;

typedef struct{//strust of peoples and their ID
	char name[4096];
	unsigned int status;
	long int size;
	ID *idlist;
}ps;

typedef struct{//list of people and ID
	ps *pl;//list of peoples and their status
	long int size;
}pls;

void badfile(const char *filename);//print out bad file warning and quit
void start_usage(const char *cmd);//print out usage
pls loadID(pls list, char *fn);//load people list
void saveID(pls list, char *fn);//save people list
void freeID(pls list);//free people list
unsigned int getstat(pls list, const char *ID);//get status of that ID
unsigned int setstat(pls list, const char *ID, unsigned int stat);//set status of that ID
void quit(void);//quit

pls pl;//list of peoples and their status

char *IDlistfile;//id list file name

FILE *logfile, *logout;//log history file, ID file, and log output file

int main(int argc, char *argv[]){
	printf("Loading");//Start Loading
	if (argc != 3){
		printf("Wrong number of argument\n");
		start_usage(argv[0]);
	}
	logfile = fopen(argv[1], "ab+");//open logfile
	if(logfile == NULL) badfile(argv[1]);//checkfile
	pl = loadID(pl, argv[2]);//load ID's
	strcpy(IDlistfile, argv[2]);//copy file name

}

void start_usage(const char *cmd){
	printf("%s logfile.txt IDdata.txt", cmd);
	exit(EXIT_FAILURE);
}

void badfile(const char *filename){//print out bad file warning and quit
	printf("file %s could not be opend or created", filename);
	exit(EXIT_FAILURE);
}

pls loadID(pls list, char *fn){//load people list
	FILE *fp = fopen(fn, "ab+");//open id file
	if(fp == NULL) badfile(fn);
	rewind(fp);//get it to start of file
	char *IDlist = NULL;
	list.size = 0;
	free(list.pl);//free anything left
	list.pl = NULL;
	while ( (IDlist = fgets(IDlist, 16384, fp)) != NULL){
		list.size++;
		list.pl = realloc(list.pl, list.size*sizeof(pl));//reallocate memory for pl
		char *idstr = NULL;
		free(list.pl[list.size - 1].idlist);//free this
		list.pl[list.size - 1].idlist = NULL;
		strcpy(list.pl[list.size - 1].name, strtok(IDlist, " ,:;"));//get the name
		list.pl[list.size - 1].status = atoi(strtok(NULL, " ,:;"));//get the status
		list.pl[list.size - 1].size = 0;
		while((idstr = strtok(NULL, " ,.:;")) != NULL ){//get ID's as list
			list.pl[list.size - 1].size++;
			list.pl[list.size - 1].idlist = realloc(list.pl[list.size - 1].idlist, list.pl[list.size - 1].size*sizeof(ID));//add more memory to ID list
			strcpy(list.pl[list.size - 1].idlist[list.pl[list.size - 1].size - 1].id, idstr);//copy ID
		}
	}
	fflush(fp);
	fclose(fp);
	return list;
}

void saveID(pls list, char *fn){//save people list
	FILE *fp = fopen(fn, "wb+");//open id file for writing
	if(fp == NULL) badfile(fn);
	rewind(fp);//get it to start of file
	unsigned long int i, j;
	for(i = 0; i < list.size; i++){
		fprintf(fp, "%s, %i, ", list.pl[i].name, list.pl[i].status);
		for(j = 0; j < list.pl[i].size; j++){
			fputs(list.pl[i].idlist[j].id, fp);//add ID
			fputs(", ", fp);//add seperator
		}
	}
	fflush(fp);
	fclose(fp);
}

void freeID(pls list){//free people list
	unsigned long int i;
	for(i = 0; i < list.size; i++){
		free(list.pl[i].idlist);//free idlist
	}
	free(list.pl);
}

void quit(void){
	saveID(pl, IDlistfile);//save ID list
	freeID(pl);//free ID list
}



//old code
/*
typedef struct{
	char name[4096];
	unsigned int status;
}ps;

int main(int argc, char *argv[]){
	printf("Loading");
	char str[4096];
	char cmd[16]; 
	char timestr[64];
	unsigned int i;
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
					fprintf(fp, "%i %i %i %i %i %i %i %i %i %s %s\n", rtime->tm_sec, rtime->tm_min, rtime->tm_hour, rtime->tm_mday, rtime->tm_mon, rtime->tm_year, rtime->tm_wday, rtime->tm_yday, rtime->tm_isdst, pl[i].name, cmd);
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
					fprintf(fp, "%i %i %i %i %i %i %i %i %i %s %s\n", rtime->tm_sec, rtime->tm_min, rtime->tm_hour, rtime->tm_mday, rtime->tm_mon, rtime->tm_year, rtime->tm_wday, rtime->tm_yday, rtime->tm_isdst, pl[i].name, cmd);
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
				char name[4096];
				strcpy(name, str);
				if (l > 1){
					while (EOF != fscanf(fp, "%i %i %i %i %i %i %i %i %i %s %s\n", &rtiv.tm_sec, &rtiv.tm_min, &rtiv.tm_hour, &rtiv.tm_mday, &rtiv.tm_mon, &rtiv.tm_year, &rtiv.tm_wday, &rtiv.tm_yday, &rtiv.tm_isdst, str, cmd)){
						int d = (int)(difftime(time(NULL), mktime(&rtiv)) / 86400);
						if(d <= ds && d >= de){
							strftime(timestr, 63, "%c", &rtiv);
							printf("%s %s got %s\n", timestr, str, cmd);
						}
					}
				}
				if (l > 0){
					for (i = 0; i < pls; i++){
						printf("%s is %s\n", pl[i].name, pl[i].status ? "in" : "out");
					}
				}
			}
			else{
				printf("type:");
				int ds, de, l;
				scanf("%i-%i %i", &de, &ds, &l);
				rewind(fp);
				char name[4096];
				strcpy(name, str);
				if (l > 1){
					while (EOF != fscanf(fp, "%i %i %i %i %i %i %i %i %i %s %s\n", &rtiv.tm_sec, &rtiv.tm_min, &rtiv.tm_hour, &rtiv.tm_mday, &rtiv.tm_mon, &rtiv.tm_year, &rtiv.tm_wday, &rtiv.tm_yday, &rtiv.tm_isdst, str, cmd)){
						if (!strcmp(str, name)){
							int d = (int)(difftime(time(NULL), mktime(&rtiv)) / 86400);
							if (d <= ds && d >= de){
								strftime(timestr, 63, "%c", &rtiv);
								printf("%s %s got %s\n", timestr, str, cmd);
							}
						}
					}
				}
				if (l > 0){
					for (i = 0; i < pls; i++){
						if (!strcmp(pl[i].name, name)){
							printf("%s is %s\n", pl[i].name, pl[i].status ? "in" : "out");
						}
					}
				}
			}
		}
		else if (!strcmp(cmd, "logf")){
			printf("file:");
			char fln[4096];
			scanf("%4095s", fln);
			FILE *lfp = fopen(fln, "ab");
			time(&system_time);
			fprintf(lfp, "%s\n", ctime(&system_time));
			if (!strcmp(str, "all")){
				printf("type:");
				int ds, de, l;
				scanf("%i-%i %i", &de, &ds, &l);
				rewind(fp);
				char name[4096];
				strcpy(name, str);
				if (l > 1){
					while (EOF != fscanf(fp, "%i %i %i %i %i %i %i %i %i %s %s\n", &rtiv.tm_sec, &rtiv.tm_min, &rtiv.tm_hour, &rtiv.tm_mday, &rtiv.tm_mon, &rtiv.tm_year, &rtiv.tm_wday, &rtiv.tm_yday, &rtiv.tm_isdst, str, cmd)){
						int d = (int)(difftime(time(NULL), mktime(&rtiv)) / 86400);
						if (d <= ds && d >= de){
							strftime(timestr, 63, "%c", &rtiv);
							fprintf(lfp, "%s,%s,%s\n", timestr, str, cmd);
						}
					}
				}
				if (l > 0){
					for (i = 0; i < pls; i++){
						fprintf(lfp, "%s,%s\n", pl[i].name, pl[i].status ? "in" : "out");
					}
				}
			}
			else{
				printf("type:");
				int ds, de, l;
				scanf("%i-%i %i", &de, &ds, &l);
				rewind(fp);
				char name[4096];
				strcpy(name, str);
				if (l > 1){
					while (EOF != fscanf(fp, "%i %i %i %i %i %i %i %i %i %s %s\n", &rtiv.tm_sec, &rtiv.tm_min, &rtiv.tm_hour, &rtiv.tm_mday, &rtiv.tm_mon, &rtiv.tm_year, &rtiv.tm_wday, &rtiv.tm_yday, &rtiv.tm_isdst, str, cmd)){
						if (!strcmp(str, name)){
							int d = (int)(difftime(time(NULL), mktime(&rtiv)) / 86400);
							if (d <= ds && d >= de){
								strftime(timestr, 63, "%c", &rtiv);
								fprintf(lfp, "%s,%s,%s\n", timestr, str, cmd);
							}
						}
					}
				}
				if (l > 0){
					for (i = 0; i < pls; i++){
						if (!strcmp(name, pl[i].name)){
							fprintf(lfp, "%s,%s\n", str, pl[i].status ? "in" : "out");
						}
					}
				}
			}
			fclose(lfp);
		}
		else printf("\n");
	}
quit:
	fflush(fp);
	fclose(fp);
	exit(0);
}
*/