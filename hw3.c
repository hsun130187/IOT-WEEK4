//Name:Hui Sun
//complile command : gcc-g hw3.c -o homed
//run the process:  ./homed 
// look at the syslog: cat/var/log/syslog
//kill the process: pidof homed //ThiS command is used to look at the pid number of this proocess. Then use the command
// kill pidnumber to end this process.

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<syslog.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>
#include<errno.h>  //This is for errno
#include<time.h>
#define OK 0
#define DAEMON_NAME "homed"
#define ERROR_FORMAT   "Couldn't fork: %s"
#define ERR_FORK     2
#define ERR_SETSID    3
#define ERR_CHDIR     4
#define ERR_WTF       5

static void _signal_handler(const int signal){
	switch(signal){
		case SIGHUP:
			break;
		case SIGTERM:
			syslog(LOG_INFO,"received SIGTERM, exiting");
			closelog();
			exit(OK);
			break;
		default:
			syslog(LOG_INFO,"RECEIVED unhandled signal");
	}
}

static void _dowork(void){
	for(int i=0;true;i++){
		
		//syslog(LOG_INFO,"ITERATION: %d",i);
		time_t tmpcal_ptr;
		struct tm *tmp_ptr = NULL;
		time(&tmpcal_ptr);
		printf("tmpcal_ptr=%d\n", tmpcal_ptr);
		tmp_ptr = localtime(&tmpcal_ptr);
		char time[50];
		// write time into syslog
		sprintf(time,"%d-%d-%d %d:%d:%d", (1900+tmp_ptr->tm_year), (1+tmp_ptr->tm_mon), tmp_ptr->tm_mday,tmp_ptr->tm_hour, tmp_ptr->tm_min, tmp_ptr->tm_sec);
		syslog(LOG_INFO,"current time is %s", time);
		sleep(1);
	}
}

int main(void){
	openlog(DAEMON_NAME, LOG_PID | LOG_NDELAY |LOG_NOWAIT, LOG_DAEMON);
	syslog(LOG_INFO,"starting sampled");
	pid_t pid=fork();
	if(pid<0){
		syslog(LOG_ERR,ERROR_FORMAT,strerror(errno));//SOME PROBLEM HERE
		return ERR_FORK;
	}
	if(pid>0){
		return OK;
	}
	if(setsid()<-1){
		syslog(LOG_ERR,ERROR_FORMAT, strerror(errno));
		return ERR_SETSID;
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	
	umask(S_IRUSR | S_IWUSR| S_IRGRP | S_IROTH);
	if(chdir("/")<0){
		syslog(LOG_ERR,ERROR_FORMAT,strerror(errno));
		return ERR_CHDIR;

	}
	signal(SIGTERM,_signal_handler);
	signal(SIGHUP,_signal_handler);
	_dowork();
	return ERR_WTF;


}
