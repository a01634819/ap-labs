#include <stdio.h>
#include "logger.h"
#include <time.h>
#include <syslog.h>
#include <stdarg.h>
#include <string.h>

int log=0;

int initLogger(char *logType) {
    printf("Logger starting  %s\n", logType);

    if (strcmp(logType,"stdout") == 0){
        log = 0;
    } else if (strcmp(logType,"syslog") == 0){
            log = 1;
    }else{       
        printf("Error");
        return -1;
    }   
    return 0;
}

int infof ( const char * format, ... ){
    va_list args;
    va_start (args, format);

    if(log == 1){
        openlog("Logger", LOG_PID | LOG_CONS, LOG_SYSLOG);
        vsyslog(LOG_EMERG,format, args);
        closelog();
    } else {
        vprintf (format, args);
    }
    va_end (args);
    return 1;
}

int warnf ( const char * format, ... ){
    va_list args;
    va_start (args, format);

    if(log == 1){
        openlog("Logger", LOG_PID | LOG_CONS, LOG_SYSLOG);
        vsyslog(LOG_EMERG,format, args);
        closelog();
    } else {
        vprintf (format, args);
    }
    va_end (args);
    return 0;
}

int errorf ( const char * format, ... ){
    va_list arg;
    va_start (arg, format);
    if(log == 1){
        openlog("Logger", LOG_PID | LOG_CONS, LOG_SYSLOG);
        vsyslog(LOG_EMERG,format, arg);
        closelog();

    } else {
        vprintf (format, arg);
    }
    va_end (arg);
    return 0;
}

int panicf ( const char * format, ... ){
    va_list arg;
    va_start (arg, format);

    if(log == 1){
        openlog("Logger", LOG_PID | LOG_CONS, LOG_SYSLOG);
        vsyslog(LOG_EMERG,format, arg);
        closelog();
    } else {
        vprintf (format, arg);
    }
    va_end (arg);
    return 1;
}

