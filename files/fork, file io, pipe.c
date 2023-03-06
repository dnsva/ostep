//fork pipe wait file

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){

    int fd[2]; //pipe
    if(pipe(fd) != 0){ 
        fprintf(stderr, "err with pipe\n");
    }

    int rc = fork(); //create process

    if(rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
        
    }else if(rc == 0){ //child

        close(fd[0]); //close read end of pipe

        int fd2 = open("./AAA.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU); //make file
        char message [100];
        sprintf(message, "hello i am the child (pid:%d)\n", (int) getpid()); //write formatted data to string
        write(fd2, message, strlen(message)); //write to file
        close(fd2); //close file

        int x = 42;
        write(fd[1], &x, sizeof(int));
        close(fd[1]); //close write

    }else{ //parent

        int rc_wait = waitpid(rc, NULL, 0); //wait for child to end 

        close(fd[1]); //close write end of pipe

        int fd2 = open("./AAA.output", O_WRONLY); //open file
        lseek(fd2, 0, SEEK_END); //go to end of file 
        char message [100];
        sprintf(message, "hello, I am parent of %d (rc_wait:%d) (pid:%d)\n", rc, rc_wait, (int) getpid()); 
        write(fd2, message, strlen(message)); //write to file

        int x;
        read(fd[0], &x, sizeof(int));
        close(fd[0]); //close read

        
        sprintf(message, "x recieved from child process is %d\n", x);
        lseek(fd2, 0, SEEK_END);
        write(fd2, message, strlen(message)); //write to file
        close(fd2); //close file
        
    }

    return 0;
}