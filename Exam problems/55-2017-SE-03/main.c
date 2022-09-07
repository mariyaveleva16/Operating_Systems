#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<err.h>
#include<fcntl.h>
#include<unistd.h>

struct troika{
	uint16_t off;
	uint8_t old;
	uint8_t new;
}__attribute__((packed));

int main(const int argc, const char* argv[]){
	if(argc != 4){
		err(1,"Wrong number of arg");
	}
	struct stat st2;
	if(stat(argv[2], &st2) == -1){
		err(2, "Error stating %s", argv[2]);
	}
	if( st2.st_size == 0){
		err(3, "File %s is empty", argv[2]);
	}
	struct troika t;
	struct stat st1;
	if(stat(argv[1], &st1) == -1){
		err(4, "Error stating %s", argv[1]);
	}
	if(st1.st_size ==0 ){
		err(5, "File %s is empty", argv[1]);
	}
	if((st1.st_size%sizeof(t)) != 0){
		err(6, "Wrong file format %s", argv[1]);
	}
	int fd1;
	if((fd1=open(argv[2],O_RDONLY)) == -1){
		err(7, "Error opening %s", argv[2]);
	}
	int fdPatch;
	if((fdPatch=open(argv[1], O_RDONLY))==-1){
		err(8, "Error opening %s", argv[1]);
	}
	int fd2;
	if((fd2=open(argv[3], O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP))==-1){
		err(9,"Error opening %s", argv[3]);
	}
	int read_size;
	int byte=0;
	uint8_t a;
	read(fdPatch, &t, sizeof(t));
	while((read_size=(read(fd1, &a, sizeof(a)))) == sizeof(a)){
		if(byte > t.off ){
			read(fdPatch, &t, sizeof(t));
		}
		if(byte != (int)t.off){
			write(fd2, &a, sizeof(a));
		}
		else{
			write(fd2, &t.new, sizeof(t.new));
		}
		byte++;
	}
	exit(0);
}	
