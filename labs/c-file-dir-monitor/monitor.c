#include <stdio.h>
#include "logger.h"
#include <unistd.h>
#include <sys/inotify.h>
#include <ftw.h>

struct inotify_event *iNotifyEvent;
int main(int argc, char** argv){
    char *size;
    int iNotifyAPI;
	int readd;
    int x = 1;
    char buffer[1024 * (sizeof(struct inotify_event) + 16)];
	int wind;
	
	if(argc == 2) {
		iNotifyAPI = inotify_init();
		if(iNotifyAPI == -1)
			errorf("Error");
		wind = inotify_add_watch(iNotifyAPI, argv[1], IN_ALL_EVENTS);
		if(wind == -1)
			errorf("Error");
        infof("Starting file/directory monitor on %s", argv[1]);
		while(x == 1) {
			readd = read(iNotifyAPI, buffer, 1024*(sizeof(struct inotify_event)+16));
			for (size=buffer; size<buffer+readd;){
				iNotifyEvent = (struct inotify_event*) size;
                if (iNotifyEvent->mask & IN_CREATE){
					if(iNotifyEvent->mask & IN_ISDIR){
                    	printf("[Directory - ");
                	}else{
                    	printf("[File - ");
                	}
		            infof("Create] - %s", iNotifyEvent->name);
				}
	            if (iNotifyEvent->mask & IN_DELETE){
					if(iNotifyEvent->mask & IN_ISDIR){
                    	printf("[Directory - ");
                	}else{
                    	printf("[File - ");
                	}
		            infof("Removal] - %s", iNotifyEvent->name);
				}
	            if (iNotifyEvent->mask & IN_MOVE){
					if(iNotifyEvent->mask & IN_ISDIR){
                    	printf("[Directory - ");
                	}else{
                    	printf("[File - ");
                	}
		            infof("Rename] - %s", iNotifyEvent->name);
				}
				watchSize += sizeof(struct inotify_event)+iNotifyEvent->len;
			}
		}
		inotify_rm_watch(iNotifyAPI, wind);
		close(iNotifyAPI);
	}
	else
		warnf("Error");
    return 0;
}