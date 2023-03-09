//sys call cost

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/time.h>

int main(int argc, char* argv[]){

    
    struct timeval tv1;
    gettimeofday(&tv1, NULL);

    long long sum = 0;

    for(int i = 0; i < 10; ++i){
        int fd2 = open("./AAA.output", O_CREAT|O_WRONLY); //open file
        write(fd2, " ", 0); //write to file
        close(fd2); //close file
        struct timeval tv2;
        gettimeofday(&tv2, NULL);  
        sum += tv2.tv_usec - tv1.tv_usec;
        tv1 = tv2;
    }

    printf("Sum before is %d\n", sum);
    printf("Average is %d\n", sum/10);
    
    return 0;
}