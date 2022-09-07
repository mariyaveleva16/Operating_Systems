#include<stdio.h>
#include<stdlib.h>
#include<err.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdint.h>
#include<sys/stat.h>

struct IDX{
	uint16_t offset;
	uint8_t leng;
	uint8_t save;
}__attribute__((packed));

int main(const int argc, const char* argv[]){
	if ( argc != 5 ){
		errx(1, "Wr number of params");
	}
	struct stat st1;
	if((stat(argv[1], &st1)) == -1){
	}
	if(st1.st_size == 0){
	}
	struct stat st2;
	if((stat(argv[2], &st2)) == -1){
	}
	if(st2.st_size == 0){
	}
	struct IDX tri;
	if(((st2.st_size)%sizeof(tri)) != 0){
	}
	int fd1;
	if( (fd1 = open(argv[1], O_RDONLY)) == -1){
	}
	int fd2;
	if ( (fd2 = open(argv[2], O_RDONLY)) == -1){
	}
	int fd3;
	if ( (fd3 = open(argv[3], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP)) == -1){
	}
	int fd4;
	if ( (fd4 = open(argv[4], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP)) == -1){
	}

	int read_size;
	while((read_size=read(fd2, &tri, sizeof(tri))) == sizeof(tri)){
		if((lseek(fd1, tri.offset, SEEK_SET)) == -1){
		}
		uint8_t a;
		read(fd1, &a, sizeof(a));
		if( 'A'<=a && a>='Z'){
			write(fd3, &a, sizeof(a));
			for(int i=0; i<tri.offset; i++){
				read(fd1, &a, sizeof(a));
				write(fd3, &a, sizeof(a));
			}

		}
	}

	close(fd1);
	close(fd2);
	close(fd3);
	close(fd4);
	exit(0);
}
