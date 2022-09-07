#include<stdint.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<err.h>
#include<fcntl.h>
#include<unistd.h>

int main(const int argc, const char* argv[]){
	if(argc != 2){
		errx(1, "Wrong number of parameters");
	}
	
	int fd;
	if((fd=open(argv[1], O_RDONLY))==-1){
		err(2, "Err opening %s",argv[1]); 
	}
	
	int p[2];
	if(pipe(p)==-1){
		err(3, "Couldn't pipe");
	}

	const pid_t child_cat=fork();
	if(child_cat==-1){
		err(4, "Couldn't fork");
	}

	if(child_cat == 0){
		close(p[0]);
		if(dup2(p[1], 1)==-1){			
			err(5, "Couldn't dup");
		}
		if(execl("/bin/cat", "cat", argv[1], (char*)NULL)== -1){
			err(6, "Couldn't execl cat");
		}
	}
	close(p[1]);

	if(dup2(p[0], 0)==-1){
		err(7, "Couldn't dup");
	}
	if(execlp("sort", "sort", (char*)NULL)==-1){
		err(8, "Couldn't exelp");
	}

	exit(0);
}
