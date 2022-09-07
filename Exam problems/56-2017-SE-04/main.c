#include<stdlib.h>
#include<sys/types.h>
#include<stdint.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<err.h>

int main(const int argc, const char* argv[]){
	if( argc == 1){ //da nqma argumenti
		uint8_t a;
		while(read(0, &a, sizeof(a)) ==sizeof(a)){
			write(1, &a, sizeof(a));
		}
	}
	else{ // s argumenti
		int arg=1;
		while(arg<argc){
			uint8_t a;
			if( strcmp( argv[arg], "-") ==0){
				while(read(0, &a, sizeof(a)) == sizeof(a)){
					write(1, &a,sizeof(a));
				}
			}
			else{
				int fd;
				if((fd=open(argv[arg],O_RDONLY)) == -1){
					err(2, "Err opening");
				}
				while(read(fd, &a, sizeof(a)) == sizeof(a)){
					write(1, &a, sizeof(a));
				}
				close(fd);
			}
			arg++;
		}
	}
	exit(0);
}	
