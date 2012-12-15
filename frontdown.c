#include <stdio.h>
#include <stdlib.h>

#include "frontdown.h"

void version(){
	printf("\nFrontdown %s\n", FD_VERSION);
	#ifdef __GNUC__
		printf("Compiled: %s %s with gcc %d.%d.%d\n\n", __DATE__, __TIME__, __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
	#endif	
}

void usage(char *prog){
	printf("Usage: %s [OPTIONS]\n\n", prog);
}

void args(){
	printf("\t-h\t--help\tprints this help\n");
	printf("\n");
}

void support(){
	printf("There are no bugs - just random features.\n");
	printf("Mail them to: <nosupport@nowhere.nix>\n\n");
	printf("(C) Copyright 2012 by Patrick Eigensatz\n\n");
}

void help(int argc, char** argv){
	version();
	usage(argv[0]);
	args();
	support();
}

int main(int argc, char **argv){
	
	help(argc, argv);
	
	return 0;
}
