#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>

#include "frontdown.h"
#include "scandir.h"
#include "fd_curl.h"
#include "communication.h"

void version(void){
	printf("\nFrontdown %s\n", FD_VERSION);
	#ifdef __GNUC__
		printf("Compiled: %s %s with gcc %d.%d.%d\n\n", __DATE__, __TIME__, __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
	#endif
}

void usage(void){
	printf("Usage: frontdown [OPTIONS] \n\n");
	printf("\t-c --conf          Configuration file\n");
	printf("\t-d --destination   Backup destination\n");
	printf("\t-e --exclude       File/Folder to exclude as POSIX Extended Regular Expressions\n");
	printf("\t-h --help          Print this help\n");
	printf("\t-H --hidden        Include files starting with .\n");
	printf("\t-l                 Source requires login\n");
	printf("\t-L                 Destination requires login\n");
	printf("\t-s --source        Backup source\n");
	
	printf("\n");
	printf("There are no bugs - just random features.\n");
	printf("Mail them to: <nosupport@nowhere.nix>\n\n");
	printf("(C) Copyright 2012 by Patrick Eigensatz & Florian Wernli\n\n");
}


void help(){
	version();
	usage();
}

int main(int argc, char **argv){
	// Initialize exclude lists
	config.excludes = calloc(1, sizeof(struct exclude_list));
	
	latest_exclude = config.excludes;
	
	// Parse command line options
	parse_options(argc, argv);
	
	// Display parsed options
	printf("================================ CONFIG ================================\n");
	printf("Configuration File:     %s\n", strlen(config.conf)==0?"None":config.conf);
	printf("Source:                 %s\n", config.source);
	printf("Destination:            %s\n", config.destination);
	printf("Threads:                %d\n", config.threads);
	printf("Include hidden Files:   %s\n", config.hidden==0?"no":"yes");
	printf("Last backup:            %s\n", config.last_backup==0?"Never before":ctime((time_t*)&config.last_backup));
	printf("========================================================================\n\n");
	
	
	// Get index.db
	char indexpath[16384];
	strcpy(indexpath, config.destination);
	strcat(indexpath, "index.db");
	
	if(config.destinationLogin||config.sourceLogin){
		printf("To provide maximal security we won't display any character entered!\n\n");
		if(config.sourceLogin){
			config.sourceUname=getpass("Source User: ");
			config.sourcePwd=getpass("Source Password: ");
			printf("\n\n");
		}
		if(config.destinationLogin){
			config.sourceUname=getpass("Destination User: ");
			config.sourcePwd=getpass("Destination Password: ");			
			printf("\n\n");
		}
	}
	
	get_indexfile(indexpath);
	
	fd_scandir(config.source, config.last_backup, config.excludes);
	
	return 0;
}
