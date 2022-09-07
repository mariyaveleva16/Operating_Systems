#include <err.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char* argv[]){
        if(argc != 3){
                errx(1, "We need 2 arguments");
        }

        if(strlen(argv[1]) > 1){
                errx(5, "[0-9] numeber needed");
        }

        if(strlen(argv[2]) > 1){
                errx(5, "[0-9] number needed");
        }

        int n = argv[1][0] - '0';
        int d = argv[2][0] - '0';

        if(n < 0 || n > 9){
                errx(2, "We need number in [0,9]");
        }

        if(d < 0 || d > 9){
                errx(2, "We need numebr in [0,9]");
        }

        int cw[2];
        int pw[2];

        char cok;
        char pok;
        char nia=42;

        if(pipe(cw) < 0){
                err(5, "Error pipe");
        }

        if(pipe(pw) < 0){
                err(5, "Error pipe");
        }

        pid_t p = fork();

        if(p < 0){
                err(3, "Error fork");
        }

        if(p == 0){

                close(cw[1]);
                close(pw[0]);
                for(int i = 0; i < n; i++){
                //      wait();

                        read(cw[0], &cok, sizeof(cok));
                        if(write(1, "DONG\n", 5) != 5){
                                err(4, "Error writinig");
                        }

                        write(pw[1], &nia, sizeof(nia));

                }

                exit(0);
        }

        for(int i = 0; i < n; i++){

                close(cw[0]);
                close(pw[1]);

                if(write(1, "DING\n", 5) != 5){
                        err(4, "Error writing");
                }

                write(cw[1], &nia, sizeof(nia));
                read(pw[0], &pok, sizeof(pok));
                sleep(d);
        }

        wait(NULL);
        exit(0);
}
