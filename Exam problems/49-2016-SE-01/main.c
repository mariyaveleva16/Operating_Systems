#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <err.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int comperator(const void* x,const void* y){
	return (*(unsigned char*)x - *(unsigned char*)y);
}
int main (const int argc, const char* argv[]){
	if ( argc != 2 ){
		errx(1, "Wrong number of parameters");
	}

	int fd;
	if((fd = open(argv[1], O_RDONLY)) == -1){
	   err(2, "Error opening %s", argv[1]);	
	}
	struct stat st;
	const char* file = argv[1];
	if(stat(file,&st)== -1){
		err(3, "Error while stat the file");
	}
	if(!st.st_size){
		exit(0);
	} 
	void* ptr = malloc(st.st_size);
	if(ptr==NULL){
		err(4, "Memmory not allocated");
	}

	if ( st.st_size != read(fd, ptr, st.st_size)){
		free(ptr);
		err(5, "err reading");
	}
	qsort(ptr, st.st_size, 1 , comperator);
	close(fd);
	int fd1;
	if((fd1 = open(argv[1], O_WRONLY, O_CREAT, O_TRUNC, S_IRUSR, S_IWUSR, S_IRGRP, S_IROTH)) == -1){
			err(6, "err open for editing");
	}
	if (st.st_size != write(fd1 ,ptr, st.st_size)){
		free(ptr);
		err(7, "err writing");
	}

	free(ptr);
	close(fd1);
	exit(0);
}
