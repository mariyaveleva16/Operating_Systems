#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<err.h>
#include<unistd.h>

struct troika{
	uint16_t off;
	uint8_t old;
	uint8_t new;
}__attribute__((packed));

int main(const int argc, const char* argv[]){

	if ( argc != 4 ){
		errx(1, "Wrong number of parameters.");
	}
	
	//stat f1 =stat f2
	struct stat st1;
	if ( (stat(argv[1], &st1)) == -1 ){
		err(2, "Error stating file %s", argv[1]);
	}
	if( st1.st_size == 0 ){
		err(3, "File %s is empty", argv[1]);
	}
	
	struct stat st2;
	if ( (stat(argv[2], &st2)) == -1 ){
		err(4, "Error stating file %s", argv[2]);
	}
	if( st2.st_size == 0 ){
		err(5, "File %s is empty", argv[2]);
	}
	
	if( st1.st_size != st2.st_size ){
		err(6, "Files %s and %s must have the same size", argv[1], argv[2]);
	}

	//open f1 read
	int fd1;
	if( (fd1=open(argv[1], O_RDONLY)) == -1 ){
		err(7, "Error opening file %s", argv[1]);
	}

	//open f2 read
	int fd2;
	if( (fd2=open(argv[2], O_RDONLY)) == -1 ){
		err(8, "Error opening file %s", argv[2]);
	}

	//open f3 write
	int fd3; 
	if( (fd3=open(argv[3], O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP)) == -1){
			err(9, "Error creating file %s", argv[3]);
	}
	
	int i=0;
	uint8_t a;
	uint8_t b;
	int read_size;
	struct troika t;
	while (i<st1.st_size){
		
		if( (read_size = read(fd1, &a, sizeof(a))) == -1 ){
			err(10, "Err");
		}
		
		if( (read_size = read(fd2, &b, sizeof(b))) == -1 ){
			err(11, "Err");
		}
		
		if( a != b ){
			t.off=(uint16_t)i;
			t.old=a;
			t.new=b;
			write(fd3, &t, sizeof(t));
		}
	
		i=i+1;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	exit(0);
}
