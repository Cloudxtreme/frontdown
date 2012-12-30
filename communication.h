#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#include "frontdown.h"

#ifndef __COMMUNICATION_H__
#define __COMMUNICATION_H__

extern int close_destination();
extern int open_destination(char *target);
extern int get_indexfile(char *source);
extern int put_file(char *source, char *filename, char *target, curl_off_t size);

#endif
