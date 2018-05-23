#ifndef _DAEMONIZE_H
#define _DAEMONIZE_H


#include "apue.h"
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <daemonize.h>

void daemonize(const char *cmd);


#endif
