#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

static void run_as_daemon(void);

int main(int argc, char *argv[]) {

    if(argc < 2) {
        fprintf(stderr, "%s commands...[absolute path]\n", argv[0]);
        exit(1);
    }//end if

    run_as_daemon();
    execv(argv[1], argv + 1);
    perror("execv()"); //should not be here
    _exit(127);
}//end main

static void run_as_daemon(void) {
    pid_t pid;
 
    /* Clone ourselves to make a child */  
    pid = fork(); 
     
    /* If the pid is less than zero,
       something went wrong when forking */
    if (pid < 0) {
        perror("fork()");
        exit(EXIT_FAILURE);
    }//end if
     
    /* If the pid we got back was greater
       than zero, then the clone was
       successful and we are the parent. */
    if (pid > 0) {
        _exit(EXIT_SUCCESS);
    }//end if
     
    /* If execution reaches this point we are the child */
    /* Set the umask to zero */
    umask(0);
    /* Open a connection to the syslog server */
    //openlog(log_path, LOG_NOWAIT | LOG_PID, LOG_USER); 
 
    /* Sends a message to the syslog daemon */
    //fprintf(stdout, "Successfully started daemon\n"); 

    pid_t sid;
 
    /* Try to create our own process group */
    sid = setsid();
    if (sid < 0) {
        perror("setsid()");
        fprintf(stderr, "Could not create process group\n");
        exit(EXIT_FAILURE);
    }//end if

    /* Change the current working directory */
    if ((chdir("/")) < 0) {
        perror("chdir()");
        fprintf(stderr, "Could not change working directory to /\n");
        exit(EXIT_FAILURE);
    }//end if

    /* redirect to /dev/null */
    int fd = open("/dev/null", O_WRONLY);
    dup2(fd, 0);
    dup2(fd, 1);
    dup2(fd, 2);
    close(fd);
}//end run_as_daemon
