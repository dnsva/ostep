#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){

    printf("Hello world (pid:%d)\n", (int) getpid());

    int fd[2];
    if(pipe(fd) != 0){
        fprintf(stderr, "err with pipe\n");
    }

    int rc = fork();

    if(rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
        
    }else if(rc == 0){ //child
        close(fd[0]);
        printf("hello i am the child (pid:%d)\n", (int) getpid());
        int x = 42;
        printf("x is %d\n", x); 
        write(fd[1], &x, sizeof(int));
        close(fd[1]);

    }else{ //parent
        close(fd[1]);
        int rc_wait = waitpid(rc, NULL, 0);
        printf("hello, I am parent of %d (rc_wait:%d) (pid:%d)\n", rc, rc_wait, (int) getpid());
        int x;
        read(fd[0], &x, sizeof(int));
        close(fd[0]);
        printf("x recieved from child process is %d\n", x);
    }

    return 0;
}