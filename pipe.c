#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BSIZE 100
void main()
{
    int fildes[2];
    char buf[BSIZE];
    ssize_t nbytes;
    int status;
    pid_t pid;
    pid_t cpid;
    
    status = pipe(fildes);
    if (-1 == status) 
    {
        printf("pipe failed, errno(%d), errstr(%s)\n", errno, strerror(errno));
        return;
    }

    switch (cpid = fork()) 
    {
        case -1: 
            printf("fork failed, errno(%d), errstr(%s)\n", errno, strerror(errno));
            break;
        case 0:  /* Child - reads from pipe */
            close(fildes[1]);                       /* Write end is unused */
            nbytes = read(fildes[0], buf, BSIZE);   /* Get data from pipe */
            close(fildes[0]);                       /* Finished with pipe */
            printf("child read : %s\n", buf);
            printf("child exit\n");
            break;

        default:  /* Parent - writes to pipe */
            close(fildes[0]);                       /* Read end is unused */
            write(fildes[1], "Hello world\n", 12);  /* Write data on pipe */
            close(fildes[1]);                       /* Child will see EOF */
            printf("parent write : %s\n", "Hello world\n");
            pid = waitpid(cpid, NULL, 0);
            printf("parent exit\n");
            break;
    }

    return;
}
